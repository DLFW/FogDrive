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
#include <avr/pgmspace.h>

#define _LED_MAX_COMMAND_COUNT 12

typedef struct {
    uint8_t cmd;
    union {
        struct {
            uint8_t a;
            uint8_t b;
            uint8_t c;
        } generic;
        struct {
            uint8_t value;
            uint8_t _dead_;
            uint8_t _dead__;
        } brightness;
        struct {
            uint8_t index;
            uint8_t number;
            uint8_t counter;
        } repeat;
        struct {
            uint8_t duration;   // 0 for infinity
            uint8_t _dead_;
            uint8_t _dead__;
        } hold;
        struct {
            uint8_t _ramp_duration;
            uint8_t _start_brightness;
            uint8_t _target_brightness;
        } dim_linear;
    };
} LEDCommand;


typedef struct {
    uint8_t* _compare_register_address;
    uint8_t _step_count;
    uint8_t _current_brightness;
    LEDCommand _commands[_LED_MAX_COMMAND_COUNT];
    uint8_t _current_command_ix; // [0..9] as index for the command, 255 for "no command"
    uint8_t _command_count;
} LED;


void led_init_led(LED* led, uint8_t* compare_register_address);

void led_step(LED* led);

void led_set_brightness(LED* led, uint8_t brightness);

void led_program_reset(LED* led);

void led_program_add_brightness(LED* led, uint8_t brightness);

void led_program_add_linear_dim(LED* led, uint8_t brightness, uint8_t ramp_duration);

void led_program_add_hold(LED* led, uint8_t duration);

void led_program_repeat(LED* led, uint8_t from_step, uint8_t number);

void led_start_program(LED* led);

#endif // LED_H
