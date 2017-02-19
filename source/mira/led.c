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
#include <avr/pgmspace.h>
#include MCUHEADER
#ifdef UART_ENABLED
    #include "deviface.h"
#endif


static const uint8_t led_pwmtable[100] PROGMEM =        // created by "valuearray.py -f logarithmic -a 5 -b 255 -n 100"
{
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


// Commands for a LED, "instant commands" (commands that do not need a temporal duration) must have the lowest values.
// The highest value for an instant command must be specified as HIGHEST_INSTAND_COMMAND_VALUE.
#define COMMAND_SET_BRIGTHNESS  0
#define COMMAND_REPEAT          1
#define COMMAND_CALLBACK        2
#define COMMAND_HOLD            3
#define COMMAND_DIM_LINEAR      4
#define HIGHEST_INSTAND_COMMAND_VALUE 2


void led_init_led(LED* led, uint8_t *compare_register_address) {
    led->_compare_register_address = compare_register_address;
    led_set_brightness(led, 0);
    led_program_reset(led);
}

void led_program_reset(LED* led) {
    led->_current_command_ix = 255;
    led->_command_count = 0;
    led->_step_count = 0;
}

LEDCommand* _get_command_to_add(LED* led) {
    if (led->_command_count < _LED_MAX_COMMAND_COUNT) {
        ++(led->_command_count);
    } else {
        #ifdef UART_ENABLED
        deviface_putstring("ERROR: too much LED commands");
        #endif
    }
    return led->_commands + led->_command_count - 1;
}

void led_program_add_brightness(LED* led, uint8_t brightness) {
    LEDCommand* command = _get_command_to_add(led);
    command->cmd = COMMAND_SET_BRIGTHNESS;
    command->brightness.value = brightness;
}

void led_program_add_hold(LED* led, uint8_t duration) {
    LEDCommand* command = _get_command_to_add(led);
    command->cmd = COMMAND_HOLD;
    command->hold.duration = duration;
}

void led_program_repeat(LED* led, uint8_t from_step, uint8_t number) {
    LEDCommand* command = _get_command_to_add(led);
    command->cmd = COMMAND_REPEAT;
    command->repeat.index = from_step - 1;
    command->repeat.number = number;
    command->repeat.counter = 0;
}

void led_program_add_linear_dim(LED* led, uint8_t brightness, uint8_t ramp_duration) {
    LEDCommand* command = _get_command_to_add(led);
    command->cmd = COMMAND_DIM_LINEAR;
    command->dim_linear._ramp_duration = ramp_duration;
    command->dim_linear._target_brightness = brightness;
}

void led_program_callback(LED* led, LedProgramCallback callback_fct) {
    LEDCommand* command = _get_command_to_add(led);
    command->cmd = COMMAND_CALLBACK;
    command->callback._callback = callback_fct;
}

void _led_set_brightness(LED* led, uint8_t brightness) {
    if (brightness > 99) {
        brightness = 99;
    }
    *(led->_compare_register_address) = pgm_read_byte(& led_pwmtable[99 - brightness]);
    led->_current_brightness = brightness;
}

void _next_command(LED* led) {
    led->_step_count = 0;
    do {
        ++(led->_current_command_ix);
        if (led->_current_command_ix == led->_command_count) {
            // no command left, LED program finished
            led_program_reset(led);
            return;
        } else {
            // check for the next command
            if (led->_commands[led->_current_command_ix].cmd > HIGHEST_INSTAND_COMMAND_VALUE) {
                // not an "instant" command -> will be handled in the led_step function
                return;
            }
            // "instant" commands (handle commands that have no temporal duration here, not in the led_step function)
            switch (led->_commands[led->_current_command_ix].cmd) {
                case COMMAND_SET_BRIGTHNESS: {
                    _led_set_brightness(led, led->_commands[led->_current_command_ix].brightness.value);
                    break;
                }
                case COMMAND_REPEAT: {
                    LEDCommand* cmd = &led->_commands[led->_current_command_ix];
                    if (cmd->repeat.number == 0 || cmd->repeat.counter++ < cmd->repeat.number) {
                        led->_current_command_ix = cmd->repeat.index;
                    } else {
                        // else, go on with the next command...
                        cmd->repeat.counter = 0; // ...but set the counter back which is needed if we have nested repeats
                    }
                    break;
                }
                case COMMAND_CALLBACK: {
                    led->_commands[led->_current_command_ix].callback._callback(led);
                }
            }
        }
    } while (1);
}

void led_start_program(LED* led) {
    _next_command(led);
}

void led_step(LED* led) {
    LEDCommand* command = &(led->_commands[led->_current_command_ix].cmd);
    ++(led->_step_count);
    switch (command->cmd) {
        case COMMAND_HOLD: {
            if (command->hold.duration == led->_step_count) {   // if we hold "long enough", go to the next command
                _next_command(led);
            };                                                  // otherwise, do nothing
            break;
        }
        case COMMAND_DIM_LINEAR: {
            if (led->_step_count == 1) {
                    command->dim_linear._start_brightness = led->_current_brightness;
            }
            if (command->dim_linear._ramp_duration == 0 || led->_step_count == command->dim_linear._ramp_duration) {
                _led_set_brightness(led, command->dim_linear._target_brightness);   // we reached the final step, set the final brightness...
                _next_command(led);                                                 // ... and go to the next command
            } else {
                  float a = command->dim_linear._target_brightness - command->dim_linear._start_brightness;
                  float b = (float)command->dim_linear._ramp_duration;
                  int8_t c = (int8_t)(
                       (a / b) * led->_step_count + 0.5 + command->dim_linear._start_brightness
                  );
                  _led_set_brightness(led, c);
            }
            break;
        }
    }
}

void led_set_brightness(LED* led, uint8_t brightness) {
    led_program_reset(led);
    _led_set_brightness(led, brightness);
}
