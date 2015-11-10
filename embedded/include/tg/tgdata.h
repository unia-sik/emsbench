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
 * $Id: tgdata.h 502 2015-11-05 14:18:19Z klugeflo $
 * @file tgdata.h
 * @brief Input data of the trace generator.
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#ifndef TG_CRANKSHAFTDATA_H
#define TG_CRANKSHAFTDATA_H 1

#include <stdlib.h>

/**
 * @brief One phase of the driving cycle.
 * Note that one operation of the driving cycle can consist of multiple phases!
 */
typedef struct {
  float duration; ///< duration of the phase in seconds
  float alpha; ///< angular acceleration of the phase
} cs_phase_t;

/**
 * @name Input data
 * The following variables are defined in the .c file that is created by
 * the trace generator preprocessor tgpp.
 * @{
 */
extern const cs_phase_t PHASES[];
extern const size_t N_PHASES;

extern const float OMEGA_IDLE;

extern const size_t N_PRIMARY;
extern const float DIST_PRIMARY;
extern const float OFFSET_SECONDARY;

/**
 * @}
 */


#endif // !TG_CRANKSHAFTDATA_H
