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
#include <util/delay.h>
#include "logic.h"
#include "deviface.h"
#include "hardware.h"
#include "ui.h"

uint16_t logic_main_cycle_counter;
uint16_t last_logic_cycles_per_50ms_event;

uint8_t logic_init(void) {
    logic_main_cycle_counter = 0;
    last_logic_cycles_per_50ms_event = 0;
    return 0;
}

void logic_loop (void) {
    static uint16_t last_logic_cycle_value = 0; // stores the logic cycle count at each 50 ms event and is used to calc the delta
    deviface_putline("FogDrive  Copyright (C) 2016, the FogDrive Project");
    deviface_putline("This program is free software and comes with ABSOLUTELY NO WARRANTY.");
    deviface_putline("It is licensed under the GPLv3 (see <http://www.gnu.org/licenses/#GPL>).");
    deviface_putline("\r\nHi! This is the Mira 0 FogDrive.\r\n");
    while(1) {
        ui_input_step();
        hardware_step();

        // process UI event
        QueueElement* e = queue_get_read_element(&ui_event_queue);
        if (e != 0) {
            if (e->bytes.a == UI__FIRE_BUTTON_PRESSED) {
                hardware_fire_on();
            }
            if (e->bytes.a == UI__FIRE_BUTTON_RELEASED) {
                hardware_fire_off();
            }
            if (e->bytes.a == UI__50MS_PULSE) {
                if (last_logic_cycle_value < logic_main_cycle_counter) {
                    // no overflow
                    last_logic_cycles_per_50ms_event = logic_main_cycle_counter - last_logic_cycle_value;
                }
                last_logic_cycle_value = logic_main_cycle_counter;
            }
        }
        //process HW event
        e = queue_get_read_element(&hw_event_queue);
        if (e != 0) {
            if (e->bytes.a == HW__FIRE_ON) {
                ui_fire_is_on();
            }
            else if (e->bytes.a == HW__FIRE_OFF) {
                ui_fire_is_off();
            }
            else if (e->bytes.a == HW__BATTERY_MEASURE) {
                uint8_t value = e->bytes.b;
                char value_s[6];
                itoa(value,value_s,10);
                deviface_putstring("BVM: ");
                deviface_putstring(value_s);
                deviface_putstring("\n\r");
            }
        }

        if (uart_str_complete) {
            char in_string[UART_MAXSTRLEN + 1];
            strcpy (in_string, uart_string);
            uart_str_complete = 0;
            if (strcmp(in_string, "off") == 0) {
                hardware_fire_off();
            }
            if (strcmp(in_string, "on") == 0) {
                hardware_fire_on();
            }
            if (strcmp(in_string, "bvm") == 0) {
                do_battery_measurement();
            }
            if (strcmp(in_string, "cyc 50ms") == 0) {
                deviface_putstring("Main cycles per 50ms event: ");
                deviface_put_uint16(last_logic_cycles_per_50ms_event);
                deviface_putlineend();
            }
            if (strcmp(in_string, "cyc count") == 0) {
                deviface_putstring("Main cycle counter: ");
                deviface_put_uint16(logic_main_cycle_counter);
                deviface_putlineend();
            }
            if (strcmp(in_string, 'ui leds')) {
                ui_print_led_info();
            }
        }
        logic_main_cycle_counter++;
    }
    return 0;
}

