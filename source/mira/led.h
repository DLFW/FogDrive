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

static const uint8_t led_pwmtable[100] PROGMEM =
{
//    0,    0,    0,    0,    0,    1,    1,    1,
//    2,    2,    3,    3,    4,    4,    5,    6,
//    7,    8,    8,    9,   10,   11,   13,   14,
//    15,   16,   18,   19,   20,   22,   23,   25,
//    27,   28,   30,   32,   34,   36,   38,   40,
//    42,   44,   46,   48,   50,   53,   55,   57,
//    60,   62,   65,   68,   70,   73,   76,   79,
//    82,   85,   88,   91,   94,   97,  100,  103,
//    107,  110,  113,  117,  120,  124,  127,  131,
//    135,  139,  142,  146,  150,  154,  158,  162,
//    167,  171,  175,  179,  184,  188,  192,  197,
//    201,  206,  211,  215,  220,  225,  230,  235,
//    240,  245,  250,  255
    5,   18,   31,   43,   55,   66,   76,   86,
   95,  103,  112,  119,  127,  134,  140,  146,
  152,  158,  163,  168,  173,  177,  182,  186,
  189,  193,  196,  200,  203,  205,  208,  211,
  213,  215,  218,  220,  222,  224,  225,  227,
  228,  230,  231,  233,  234,  235,  236,  237,
  238,  239,  240,  241,  242,  243,  243,  244,
  245,  245,  246,  246,  247,  247,  248,  248,
  249,  249,  249,  250,  250,  250,  251,  251,
  251,  252,  252,  252,  252,  252,  253,  253,
  253,  253,  253,  253,  254,  254,  254,  254,
  254,  254,  254,  254,  254,  255,  255,  255,
  255,  255,  255,  255
};


typedef struct {
    uint8_t* _compare_register_address;
    uint8_t _state;
    uint8_t _step_count;
    uint8_t _ramp_duration;
    uint8_t _start_brightness;
    uint8_t _current_brightness;
    uint8_t _target_brightness;
} LED;

void _led_dim_linear(LED* led, uint8_t brightness, uint8_t ramp_duration);

void led_init_led(LED* led, uint8_t* compare_register_address);

void led_step(LED* led);

void led_set_brightness(LED* led, uint8_t brightness);

#endif // LED_H
