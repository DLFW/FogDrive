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

#ifndef BUTTON_H
#define BUTTON_H

#include "queue.h"

#define BUTTON_EVENT_RELEASED   0
#define BUTTON_EVENT_PRESSED    1
#define BUTTON_EVENT_CLICK      2 // number of clicks in second byte

typedef struct {
    Queue button_event_queue;
    QueueElement _button_event_queue_elements[3];
    uint8_t _state;
    uint8_t _click_press_duration;
    uint8_t _click_release_duration;
    uint8_t _local_step_count;
    uint8_t _click_count;
} Button;

void button_step(Button* button);

void button_init(Button* button);

void button_pressed(Button* button);

void button_released(Button* button);

#endif // BUTTON_H
