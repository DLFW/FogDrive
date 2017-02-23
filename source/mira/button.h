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

/** \defgroup button Button
*   \brief Abstraction for a button switch to generate press, release and click events.
*
*   This module’s API consists of a struct type definition (#Button) and a few functions which all takes a reference
*   to a #Button variable as first argument. This is kind of object oriented, where the struct keeps the buttons state
*   and the methods act always exclusively on the struct.
*
*   A #Button struct is first initialized by the use of button_init(Button* button). During the buttons runtime,
*   the function void button_step(Button* button) must be called cyclically. Furthermore, each time the (physical)
*   button is pressed (debounced, if necessary), button_pressed(Button* button). If the (physical) button is released,
*   button_released(Button* button) must be invoked. So, this module doesn't encapsulate the hardware part since it is
*   highly application dependent.
*
*   As a result from the mentioned inputs (cyclical step and pressed and released events), this button logic generate
*   click, pressed and released events where pressed is only emitted if the button was pressed long enough to “be not
*   a click”.
*
*   The output events must be actively taken from a \ref queue. The events are decoded as integers, defined as preprocessor
*   definitions \e BUTTON_EVENT_x.
*
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "queue.h"

#define BUTTON_EVENT_RELEASED   0
#define BUTTON_EVENT_PRESSED    1
#define BUTTON_EVENT_CLICK      2 // number of clicks in second byte
#define BUTTON_EVENT_TIMEOUT    3
#define BUTTON_EVENT_RELEASED_TIMEOUT    4

typedef struct {
    Queue button_event_queue;
    QueueElement _button_event_queue_elements[3];
    uint8_t _state;
    uint8_t _click_press_duration;
    uint8_t _click_release_duration;
    uint8_t _local_step_count;
    uint8_t _click_count;
    uint8_t _press_timeout;
} Button;

/**
 * \brief Must be called cyclically for each button instance.
 *
 * This function must be called cyclically and is used by the button logic for the timing which is
 * important for the detection click events.
 *
 * \param button the button instance
 */
void button_step(Button* button);

void button_init(Button* button);

void button_pressed(Button* button);

void button_released(Button* button);

#endif // BUTTON_H
