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

#include "hardware.h"
#include "deviface.h"
#include "queue.h"
#include MCUHEADER

#define CTRLMAP_FIRE_BIT_MASK   (1 << HWMAP_HW_FIRE_BIT_IX)
#define ALL_OUT_BITS            CTRLMAP_FIRE_BIT_MASK


// state machine: battery voltage measurement (bvm)
#define SMS_BVM_IDLE 0
#define SMS_BVM_MEASURING 1
#define SMS_BVM_CALCULATING 4
uint8_t sm_bvm_status = SMS_BVM_IDLE;

uint8_t make_measurement = 0;

#define bvm_smoothing 10
uint16_t battery_voltage_adcs[bvm_smoothing];
uint8_t battery_voltage_adc_ix = 0;

Queue hw_event_queue;
QueueElement hw_event_queue_elements[5];


uint8_t hardware_init(void) {
    // configure the fire pin as output by setting the related direction bit to 1
    HWMAP_HW_FIRE_DDR |= CTRLMAP_FIRE_BIT_MASK;
    // initialize the fire pin with 0 (fire off)
    HWMAP_HW_FIRE_PORT &= ~CTRLMAP_FIRE_BIT_MASK;
    // set up the hardware event queue
    queue_initialize(&hw_event_queue, 5, hw_event_queue_elements);



    ADMUX |= (1<<REFS0);                         //voltage reference selction: AREF, Internal Vref turned off
    ADMUX |= (1<<MUX3) | (1<<MUX2) | (1<<MUX1);  //input voltage selection: 1.1V (V_BG)
    ADCSRA |= (1<<ADEN);                         //activate ADC


    return 0;
}

void hardware_fire_on(void) {
    deviface_putline(">Fire On");
    HWMAP_HW_FIRE_PORT = HWMAP_HW_FIRE_PORT | CTRLMAP_FIRE_BIT_MASK;
    QueueElement* e = queue_get_write_element(&hw_event_queue);
    e->bytes.a = HW__FIRE_ON;
}

void hardware_fire_off(void) {
    deviface_putline(">Fire Off");
    HWMAP_HW_FIRE_PORT = HWMAP_HW_FIRE_PORT & ~CTRLMAP_FIRE_BIT_MASK;
    QueueElement* e = queue_get_write_element(&hw_event_queue);
    e->bytes.a = HW__FIRE_OFF;
}

void sm_bvm(void) {
    switch (sm_bvm_status) {
        case SMS_BVM_IDLE: {
            if (make_measurement == 1) {
                ADCSRA |= (1<<ADSC);// start
                while(ADCSRA & (1<<ADSC)); //await
                uint8_t adc_low = ADCL;
                uint8_t adc_high = ADCH;
                uint16_t adc_result = (adc_high<<8) | adc_low; //Gesamtergebniss der ADC-Messung
                uint16_t vcc = 1125300L / adc_result;
                deviface_putint16(vcc);
                deviface_putlineend();
                uint8_t result = vcc / 20;

                QueueElement* e = queue_get_write_element(&hw_event_queue);
                e->bytes.a = HW__BATTERY_MEASURE;
                e->bytes.b = result;
                sm_bvm_status = SMS_BVM_IDLE;
                make_measurement = 0;
            }
            break;
        }
    }
}

void hardware_step(void) {
    sm_bvm();
}

void do_battery_measurement(void) {
    make_measurement = 1;
}
