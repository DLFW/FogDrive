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

#include "atmega328p.h"


// Baud rate related calculation
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)      // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
#error Systematic error of baud rate to high (> 1%). Aborting.
#endif

void uart_init_8_plus_1(void) {
    UBRR0H = UBRR_VAL >> 8;
    UBRR0L = UBRR_VAL & 0xFF;
    UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);  // enable send, enable receive, enable receive interrupt
    UCSR0C = (1<<UCSZ01)| (1<<UCSZ00)|(1<<UCPOL0);    // asynch 8 bit + 1 stop bit
}

void ui_timer_init_10ms_overflow(void) {
    TCCR2B = (1<<CS22)|(1<<CS21);  // prescaler 256
    TIMSK2 = (1<<TOIE2);
    HWMAP_UI_TIMER_CMD_REINIT_FOR_10ms;
}

void mcu_init_ui_double_compare_timer_for_fast_pwm_1ms(void) {
    //TODO: it's only 1ms with 1MHz frequency: refactor name or function
    DDRD |= (1<<6);                                   // Set the PIN of PWM channel A as output
    TCCR0A = (1<<WGM01) | (1<<WGM00) | (1<<COM0A1);   // Fast PWM, single slope, count from 0 to 255 (not only till compare), non-inverting
    TCCR0B = (1<<CS00);                               // Internal clock, no prescaling
}
