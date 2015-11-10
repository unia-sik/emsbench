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
 * $Id: freeems_hal_globals.c 502 2015-11-05 14:18:19Z klugeflo $
 * @brief Various globally accessable fields.
 * @file freeems_hal_globals.c
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 */
#include "freeems_hal_globals.h"
#include <hal/ems/freeems_hal.h>

channelid_t injectionOutputChannels[] = {INJECTION1_OUTPUT,INJECTION2_OUTPUT,INJECTION3_OUTPUT,INJECTION4_OUTPUT,INJECTION5_OUTPUT,INJECTION6_OUTPUT,INJECTION7_OUTPUT,INJECTION8_OUTPUT};
channelid_t ignitionChannels[] = {IGNITION1_OUTPUT,IGNITION2_OUTPUT,IGNITION3_OUTPUT,IGNITION4_OUTPUT,IGNITION5_OUTPUT,IGNITION6_OUTPUT,IGNITION7_OUTPUT,IGNITION8_OUTPUT};
