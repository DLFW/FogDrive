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

#ifndef LOGIC_H
#define LOGIC_H

#include <avr/io.h>
#include "queue.h"

#define BATTERY_VOLTAGE_LOW_VALUE 35
#define BATTERY_VOLTAGE_VERY_LOW_VALUE 32
#define BATTERY_VOLTAGE_STOP_VALUE 29

extern uint8_t battery_voltage_under_load;
extern uint8_t global_state;

#define GS_ON        2  // device is on
#define GS_AWAKENING 3  // device just left deep sleep because of interrupt but the on-command from the UI is not received yet


uint8_t logic_init(void);
void logic_loop (void);



#endif // LOGIC_H
