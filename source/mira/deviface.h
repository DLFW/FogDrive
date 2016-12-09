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

#ifndef DEVIFACE_H
#define DEVIFACE_H

#include <avr/io.h>

#define UART_MAXSTRLEN 10

extern volatile uint8_t uart_str_complete;
extern volatile uint8_t uart_str_count;
extern volatile char uart_string[UART_MAXSTRLEN + 1];

void deviface_init(void);

void deviface_put_uint16(uint16_t v);

void deviface_put_uint8(uint8_t v);

void deviface_putlineend(void);

void deviface_putstring(char* s);

void deviface_putline(char* s);

void deviface_putchar( unsigned char data );

#endif // DEVIFACE_H
