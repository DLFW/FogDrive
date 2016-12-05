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

#include "queue.h"

QueueElement* queue_get_write_element(Queue* queue) {
    QueueElement* result = (queue->queueElementArray + queue->write_index++);
    if (queue->write_index == queue->number_of_elements) {
        queue->write_index = 0;
    }
    return result;
}

QueueElement* queue_get_read_element(Queue* queue) {
    if (queue->read_index == queue->write_index) {
        return 0;
    }
    QueueElement* result = (queue->queueElementArray + queue->read_index++);
    if (queue->read_index == queue->number_of_elements) {
        queue->read_index = 0;
    }
    return result;
}

void queue_initialize(Queue *queue, uint8_t number_of_elements, QueueElement *queue_element_array) {
    queue->read_index = 0;
    queue->write_index = 0;
    queue->number_of_elements = number_of_elements;
    queue->queueElementArray = queue_element_array;
}

