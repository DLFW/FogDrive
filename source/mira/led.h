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

#ifndef LED_H
#define LED_H

#include <avr/io.h>

typedef struct {
    uint8_t duty_cycle_count;
    uint8_t* p_port;
    uint8_t pin_mask;
} LED;

extern uint8_t led_pwm_cycle_counter;

void led_init_led(LED* led);

void led_step(LED* led);

void led_set_brightness(LED* led, uint8_t brightness);

#endif // LED_H
