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
 * $Id: cr.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file cr.c
 * @brief Reimplementation of cyclereader
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include "cr.h"

#include <stdlib.h>

/**
 * @brief Size of read buffer (also used for extension of buffer)
 */
#define NBUFF 256

/**
 * @brief Initial size of driving cycle buffer (also used for extension)
 */
#define OEXT 32


cycle_t* read_cycle(FILE *file) {
  if (file == NULL) {
    return NULL;
  }

  cycle_t *cycle = malloc(sizeof(cycle_t));
  cycle->operations = calloc(OEXT, sizeof(operation_t));
  cycle->n_entries = OEXT;
  cycle->used_entries = 0;

  // now run through file
  char *buffer = malloc(NBUFF);
  size_t buf_size = NBUFF;

  buffer[buf_size - 1] = 0xff; // canary
  while (fgets(buffer, buf_size, file) == buffer) {
    while (buffer[buf_size - 1] != (char)0xff) {
      // The canary got overwritten, so the line did not yet fit into the buffer
      // extend the buffer and read more bytes
      printf("Need to extend buffer, last byte is %x\n", buffer[buf_size - 1]);
      buffer = realloc(buffer, buf_size + NBUFF);
      char *old_end = buffer + buf_size;
      buf_size += NBUFF;
      buffer[buf_size - 1] = 0xff;
      if (fgets(old_end, NBUFF, file) != old_end) {
        fprintf(stderr, "Reading extended line failed, exiting!\n");
        abort();
      }
    }

    char *str = buffer;

    // ignore whitespaces
    while (*str == ' ' || *str == '\t') {
      str++;
    }
    // ignore comments and empty lines
    if (*str == '#' || *str == '\n') {
      // directly jump to next iteration
      buffer[buf_size-1] = 0xff;
      continue;
    }

    // # Acc. ; SpeedS ; SpeedE ; Dur. ; Gear

    char *conv_start = str;
    while (*str != ';') {
      str++;
    }
    char *conv_end;
    double acc = strtod(conv_start, &conv_end);

    while (*str == ';' || *str == ' ') {
      ++str;
    }

    conv_start = str;
    while (*str != ';') {
      str++;
    }
    long int speed_start = strtol(conv_start, &conv_end, 10);

    while (*str == ';' || *str == ' ') {
      ++str;
    }

    conv_start = str;
    while (*str != ';') {
      str++;
    }
    long int speed_end = strtol(conv_start, &conv_end, 10);

    while (*str == ';' || *str == ' ') {
      ++str;
    }

    conv_start = str;
    while (*str != ';') {
      str++;
    }
    long int duration = strtol(conv_start, &conv_end, 10);

    while (*str == ';' || *str == ' ') {
      ++str;
    }

    conv_start = str;

    long int gear = strtol(conv_start, &conv_end, 10);

    //printf("Acc: %f vs: %ld ve: %ld dur: %ld gear: %ld\n",
    //	   acc, speed_start, speed_end, duration, gear);

    if (cycle->used_entries == cycle->n_entries) {
      // extend
      cycle->operations = realloc(cycle->operations, (cycle->n_entries + OEXT) * sizeof(operation_t));
      cycle->n_entries += OEXT;
    }
    operation_t *op = &cycle->operations[cycle->used_entries++];
    op->acceleration = acc;
    op->speed_start = speed_start;
    op->speed_end = speed_end;
    op->duration = duration;
    op->gear = gear;

    // prepare next iteration
    buffer[buf_size-1] = 0xff;
  }

  free(buffer);
  return cycle;
}


void free_cycle(cycle_t* cycle) {
  if (cycle == NULL) {
    return;
  }
  free(cycle->operations);
  free(cycle);
}
