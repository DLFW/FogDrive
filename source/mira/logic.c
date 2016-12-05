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

static uint8_t fire_button_is_pressed = 0;
static uint8_t fire_button_was_pressed = 0;

uint8_t logic_init(void) {
    return 0;
}

void logic_loop (void) {
    deviface_putline("FogDrive  Copyright (C) 2016, the FogDrive Project");
    deviface_putline("This program is free software and comes with ABSOLUTELY NO WARRANTY.");
    deviface_putline("It is licensed under the GPLv3 (see <http://www.gnu.org/licenses/#GPL>).");
    deviface_putline("\r\nHi! This is the Mira 0 FogDrive.\r\n");
    ui_fire_is_on();
    _delay_ms(100);
    ui_fire_is_off();
    _delay_ms(100);
    ui_fire_is_on();
    _delay_ms(100);
    ui_fire_is_off();
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
        }
    }
    return 0;
}

