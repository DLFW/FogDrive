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

#include "attiny45.h"

void uart_init_8_plus_1(void) {
    // No UART for the Tiny
}

void ui_timer_init_10ms_overflow(void) {
    TCCR1 = (1<<CS10)|(1<<CS13);  // prescaler 256
    TIMSK = (1<<TOIE1);  // enable overflow interrupt
    HWMAP_UI_TIMER_CMD_REINIT_FOR_10ms;
}

void mcu_init_ui_double_compare_timer_for_fast_pwm_1ms(void) {
    //TODO: it's only 1ms with 1MHz frequency: refactor name or function
    DDRB |= (1<<1);                                   // Set the pin of PWM channel B as output
    TCCR0A = (1<<WGM01) | (1<<WGM00) | (1<<COM0A1) | (1<<COM0A0);   // Fast PWM, single slope, count from 0 to 255 (not only till compare), inverting
    TCCR0B = (1<<CS00);                               // Internal clock, no prescaling
}

void mcu__enabled_one_adc_with_vcc_reference_and_vgb_input(void) {
    // REFS0+REFS1 left to 00 in order to use AV_CC as reference
    ADMUX |= (1<<MUX3) | (1<<MUX2);  //input voltage selection: 1.1V (V_BG)
    ADCSRA |= (1<<ADEN);                         //activate ADC
}
