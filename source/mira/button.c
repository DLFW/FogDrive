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

#include "button.h"

// BuTton State Machine States
#define BTSMS_IDLE          0   // button released
#define BTSMS_CLICK_DOWN    1   // button pressed and within click duration
#define BTSMS_CLICK_UP      2   // button released after click, release state is so short that another click of the same click sequence could happen
#define BTSMS_PRESSED       3   // button fully pressed, not a click


void button_init(Button* button) {
    queue_initialize(&(button->button_event_queue), 3, &(button->_button_event_queue_elements));
    button->_click_press_duration = 3;
    button->_click_release_duration = 3;
    button->_state = BTSMS_IDLE;
    button->_local_step_count = 0;
    button->_click_count = 0;
}

void button_pressed(Button* button) {
    switch (button->_state) {
        case BTSMS_IDLE: {
                button->_state = BTSMS_CLICK_DOWN;  // first click or start of pressing
                button->_click_count = 0;
                button->_local_step_count = 0;
                break;
        }
        case BTSMS_CLICK_DOWN: {
                button->_state = BTSMS_IDLE;        // should never happen, two pressed events without a release; go to idle for safety...
                break;
        }
        case BTSMS_CLICK_UP: {
                button->_local_step_count = 0;
                button->_state = BTSMS_CLICK_DOWN;  // next click started (or maybe refusal of clicking sequence by pressing too long later)
                break;
        }
        case BTSMS_PRESSED: {
                button->_state = BTSMS_IDLE;        // should never happen, two pressed events without a release; go to idle for safety...
                break;
        }
    }
}

void button_released(Button* button) {
    switch (button->_state) {
        case BTSMS_IDLE: {
                break;                              // should never happen (maybe due to init race), just stay in idle...
        }
        case BTSMS_CLICK_DOWN: {
                button->_click_count++;             // click happened
                button->_state = BTSMS_CLICK_UP;
                button->_local_step_count = 0;
                break;
        }
        case BTSMS_CLICK_UP: {
                button->_state = BTSMS_IDLE;        // should never happen, two released events without a pressed; go to idle for safety...
                break;
        }
        case BTSMS_PRESSED: {                       // button released after beeing "pressed": emmit released event
                QueueElement* e = queue_get_write_element(&(button->button_event_queue));
                e->bytes.a = BUTTON_EVENT_RELEASED;
                e->bytes.b = 0;
                button->_state = BTSMS_IDLE;
                break;
        }
    }
}

void button_step(Button* button){
    switch (button->_state) {
        case BTSMS_IDLE: {
                break;                              // nothing to do
        }
        case BTSMS_CLICK_DOWN: {
                button->_local_step_count++;
                if (button->_local_step_count > button->_click_press_duration) {        // button fully pressed: emmit pressed event
                    QueueElement* e = queue_get_write_element(&(button->button_event_queue));
                    e->bytes.a = BUTTON_EVENT_PRESSED;
                    e->bytes.b = 0;
                    button->_state = BTSMS_PRESSED;
                }
                break;
        }
        case BTSMS_CLICK_UP: {
                button->_local_step_count++;
                if (button->_local_step_count > button->_click_release_duration) {     // click sequence done
                    button->_state = BTSMS_IDLE;
                    QueueElement* e = queue_get_write_element(&(button->button_event_queue));
                    e->bytes.a = BUTTON_EVENT_CLICK;
                    e->bytes.b = button->_click_count;
                }
                break;
        }
        case BTSMS_PRESSED: {
                break;                              // nothing to do, press time limitation can be implemented here
        }
    }
}
