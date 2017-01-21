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

#ifndef HARDWARE_H
#define HARDWARE_H

// events from the hardware module, communicated by the hw_events_queue
#define HW__FIRE_ON 1
#define HW__FIRE_OFF 2
#define HW__BATTERY_MEASURE 3       // battery voltage in second byte of queue element

#include <avr/io.h>
#include "queue.h"

extern Queue hw_event_queue;

uint8_t hardware_init(void);

void hardware_step(void);

void hardware_fire_on(void);

void hardware_fire_off(void);

void do_battery_measurement(void);

void hardware_power_down(void);

void hardware_power_up(void);


#endif // HARDWARE_H

