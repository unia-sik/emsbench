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
 * $Id: cr.h 502 2015-11-05 14:18:19Z klugeflo $
 * @file cr.h
 * @brief Reimplementation of cyclereader
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef CR_H
#define CR_H

#include <stdio.h>

/**
 * @brief Input data as read from file
 */
typedef struct {
  double acceleration; ///< ms^{-2}
  long speed_start; ///< kmh^{-1}
  long speed_end; ///< kmh^{-1}
  unsigned duration; ///< s
  unsigned gear; ///< [0..5]
} operation_t;


/** 
 * @brief A complete driving cycle
 */
typedef struct {
  size_t n_entries;
  size_t used_entries;
  operation_t *operations;
} cycle_t;


/**
 * @brief Read a driving cycle from file.
 *
 * No error handling is performed, so make sure your file is valid!
 * @param file The input file
 * @return a structure containing the parsed driving cycle
 */
cycle_t* read_cycle(FILE *file);


/**
 * @brief Free memory used by driving cycle
 */
void free_cycle(cycle_t* cycle);

#endif // !CR_H
