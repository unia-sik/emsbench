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
 * $Id: transformer.h 502 2015-11-05 14:18:19Z klugeflo $
 * @file transformer.h
 * @brief Tranformation of driving cycle operations to trace generator phases.
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <stdio.h>

#include "kvfile.h"
#include "cr.h"


/**
 * @brief Transform a driving cycle into a crank shaft cycle.
 * @param cardata Properties of the car (gears etc.)
 * @param cycle The driving cycle
 * @param outfile Where to write tht crank shaft cycle.
 * @return 0 on success.
 */
int transform(const kv_file_t *cardata, const cycle_t *cycle, FILE* outfile);


#endif // !TRANSFORMER_H
