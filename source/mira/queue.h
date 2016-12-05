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

#ifndef QUEUE_H
#define QUEUE_H

#include <avr/io.h>

typedef union {
  struct {
      uint8_t a;
      uint8_t b;
  } bytes;
  uint16_t word;
} QueueElement;


typedef struct {
    QueueElement *queueElementArray;
    uint8_t number_of_elements;
    uint8_t read_index;
    uint8_t write_index;
} Queue;

QueueElement* queue_get_write_element(Queue *queue);

QueueElement* queue_get_read_element(Queue *queue);

void queue_initialize(Queue *queue, uint8_t number_of_elements, QueueElement *queue_element_array);

#endif // QUEUE_H
