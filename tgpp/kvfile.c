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
 * $Id: kvfile.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file kvfile.c
 * @brief Provides a very basic key/value map
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#define _GNU_SOURCE
#include "kvfile.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define NBUFF 256
#define PEXT 32


typedef struct {
  char *key;
  char *value;
} kv_pair_t;

struct _kv_file {
  size_t n_pairs;
  size_t used_pairs;
  kv_pair_t **pairs;
};


/**
 * @brief Find an entry pair in the key-value map
 * @param kv The key-value file
 * @param key The key of the pair
 * @return A pointer to the pair, or NULL if none was found
 */
static const kv_pair_t* kv_find_pair(const kv_file_t *kv, const char *key);


int kv_read_file(kv_file_t** kvp, FILE* file) {
  kv_file_t *kv = malloc(sizeof(kv_file_t));

  kv->pairs = malloc(PEXT * sizeof(kv_pair_t*));
  memset(kv->pairs, 0, PEXT * sizeof(kv_pair_t*));

  kv->n_pairs = PEXT;
  kv->used_pairs = 0;

  // now run through file
  char *buffer = malloc(NBUFF);
  size_t buf_size = NBUFF;

  buffer[buf_size - 1] = 0xff; // canary (assumes that char 0xff is not used
  while (fgets(buffer, buf_size, file) == buffer) {
    while (buffer[buf_size - 1] != (char)0xff) { // check canary
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
    if (*str == '#' || *str == '\n') {
      // directly jump to next iteration
      buffer[buf_size-1] = 0xff;
      continue;
    }

    // ok, now we hopefully have a valid key value pair...
    char *key = str;
    // find end of key
    while (*str != ' ' && *str != '=') {
      str++;
    }
    // now str points to the first byte after the key
    char *key_end = str;
    // find start of value
    while (*str == ' ' || *str == '=') {
      str++;
    }
    char *value = str;
    // find end of value and possibly terminate
    while (*str != '\n' && *str != '\0') {
      str++;
    }

    kv_pair_t *pair = malloc(sizeof(kv_pair_t));

    *key_end = '\0';
    if (asprintf(&pair->key, "%s", key) < 0) {
      fprintf(stderr, "Storing key \"%s\" failed, exiting.\n", key);
      abort();
    }
    *str = '\0';
    if (asprintf(&pair->value, "%s", value) < 0) {
      fprintf(stderr, "Storing value \"%s\" failed, exiting.\n", value);
      abort();
    }

    if (kv->used_pairs == kv->n_pairs) {
      // extend
      kv->pairs = realloc(kv->pairs, kv->n_pairs + PEXT);
      kv->n_pairs += PEXT;
    }
    kv->pairs[kv->used_pairs] = pair;
    kv->used_pairs++;

    // prepare next iteration
    buffer[buf_size-1] = 0xff;
  }

  free(buffer);
  *kvp = kv;
  return 0;
}


void kv_cleanup(kv_file_t *kv) {
  if (kv == NULL) {
    return;
  }
  if (kv->used_pairs > 0) {
    size_t i;
    for (i = 0; i < kv->used_pairs; ++i) {
      free(kv->pairs[i]->key);
      free(kv->pairs[i]->value);
      free(kv->pairs[i]);
    }
    free(kv->pairs);
  }
  free(kv);
}


long long kv_get_ll(const kv_file_t *kv, const char *key) {
  const kv_pair_t *pair = kv_find_pair(kv, key);
  if (pair == NULL) {
    return 0;
  }
  else {
    return atoll(pair->value);
  }
}


double kv_get_float(const kv_file_t *kv, const char *key) {
  const kv_pair_t *pair = kv_find_pair(kv, key);
  if (pair == NULL) {
    return 0;
  }
  else {
    return atof(pair->value);
  }
}


static const kv_pair_t* kv_find_pair(const kv_file_t *kv, const char *key) {
  size_t i;
  for (i = 0; i < kv->used_pairs; ++i) {
    if (strcmp(key, kv->pairs[i]->key) == 0) {
      return kv->pairs[i];
    }
  }
  return NULL;
}
