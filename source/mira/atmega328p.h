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

#ifndef ATMEGA328P_H
#define ATMEGA328P_H

#include <avr/io.h>

/**************************************************
 * UI input
 *************************************************/
#define HWMAP_UI_SWITCH_DDR      DDRB
#define HWMAP_UI_SWITCH_PORT     PORTB
#define HWMAP_UI_SWITCH_PIN      PINB
#define HWMAP_UI_SWITCH_0_IX     1

/**************************************************
 * UI output
 *************************************************/
#define HWMAP_UI_OUTPIN_DDR     DDRB
#define HWMAP_UI_OUTPIN_PORT    PORTB
#define HWMAP_UI_OUTPIN_0_IX    2


/**************************************************
 * UART
 *************************************************/
// Baud rate for the UART, should be externalized somehow later on
#define BAUD 4800UL
// The UART's char buffer register (delivers in received character inside the ISR and takes a charater to write out)
#define CTRLMAP_UART_CHARBUFFER     UDR0
// Command that waits until the charbuffer is empty and can be used to send a single character
#define MCUMAP_UART_CMD_AWAIT_EMPTY_CHARBUFFER  while ( !( UCSR0A & (1<<UDRE0)) );
// Function that inititializes the UART with 8 data and one stop bit.
uint8_t uart_init_8_plus_1(void);

/**************************************************
 * Hardware
 *************************************************/
// Data register used to control the fire MOSFET
#define HWMAP_HW_FIRE_DDR        DDRB
// Corresponding port
#define HWMAP_HW_FIRE_PORT       PORTB
// Index of the pin used to control the fire MOSFET
#define HWMAP_HW_FIRE_BIT_IX     0

#endif // ATMEGA328P_H
