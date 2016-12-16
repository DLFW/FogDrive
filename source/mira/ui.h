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

#ifndef UI_H
#define UI_H
#include <avr/io.h>
#include "queue.h"

#define UI__FIRE_BUTTON_PRESSED 1
#define UI__FIRE_BUTTON_RELEASED 2
#define UI__50MS_PULSE 3

// A queue that transports user interface inputs (low level command from the user) to the logic module
extern Queue ui_event_queue;

uint8_t ui_init(void);

void ui_input_step(void);

void ui_fire_is_on(void);

void ui_fire_is_off(void);

#endif // UI_H
