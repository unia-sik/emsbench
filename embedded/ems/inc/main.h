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
 * @file main.h
 * @ingroup allHeaders
 * @brief Include this file to use the FreeEMS API.
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */
/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_MAIN_H_SEEN
#define FILE_MAIN_H_SEEN


#include "freeEMS.h"
#include "interrupts.h"
#include "utils.h"
#include "init.h"
#include "commsISRs.h"
#include "commsCore.h"
#include "coreVarsGenerator.h"
#include "derivedVarsGenerator.h"
#include "fuelAndIgnitionCalcs.h"
#include "DecoderInterface.h"

/* Computer Operating Properly reset sequence MC9S12XDP512V2.PDF Section 2.4.1.5 */
#define COP_RESET1 0x55
#define COP_RESET2 0xAA


// temp method of ensuring logs sent only once per second
//unsigned short lastTime = 65535;
//unsigned short lastCalcCount;
int main_freeems(void);

#else
/* let us know if we are being untidy with headers */
#warning "Header file MAIN_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
