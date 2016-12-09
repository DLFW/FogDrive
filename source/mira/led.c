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

uint8_t led_pwm_cycle_counter;

//:TODO: remove
void led_init_led(LED* led) {

}

void led_step(LED* led) {
    if (led->duty_cycle_count <= led_pwm_cycle_counter) {
        //led->p_port = *(led->p_port) | led->pin_mask;
        HWMAP_UI_OUTPIN_PORT = HWMAP_UI_OUTPIN_PORT & ~led->pin_mask;
    } else {
        //led->p_port = *(led->p_port) & ~led->pin_mask;
        HWMAP_UI_OUTPIN_PORT = HWMAP_UI_OUTPIN_PORT | led->pin_mask;
    }
}

void led_set_brightness(LED* led, uint8_t brightness) {
//    deviface_putstring("--\r\nb: ");
//    deviface_put_uint8(led->duty_cycle_count);
//    deviface_putstring(" to ");
    led->duty_cycle_count = brightness;
//    deviface_put_uint8(led->duty_cycle_count);
//    deviface_putlineend();
//    deviface_putstring("c: ");
//    deviface_put_uint8(led_pwm_cycle_counter);
//    deviface_putlineend();
}
