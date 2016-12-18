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

#define LSMS_HOLD        0      // maunal set, no lightning function running
#define LSMS_LINEAR_DIM  1      // led is swithing on


void led_init_led(LED* led, uint8_t *compare_register_address) {
    led->_compare_register_address = compare_register_address;
    led->_state = LSMS_HOLD;
    led->_step_count = 0;
    led_set_brightness(led, 0);
}

void _led_set_brightness(LED* led, uint8_t brightness) {
    if (brightness > 99) {
        brightness = 99;
    }
    *(led->_compare_register_address) = pgm_read_byte(& led_pwmtable[99 - brightness]);
    led->_current_brightness = brightness;
}

void _led_start_command(LED* led) {
    led->_state = LSMS_HOLD;
}

void led_step(LED* led) {
    switch (led->_state) {
        case LSMS_HOLD: {
            break;
        }
        case LSMS_LINEAR_DIM: {
            led->_step_count++;
            if (led->_ramp_duration == 0 || led->_step_count == led->_ramp_duration) {
                _led_set_brightness(led,led->_target_brightness);
                _led_start_command(led);
            } else {
//              deviface_put_uint8(led->_target_brightness);
//              deviface_putstring("-");
//              deviface_put_uint8(led->_start_brightness);
//              deviface_putstring("-");
//              deviface_put_uint8(led->_step_count);
//              deviface_putstring("-");
              uint8_t b = (uint8_t)(((float)(led->_target_brightness - led->_start_brightness) / (float)led->_ramp_duration) + 0.5);
//              deviface_put_uint8(b);
              b = b * led->_step_count;
//              deviface_putstring("-");
//              deviface_put_uint8(b);
//              deviface_putlineend();
              _led_set_brightness(led, b);
            }
            break;
        }
    }
}




void _led_dim_linear(LED* led, uint8_t brightness, uint8_t ramp_duration) {

    led->_ramp_duration = ramp_duration;
    led->_target_brightness = brightness;
    led->_start_brightness = led->_current_brightness;
    led->_step_count = 0;
    led->_state = LSMS_LINEAR_DIM;
}


void led_set_brightness(LED* led, uint8_t brightness) {
    led->_state = LSMS_HOLD;
    _led_set_brightness(led, brightness);
}
