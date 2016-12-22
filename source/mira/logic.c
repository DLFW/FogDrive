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

static uint16_t logic_main_cycle_counter;
static uint16_t last_logic_cycles_per_50ms_event;
static uint16_t min_logic_cycles_per_50ms_event = 0xFFFF;

uint8_t battery_voltage_unstressed = 0;
uint8_t battery_voltage_under_load = 0;

static uint8_t local_bools = 0;
#define LB_HW_IS_FIRING   1
#define LB_PRINT_BVMS     2

static uint8_t pulse_counter_for_battery_voltage_measurement = 0;

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
                // 1) do the main cycle time measurement (for development purposes only)
                if (last_logic_cycle_value < logic_main_cycle_counter) {
                    // no overflow
                    last_logic_cycles_per_50ms_event = logic_main_cycle_counter - last_logic_cycle_value;
                    if (min_logic_cycles_per_50ms_event > last_logic_cycles_per_50ms_event) {
                        min_logic_cycles_per_50ms_event = last_logic_cycles_per_50ms_event;
                    }
                }
                last_logic_cycle_value = logic_main_cycle_counter;

                // 2) trigger cyclical battery voltage measurement
                if (local_bools & LB_HW_IS_FIRING) {
                    if (pulse_counter_for_battery_voltage_measurement == 4) {   // every 200ms (4*50ms) when the mod is firing
                        do_battery_measurement();
                        pulse_counter_for_battery_voltage_measurement = 0;
                    }
                } else {
                    if (pulse_counter_for_battery_voltage_measurement == 40) { // every ~12s (256*50ms) when the mod is _not_ firing
                        do_battery_measurement();   // we use "40" as compare value to give the battery 2s (40*50ms) to relax after stopping firing
                        // we do not reset the counter but just let it overflow (reset at 256)
                    }
                }
                ++pulse_counter_for_battery_voltage_measurement;
            }
        }

        //process HW event
        e = queue_get_read_element(&hw_event_queue);
        if (e != 0) {
            if (e->bytes.a == HW__FIRE_ON) {
                local_bools |= LB_HW_IS_FIRING;
                pulse_counter_for_battery_voltage_measurement = 0;
                ui_fire_is_on();
            }
            else if (e->bytes.a == HW__FIRE_OFF) {
                local_bools &= ~LB_HW_IS_FIRING;
                pulse_counter_for_battery_voltage_measurement = 0;
                ui_fire_is_off();
            }
            else if (e->bytes.a == HW__BATTERY_MEASURE) {
                if (local_bools & LB_HW_IS_FIRING) {
                    battery_voltage_under_load = e->bytes.b / 5;   // hw module gives the voltage in 20mV steps...
                } else {
                    battery_voltage_unstressed = e->bytes.b / 5;   // ...but in the logic and the UI module, we process it in 0.1V steps
                }
                if (local_bools & LB_PRINT_BVMS) {
                    deviface_putstring("BVM: ");
                    deviface_put_uint8(e->bytes.b);
                    deviface_putlineend();
                }
            }
        }

        //process commands from the devolper interface (deviface) (UART)
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
            if (strcmp(in_string, "cyc last 50ms") == 0) {
                deviface_putstring("Last cycle number per 50ms event: ");
                deviface_put_uint16(last_logic_cycles_per_50ms_event);
                deviface_putlineend();
            }
            if (strcmp(in_string, "cyc min 50ms") == 0) {
                deviface_putstring("Minimum cycles number per 50ms event: ");
                deviface_put_uint16(min_logic_cycles_per_50ms_event);
                deviface_putlineend();
            }
            if (strcmp(in_string, "cyc count") == 0) {
                deviface_putstring("Main cycle counter: ");
                deviface_put_uint16(logic_main_cycle_counter);
                deviface_putlineend();
            }
            if (strcmp(in_string, "ui leds") == 0) {
                ui_print_led_info();
            }
            if (strcmp(in_string, "bvl") == 0) {
                deviface_putstring("Battery voltage under load: ");
                deviface_put_uint8(battery_voltage_under_load);
                deviface_putstring("\n\r");
            }
            if (strcmp(in_string, "bv") == 0) {
                deviface_putstring("Battery voltage unstressed: ");
                deviface_put_uint8(battery_voltage_unstressed);
                deviface_putstring("\n\r");
            }
            if (strcmp(in_string, "bools lg") == 0) {
                char value_s[9];
                utoa(local_bools,value_s,2);
                deviface_putstring("Logic bools: ");
                deviface_putstring(value_s);
                deviface_putstring("\n\r");
            }
            if (strcmp(in_string, "p bvm on") == 0) {
                local_bools |= LB_PRINT_BVMS;
            }
            if (strcmp(in_string, "p bvm off") == 0) {
                local_bools &= ~LB_PRINT_BVMS;
            }
        }
        logic_main_cycle_counter++;
    }
    return 0;
}

