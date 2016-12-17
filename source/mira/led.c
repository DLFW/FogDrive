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

#import "led.h"
#import "deviface.h"
#include MCUHEADER

void led_init_led(LED* led, uint8_t *compare_register_address) {
    led->_compare_register_address = compare_register_address;
}

void led_step(LED* led) {

}

void led_set_brightness(LED* led, uint8_t brightness) {
    if (brightness > 99) {
        brightness = 99;
    }
    *(led->_compare_register_address) = pgm_read_byte(& led_pwmtable[99 - brightness]);
}
