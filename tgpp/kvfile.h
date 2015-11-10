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
 * $Id: kvfile.h 502 2015-11-05 14:18:19Z klugeflo $
 * @file kvfile.h
 * @brief Provides a very basic key/value map
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef KVFILE_H
#define KVFILE_H 1

#include <stdio.h>

struct _kv_file;
typedef struct _kv_file kv_file_t;


/**
 * @brief Read key-value file into memory
 * @param kvp where to place the memory representation
 * @param file a valid and opened file
 * @return 0 on success
 */
int kv_read_file(kv_file_t** kvp, FILE* file);


/**
 * @brief Free the memory that was used by a kvfile
 * @param kv the representation
 */
void kv_cleanup(kv_file_t *kv);


/**
 * @brief Retrieve a long long integer value
 * @param kv A key-value file
 * @param key The key of the value
 * @return The long long value for the key. If the key does not exist,
 * 0 is returned
 */
long long kv_get_ll(const kv_file_t *kv, const char *key);


/**
 * @brief Retrieve a float value
 * @param kv A key-value file
 * @param key The key of the value
 * @return The float value for the key. If the key does not exist,
 * 0 is returned
 */
double kv_get_float(const kv_file_t *kv, const char *key);



#endif // !KVFILE_H
