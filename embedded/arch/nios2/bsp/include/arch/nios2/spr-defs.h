/**
 * $Id: spr-defs.h 803 2014-03-05 14:57:59Z klugeflo $
 */

/******************************************************************************

File: spr-defs.h

Project: RTOS training on NIOS2

Description: NIOS2 architecture specific special-purpose registers (see below)
             (available from 4th training)

Author: Florian Kluge <kluge@informatik.uni-augsburg.de>

Created: 07.09.2009

Last changed: 08.09.2009

*******************************************************************************

Modification history:
---------------------

07.09.2009 (FAK) Copied from OR32 sim sources
08.09.2009 (FAK) Header

*/



/* spr-defs.h -- Defines NIOS2 architecture specific special-purpose registers

   Copyright (C) 1999 Damjan Lampret, lampret@opencores.org
   Copyright (C) 2008 Embecosm Limited

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of OpenRISC 1000 Architectural Simulator.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>. */

/* This program is commented throughout in a fashion suitable for processing
   with Doxygen. */


#ifndef SPR_DEFS__H
#define SPR_DEFS__H


/*
 * Bit definitions for the Supervision Register
 *
 */
#define SPR_SR_PIE         0x00000001  /* Processor Interrupt Enable */
#define SPR_SR_SM          0x00000002  /* Supervisor Mode */
#define SPR_SR_EH          0x00000004  /* Exception Handler Mode */
#define SPR_SR_IH          0x00000008  /* Interrupt Handler Mode */
#define SPR_SR_IL          0x000003f0  /* Interrupt Level Mask */
#define SPR_SR_CRS         0x0000fc00  /* Current Register Set */
#define SPR_SR_PRS         0x003f0000  /* Previous Register Set */
#define SPR_SR_NMI         0x00400000  /* NMI Mode */
#define SPR_SR_RSIE        0x00800000  /* Register Set Interrupt Enable */
#define SPR_SR_RES         0xff000000  /* Reserved */


#endif	/* SPR_DEFS__H */
