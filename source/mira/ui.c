/*
    FogDrive (https://github.com/FogDrive/FogDrive)
    Copyright (C) 2016  Daniel Llin Ferrero

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ui.h"
#include "logic.h"
#include "deviface.h"
#include "led.h"
#include MCUHEADER

// Bit mask for switch 0
#define CTRLMAP_SWITCH_0_MASK   (1<<HWMAP_UI_SWITCH_0_IX)
// Bit mask for all used switches
#define ALL_SWITCHES            (1<<HWMAP_UI_SWITCH_0_IX)

// Bit mask for out pin 0 (LED)
#define OUTPIN_0_MASK           (1<<HWMAP_UI_OUTPIN_0_IX)
// Bit mask for all used out pins
#define OUTPIN_ALL_MASK         (1<<HWMAP_UI_OUTPIN_0_IX)

// Low Level Event codes
#define LLE_SWITCH_PRESSED 1    // a switch was pressed, switch index in 2nd queue element
#define LLE_SWITCH_RELEASED 2   // a switch was released, switch index in 2nd queue element
#define LLE_50MS_PULSE 3        // 50 ms pulse, this event is put in the queue each 50 ms

// User interface input queue (which is an external, see @ui.h#Queue ui_input_queue) and its element array
Queue ui_event_queue;
QueueElement ui_event_queue_elements[5];

/**
 * Queue that transports low level control events to the ui state machines.
 * It's used locally in this module only.
 * It's elements carry a "Low Level Event" (LLE_*) in byte a. In case the event refers to a switch,
 * the switch index is in byte b.
 */
Queue low_level_event_queue;
/**
 * Queue array for #ui_input_queue.
 */
QueueElement low_level_event_queue_array[5];

LED led;

uint8_t ui_timer_cycle_covered_main_cycles;

/**
 * Sets the led value.
 * For future compatibility, use value = 255 for on.
 * @param value 0 for off, anything else for on
 */
void set_led(uint8_t value) {
    led_set_brightness(&led, value);
    return;
    if (value) {
        HWMAP_UI_OUTPIN_PORT = HWMAP_UI_OUTPIN_PORT | OUTPIN_0_MASK;
    } else {
        HWMAP_UI_OUTPIN_PORT = HWMAP_UI_OUTPIN_PORT & ~OUTPIN_0_MASK;
    }
}

uint8_t ui_init(void) {
    // init queues
    queue_initialize(&ui_event_queue, 5, ui_event_queue_elements);
    queue_initialize(&low_level_event_queue, 5, low_level_event_queue_array);

    // init switch pins
    HWMAP_UI_SWITCH_DDR &= ~ALL_SWITCHES;                // configure all input pins as input by setting the related direction bits to 0
    HWMAP_UI_SWITCH_PORT |= ALL_SWITCHES;                // turn on the pull up resistors of all input pins

    // init output pin
    HWMAP_UI_OUTPIN_DDR |= OUTPIN_ALL_MASK;             // configure output pins as output in the related data direction register
    HWMAP_UI_OUTPIN_PORT &= ~OUTPIN_ALL_MASK;           // initialize all output pins (set them off)

    // init the ui timer
    ui_timer_init_200us_overflow();

    // init LED
    led.p_port = &HWMAP_UI_OUTPIN_PORT;
    led.pin_mask = OUTPIN_0_MASK;
    led.duty_cycle_count = 0;

    return 0;
}

/**
  * ISR for timer zero.
  * Configured to be called every 200us.
  */
ISR( HWMAP_UI_TIMER_ISR ) {
    // basic debouncing strategy based on http://www.mikrocontroller.net/articles/Entprellung#Timer-Verfahren_.28nach_Peter_Dannegger.29
    // debouncing counter bytes
    static uint8_t ct0 = 0xFF, ct1 = 0xFF;
    // latest debounced switch state (each bit represents one switch (bit) from the input register (PIN))
    static uint8_t switch_states = 0;
    // latest changed status (1 = changed, 0 = unchanged, each bit represents one switch (bit) from the input register (PIN))
    static uint8_t changed_switches = 0;
    // counter that just counts to fifty times and is resetted then to identify each 50th call of this ISR -> corresponds to 10 ms
    static uint8_t _10ms_counter = 0;
    // counter that just counts to five times and is resetted then to identify each 5th cycle of the 10ms branch
    static uint8_t _50ms_counter = 0;
    // stores the difference of the main cycle counter between each call and the former of this ISR
    static uint8_t last_main_cycle_counter = 0;

    /*
     * High frequent (each 200us)
     */

    // initialize the timer again to get the wanted trigger frequency for this ISR
    //HWMAP_UI_TIMER_CMD_REINIT_FOR_200us;
    TCNT0 = 254;
    // increment LED PWM counter
    led_pwm_cycle_counter++;
    // led PWM step
    led_step(&led);

    if (++_10ms_counter == 50) {
        _10ms_counter = 0;
        /*
         * Middle frequent (each 10ms)
         */

        // updating main cyle counter diff
        if (logic_main_cycle_counter > last_main_cycle_counter) {
            ui_timer_cycle_covered_main_cycles = logic_main_cycle_counter - last_main_cycle_counter;
        }
        last_main_cycle_counter = ui_timer_cycle_covered_main_cycles;

        // here we go...
        // debouncing:
        // set those bits in i to 1 which represents a switch whose actual state is different from the latest unbounced state (key_state)
        uint8_t i = switch_states ^ ~HWMAP_UI_SWITCH_PIN;
        // ct0 and ct1 bytes: count the number of subsequent differences between actual and last debounced state or set back it back to 0 if it's equal.
        ct0 = ~( ct0 & i );
        ct1 = ct0 ^ (ct1 & i);
        // for each switch that had 4 times an actual state different from the last debounced state, set the corresponding bit in i to 1
        i &= ct0 & ct1;
        // set the most current _debounced_ state of all switches
        switch_states ^= i;
        // create a bitmask of all _relevant_ switches that have changed
        changed_switches = i & ALL_SWITCHES;

        // check for concrete switch changes:
        // check for switch 0
        if (CTRLMAP_SWITCH_0_MASK & changed_switches) {
            QueueElement* e = queue_get_write_element(&low_level_event_queue);
            if (CTRLMAP_SWITCH_0_MASK & switch_states) {
                e->bytes.a = LLE_SWITCH_PRESSED;
            } else {
                e->bytes.a = LLE_SWITCH_RELEASED;
            }
            e->bytes.b = HWMAP_UI_SWITCH_0_IX;
        }

        if (++_50ms_counter == 5) {
            _50ms_counter = 0;
            /*
             * Low frequent (each 50ms)
             */
            QueueElement* e = queue_get_write_element(&low_level_event_queue);
            e->bytes.a = LLE_50MS_PULSE;
        }
    }
}

void ui_input_step(void) {
    QueueElement* low_level_event_e = queue_get_read_element(&low_level_event_queue);
    if (low_level_event_e != 0) {
        if (low_level_event_e->bytes.a == LLE_SWITCH_PRESSED) {
            QueueElement* e = queue_get_write_element(&ui_event_queue);
            e->bytes.a = UI__FIRE_BUTTON_PRESSED;
        }
        else if (low_level_event_e->bytes.a == LLE_SWITCH_RELEASED) {
            QueueElement* e = queue_get_write_element(&ui_event_queue);
            e->bytes.a = UI__FIRE_BUTTON_RELEASED;
        }
        else if (low_level_event_e->bytes.a == LLE_50MS_PULSE) {

        }
    }
}

void ui_fire_is_on(void) {
    set_led(128);
}

void ui_fire_is_off(void) {
    set_led(0);
}