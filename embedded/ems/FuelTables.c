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
 * $Id: header-ems.c 480 2015-10-27 12:42:40Z klugeflo $
 * @file FuelTables.c
 * @ingroup dataInitialisers
 *
 * @brief Fuel VE and Lambda tables
 *
 * This file contains the definitions of the primary group VE and lambda
 * tables. The declaration can be found in the global constants header file.
 *
 * @note At least one Doxygen bug prevents the data structures below being show
 *       correctly in the documentation for this file. Please see the source
 *       code itself for more information.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include "inc/freeEMS.h"


const volatile mainTable VETableMainFlash FUELTABLESD = {
  MAINTABLE_RPM_LENGTH,		/* VETableMain.RPMLength */
  MAINTABLE_LOAD_LENGTH,		/* VETableMain.LoadLength */
  /* VETableMain.RPM */
  {
    0,	 400,	1400,	2100,
    2800,	3500,	4200,	4900,
    5600,	6300,	7000,	7700,
    8400,	9100,	9800,  10500,
    11200,  11900,  12600,  13300,
    14000,  14700,  14400,  16100,
    16800,  17500,  18200
  },
  /* VETableMain.Load */
  {
    1600,	 3200,	 4800,	 6400,
    8000,	 9600,	11200,	12800,
    14400,	16000,	17600,	19200,
    20800,	22400,	24000,	25600,
    27200,	28800,	30400,	32000,
    33600
  },
  /* VETableMain.Table (Laid out to make sense for 24 RPM and 19 Load bins,
   * 8 extras on end to make up size.) */
  {
#include "data/tables/ve/flat80Percent.h"
  }
};


const volatile mainTable VETableSecondaryFlash FUELTABLESD = {
  /* VETableSecondary.RPMLength */
  MAINTABLE_RPM_LENGTH,
  /* VETableSecondary.LoadLength */
  MAINTABLE_LOAD_LENGTH,
  /* VETableSecondary.RPM */
  {
    0,	 200,	 700,	1050,
    1400,	1750,	2100,	2450,
    2800,	3150,	3500,	3850,
    4200,	4550,	4900,	5250,
    5600,	5950,	6300,	6650,
    7000,	7350,	7700,	8050,
    8400,	8750,	9100
  },
  /* VETableSecondary.Load */
  {
    1600,	 3200,	 4800,	 6400,
    8000,	 9600,	11200,	12800,
    14400,	16000,	17600,	19200,
    20800,	22400,	24000,	25600,
    27200,	28800,	30400,	32000,
    33600
  },
  /* VETableSecondary.Table */
  {
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,

    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,

    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,

    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  0xEEEE /* 6 extras to allow different axis sizes. */
  }
};


const volatile mainTable VETableTertiaryFlash FUELTABLESD = {
  /* VETableTertiary.RPMLength */
  MAINTABLE_RPM_LENGTH,
  /* VETableTertiary.LoadLength */
  MAINTABLE_LOAD_LENGTH,
  /* VETableTertiary.RPM */
  {
    0,	 200,	 700,	1050,
    1400,	1750,	2100,	2450,
    2800,	3150,	3500,	3850,
    4200,	4550,	4900,	5250,
    5600,	5950,	6300,	6650,
    7000,	7350,	7700,	8050,
    8400,	8750,	9100
  },
  /* VETableTertiary.Load */
  {
    1600,	 3200,	 4800,	 6400,
    8000,	 9600,	11200,	12800,
    14400,	16000,	17600,	19200,
    20800,	22400,	24000,	25600,
    27200,	28800,	30400,	32000,
    33600
  },
  /* VETableTertiary.Table */
  {
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,

    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,

    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,

    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,  49152,
    49152,  49152,  49152,  49152,  49152,  0xDDDD /* 6 extras to allow different axis sizes. */
  }
};


const volatile mainTable LambdaTableFlash FUELTABLESD = {
  /* LambdaTable.RPMLength */
  MAINTABLE_RPM_LENGTH,
  /* LambdaTable.LoadLength */
  MAINTABLE_LOAD_LENGTH,
  /* LambdaTable.RPM */
  {
    0,	  200,	  700,	 1050,
    1400,	 1750,	 2100,	 2450,
    2800,	 3150,	 3500,	 3850,
    4200,	 4550,	 4900,	 5250,
    5600,	 5950,	 6300,	 6650,
    7000,	 7350,	 7700,	 8050,
    8400,	 8750,	 9100
  },
  /* LambdaTable.Load */
  {
    1600,	 3200,	 4800,	 6400,
    8000,	 9600,	11200,	12800,
    14400,	16000,	17600,	19200,
    20800,	22400,	24000,	25600,
    27200,	28800,	30400,	32000,
    33600
  },
  /* LambdaTable.Table */
  {
#include "data/tables/lambda/flatStoichiometric.h"
  }
};
