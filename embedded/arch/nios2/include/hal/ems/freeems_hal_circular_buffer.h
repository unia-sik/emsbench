/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * $Id: freeems_hal_circular_buffer.h 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Implementation of a circular buffer needed for performance logging on
 *        nios2 architecture.
 * @file freeems_hal_circular_buffer.h
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#ifndef FILE_FREEEMS_HAL_CIRCULAR_BUFFER_H_SEEN
#define FILE_FREEEMS_HAL_CIRCULAR_BUFFER_H_SEEN

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <driver/board.h>
#include <arch/nios2/io.h>
#include <hal/ems/hal_irq.h>


/*
	1K = 1024,
	2K = 2048,
	4K = 4096,
	65K = 65536,
	4M = 4194304,
	8M = 8388608,
	16M = 16777216
};*/

/**
 * @autorh Andreas Meixner
 * @brief Defines the size of the circular buffers in bytes.
 * This value defines how big the the buffers ar in bytes. It has to be a power
 * of 2 e.g. 1024 (1kb), 4096 (4kb), 4194304 (4M), ....
 * This value may be changed.
 */
#define BUFFER_SIZE 4194304
/**
 * @autorh Andreas Meixner
 * @brief Defines the bitmask for fast modula calculations.
 * This value always has to be BUFFER_SIZE -1. It is used to perform fast modulo
 * calculations.
 * Because BUFFER_SIZE has to be a power of 2 the calculation
 *  (x % BUFFER_SIZE) can be substituted by (x & (BUFFER_SIZE -1)) which is much
 * faster.
 */
#define BUFFER_MODULO_FACTOR (BUFFER_SIZE - 1)

/**
 * @autorh Andreas Meixner
 * @brief Defines a circular buffer
 * This sctruct defines a circular buffer of size BUFFER_SIZE.
 */
typedef struct {
  /**
   * @autorh Andreas Meixner
   * Points to the index where to write the next byte.
   */
  uint32_t head;
  /**
   * @autorh Andreas Meixner
   * Points to the index where to read the next byte.
   * If head == tail the buffer is empty.
   */
  uint32_t tail;
  /**
   * @autorh Andreas Meixner
   * The byte array where the buffered data is stored.
   */
  uint8_t buffer[BUFFER_SIZE];
} circularbuffer_t;

/**
 * @autorh Andreas Meixner
 * @brief Return value when everything has worked.
 */
#define CIRCULAR_BUFFER_OK 0
/**
 * @autorh Andreas Meixner
 * @brief Return value when atempting to read from an emty buffer.
 */
#define CIRCULAR_BUFFER_NO_DATA_AVAILABLE 1
/**
 * @autorh Andreas Meixner
 * @brief Return value when atempting to write to a full buffer.
 */
#define CIRCULAR_BUFFER_FULL 2

/**
 * @autorh Andreas Meixner
 * @brief Checks how many bytes are in the buffer.
 * @param buffer A pointer to the buffer to check.
 * @return the number of bytes ready to read from the buffer.
 */
static inline uint32_t circular_buffer_available_data(
  circularbuffer_t* buffer) {
  if (buffer->tail <= buffer->head) {
    return buffer->head - buffer->tail;
  }
  else {
    return BUFFER_SIZE - (buffer->tail - buffer->head);
  }
}

/**
 * @autorh Andreas Meixner
 * @brief Reads the next byte from the buffer.
 * @param buffer A pointer to the buffer to read from.
 * @param outData A pointer to the variable where the read byte will be stored.
 * @return CIRCULAR_BUFFER_OK if reading was successfull or
 *         CIRCULAR_BUFFER_NO_DATA_AVAILABLE if the buffer is empty
 */
static inline uint8_t circular_buffer_read(circularbuffer_t* buffer,
    uint8_t* outData) {
  //if data is available read one byte and advance the tail pointer by one
  uint8_t ret = CIRCULAR_BUFFER_OK;
  if (circular_buffer_available_data(buffer) > 0) {
    *outData = buffer->buffer[buffer->tail];
    buffer->tail = (buffer->tail + 1) & BUFFER_MODULO_FACTOR;
  }
  else {
    ret = CIRCULAR_BUFFER_NO_DATA_AVAILABLE;
  }
  return ret;
}

/**
 * @autorh Andreas Meixner
 * @brief writes one byte to the buffer.
 * @param buffer A pointer to the buffer to rite to.
 * @param value the value to write to the buffer.
 * @return CIRCULAR_BUFFER_OK if writing was successfull or
 *         CIRCULAR_BUFFER_NO_DATA_AVAILABLE if the buffer is empty
 */
static inline uint8_t circular_buffer_write(circularbuffer_t* buffer,
    uint8_t value) {
  uint8_t ret = CIRCULAR_BUFFER_OK;
  // write to the buffer
  buffer->buffer[buffer->head] = value;
  // advance head to the next position
  // The modulo calculation is replaced by this & operator.
  // This only works because BUFFER_SIZE is a power of 2 and
  // BUFFER_MODULO_FACTOR is BUFFER_SIZE-1.
  buffer->head = (buffer->head + 1) & BUFFER_MODULO_FACTOR;
  //if the buffer is full now advance tail by one
  if (buffer->head == buffer->tail) {
    buffer->tail = (buffer->tail + 1) & BUFFER_MODULO_FACTOR;
    ret = CIRCULAR_BUFFER_FULL;
  }
  else {
    ret = CIRCULAR_BUFFER_OK;
  }
  return ret;
}

/**
 * @autorh Andreas Meixner
 * @brief Writes a given number of bytes to the given circular buffer.
 */
static inline uint8_t circular_buffer_write_all(circularbuffer_t *buffer,
    uint8_t *values, uint32_t length) {
  uint8_t retVal = CIRCULAR_BUFFER_OK;
  int i = 0;
  for (i = 0; i < length; i++) {
    retVal = circular_buffer_write(buffer, values[i]);
  }
  return retVal;
}

/**
 * @autorh Andreas Meixner
 * @brief Writes a string to the given circular buffer.
 */
static inline uint8_t circular_buffer_write_string(circularbuffer_t *buffer,
    uint8_t* string) {
  uint8_t retVal = CIRCULAR_BUFFER_OK;
  uint32_t index = 0;
  while (string[index] != 0) {
    retVal = circular_buffer_write(buffer, string[index]);
    index++;
  }
  return retVal;
}

/**
 * @autorh Andreas Meixner
 * @brief outputs the next byte from the cricular buffer to the uart.
 * This function takes the next byte from the giver circular buffer and writes
 * it to the uart output. Only call this from within the main loop.
 * @param buffer The buffer from which to read.
 * @return Returns the written byte, or 0 if nothing was done.
 */
static inline int32_t output_next_from_buffer(circularbuffer_t *buffer) {

  uint8_t nextValue = 0;
  // do not exectute any interrupts while reading the next byte,
  // otherwise the circular buffer could be corurpted.
  ATOMIC_START();
  uint8_t result = circular_buffer_read(buffer, &nextValue);
  ATOMIC_END();
  //if buffer is not empty write the next byte, else do nothing
  if (result == CIRCULAR_BUFFER_OK) {
    while (!(htonl(IORD8(A_UART, UART_ST)) & UART_ST_TRDY))
      ;
    IOWR8(A_UART, UART_TX, nextValue);
  }
  return (int32_t) nextValue;
}
#endif /* FILE_FREEEMS_HAL_CIRCULAR_BUFFER_H_SEEN */
