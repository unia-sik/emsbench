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
 * $Id: trace.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file trace.c
 * @brief
 * @author Alexander Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include <tg/tgdata.h>

const cs_phase_t PHASES[] = {
  { 11.000000, 0.000000 },
  { 1.406534, 0.000000 },
  { 2.593466, 8.294622 },
  { 9.000000, 0.000000 },
  { 2.000000, -5.529748 },
  { 0.522616, -20.000000 },
  { 2.477384, 0.000000 },
  { 21.000000, 0.000000 },
  { 1.758167, 0.000000 },
  { 3.241833, 6.635697 },
  { 1.000000, -20.000000 },
  { 1.000000, 4.725729 },
  { 5.000000, 4.058289 },
  { 24.000000, 0.000000 },
  { 8.000000, -3.282440 },
  { 0.013474, -20.000000 },
  { 2.986526, 0.000000 },
  { 21.000000, 0.000000 },
  { 1.758167, 0.000000 },
  { 3.241833, 6.635697 },
  { 1.000000, -20.000000 },
  { 1.000000, 4.725729 },
  { 9.000000, 2.652476 },
  { 1.000000, -20.000000 },
  { 1.000000, 6.831557 },
  { 8.000000, 1.532575 },
  { 12.000000, 0.000000 },
  { 8.000000, -1.532575 },
  { 13.000000, 0.000000 },
  { 0.847070, -20.000000 },
  { 0.152930, 0.000000 },
  { 1.000000, 30.109838 },
  { 7.000000, -4.262909 },
  { 0.013474, -20.000000 },
  { 2.986526, 0.000000 },
  { 7.000000, 0.000000 },
};

const size_t N_PHASES = 36;
const float OMEGA_IDLE = 11.666667;
const size_t N_PRIMARY = 12;
const float DIST_PRIMARY = 0.083333;
const float OFFSET_SECONDARY = 0.040000;
