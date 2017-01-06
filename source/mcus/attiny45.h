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
#define HWMAP_UI_SWITCH_0_IX     2

/**************************************************
 * UI output
 *************************************************/
#define HWMAP_UI_OUTPIN_DDR     DDRB
#define HWMAP_UI_OUTPIN_PORT    PORTB
#define HWMAP_UI_OUTPIN_0_IX    1

/**************************************************
 * UI timer
 *************************************************/
#define HWMAP_UI_TIMER_ISR     TIMER1_OVF_vect
#define HWMAP_UI_TIMER_CMD_REINIT_FOR_10ms TCNT1 = (256-(F_CPU / 256 * 10e-3 + 0.5));
#define MCU_UI_PWM_A_CR OCR0A
// Function that initializes the UI timers and PWMs
void ui_timer_init_10ms_overflow(void);
void mcu_init_ui_double_compare_timer_for_fast_pwm_1ms(void);

/**************************************************
 * UART
 *************************************************/
// No UART for the Tiny
void uart_init_8_plus_1(void);

/**************************************************
 * Hardware fire pin
 *************************************************/
// Data register used to control the fire MOSFET
#define HWMAP_HW_FIRE_DDR        DDRB
// Corresponding port
#define HWMAP_HW_FIRE_PORT       PORTB
// Index of the pin used to control the fire MOSFET
#define HWMAP_HW_FIRE_BIT_IX     3

/**************************************************
 * Hardware ADC
 *************************************************/
void mcu__enabled_one_adc_with_vcc_reference_and_vgb_input(void);
#define MCU__START_SINGLE_ADC_CONVERSION ADCSRA |= (1<<ADSC)
#define MCU__SINGLE_ADC_CONVERSION_IS_DONE ! (ADCSRA & (1<<ADSC))

#endif // ATMEGA328P_H

