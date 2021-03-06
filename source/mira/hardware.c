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

#include "logic.h"
#include "hardware.h"
#include "queue.h"
#include MCUHEADER
#ifdef UART_ENABLED
    #include "deviface.h"
#endif

#define CTRLMAP_FIRE_BIT_MASK   (1 << HWMAP_HW_FIRE_BIT_IX)
#define ALL_OUT_BITS            CTRLMAP_FIRE_BIT_MASK


// state machine: battery voltage measurement (bvm)
#define SMS_BVM_IDLE 0
#define SMS_BVM_START_MEASUREMENT 1
#define SMS_BVM_MEASURING 3
#define SMS_BVM_CALCULATING 4
uint8_t sm_bvm_status = SMS_BVM_IDLE;

uint8_t make_measurement = 0;

#define AVR_INTERNAL_REFERENCE_VOLTAGE 1100000L     // in 10^(-6) V
#define BVM_SMOOTHING 4
uint16_t battery_voltage_sum = 0;
uint8_t battery_voltage_values_ix = 0;

Queue hw_event_queue;
QueueElement hw_event_queue_elements[5];


uint8_t hardware_init(void) {
    // configure the fire pin as output by setting the related direction bit to 1
    HWMAP_HW_FIRE_DDR |= CTRLMAP_FIRE_BIT_MASK;
    // initialize the fire pin with 0 (fire off)
    HWMAP_HW_FIRE_PORT &= ~CTRLMAP_FIRE_BIT_MASK;
    // set up the hardware event queue
    queue_initialize(&hw_event_queue, 5, hw_event_queue_elements);
    // enable the ADC which uses V_CC as reference and the constant voltage V_GB as input
    mcu__enabled_one_adc_with_vcc_reference_and_vgb_input();

    return 0;
}

void hardware_fire_on(void) {
    #ifdef UART_ENABLED
    deviface_putline(">Fire On");
    #endif
    HWMAP_HW_FIRE_PORT = HWMAP_HW_FIRE_PORT | CTRLMAP_FIRE_BIT_MASK;
    QueueElement* e = queue_get_write_element(&hw_event_queue);
    e->bytes.a = HW__FIRE_ON;
}

void hardware_fire_off(void) {
    #ifdef UART_ENABLED
    deviface_putline(">Fire Off");
    #endif
    HWMAP_HW_FIRE_PORT = HWMAP_HW_FIRE_PORT & ~CTRLMAP_FIRE_BIT_MASK;
    QueueElement* e = queue_get_write_element(&hw_event_queue);
    e->bytes.a = HW__FIRE_OFF;
}

void hardware_power_down() {
    sm_bvm_status = SMS_BVM_IDLE;       // stop the battery voltage measure in case it's running
    queue_clear(&hw_event_queue);        // clear unprocessed events if there are some
}

void hardware_power_up() {
    // nothing to do
}

void sm_bvm(void) {
    switch (sm_bvm_status) {
        case SMS_BVM_IDLE: {
            if (make_measurement == 1) {
                MCU__START_SINGLE_ADC_CONVERSION;
                battery_voltage_values_ix = 0;
                sm_bvm_status = SMS_BVM_MEASURING;
                make_measurement = 0;
                battery_voltage_sum = 0;
            }
            break;
        }
        case SMS_BVM_MEASURING: {
            if (MCU__SINGLE_ADC_CONVERSION_IS_DONE) {
                // measurement done
                uint8_t adc_low = ADCL;     // get the low byte of the measured value
                uint8_t adc_high = ADCH;    // get the high byte of the measured value
                uint16_t adc_result = (adc_high<<8) | adc_low; //put the 16 bit measurement result together
                uint16_t vcc =  AVR_INTERNAL_REFERENCE_VOLTAGE / adc_result;   //turn the raw adc value into milli volt
                battery_voltage_sum += vcc;
                if (++battery_voltage_values_ix == BVM_SMOOTHING) {
                    sm_bvm_status = SMS_BVM_CALCULATING;
                } else {
                   MCU__START_SINGLE_ADC_CONVERSION;            // start another measurement, stay in this state...
                }
            }
            break;
        }
        case SMS_BVM_CALCULATING: {
            // and put the final result into the event queue
            QueueElement* e = queue_get_write_element(&hw_event_queue);
            e->bytes.a = HW__BATTERY_MEASURE;
            e->bytes.b = (uint8_t) (battery_voltage_sum / (BVM_SMOOTHING * 100));
            // go back to the idle state to wait for the next measurement instruction
            sm_bvm_status = SMS_BVM_IDLE;
            break;
        }
    }
}

void hardware_step(void) {
    if (~ global_state && GS_AWAKENING) {
        // if the device is not jus awakening (but really switched on)
        sm_bvm();
    }
}

void do_battery_measurement(void) {
    make_measurement = 1;
}
