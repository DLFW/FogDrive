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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "queue.h"
#include "deviface.h"
#include MCUHEADER

volatile uint8_t uart_str_complete = 0;
volatile uint8_t uart_str_count = 0;
volatile char uart_string[UART_MAXSTRLEN + 1] = "";


//Queue character_output_queue;
//QueueElement character_output_queue_array[30];

void deviface_init(void) {
    uart_init_8_plus_1();
}

void deviface_putchar( unsigned char data ) {
    // Wait for empty transmit buffer (mcu specific macro)
    MCUMAP_UART_CMD_AWAIT_EMPTY_CHARBUFFER;
    // Put data into buffer (mcu specific macro), sends the data
    CTRLMAP_UART_CHARBUFFER = data;
}

void deviface_putstring (char* s) {
    while (*s) {
        deviface_putchar(*s);
        s++;
    }
}

void deviface_putlineend(void) {
    deviface_putstring("\r\n");
}

void deviface_putline (char* s) {
    deviface_putstring(s);
    deviface_putlineend();
}

void deviface_put_uint8(uint8_t v) {
    char value_s[4];
    utoa(v,value_s,10);
    deviface_putstring(value_s);
}

void deviface_put_uint16(uint16_t v) {
    char value_s[6];
    utoa(v,value_s,10);
    deviface_putstring(value_s);
}

ISR(USART_RX_vect) {
  unsigned char nextChar;
  nextChar = CTRLMAP_UART_CHARBUFFER;
  if( uart_str_complete == 0 ) {
    if( nextChar != '\n' &&
        nextChar != '\r' &&
        uart_str_count < UART_MAXSTRLEN
    ) {
        uart_string[uart_str_count] = nextChar;
        uart_str_count++;
        deviface_putchar(nextChar);            // echo the character
    } else {
        uart_string[uart_str_count] = '\0';
        uart_str_count = 0;
        uart_str_complete = 1;
        deviface_putchar('\r');
        deviface_putchar('\n');
    }
  }
}
