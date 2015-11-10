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
 * @file xgateVectors.h
 * @brief 
 * <h> original author</h> Sean Keys
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#ifndef FILE_XGATEVECTORS_H_SEEN
#define FILE_XGATEVECTORS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
/* If fail on warning is off, remove the definition such that we can redefine
 * correctly. */
#undef EXTERN
#endif


#ifdef XGATEVECTORS_C
#define EXTERN
#else
#define EXTERN extern
#endif


typedef struct {
  /* This data is forced into the XGATE PC register */
  unsigned short programCounterValue;
  /* This data is forced into the XGATE R1 register */
  unsigned short initialVariable;
} xgateIntVector;


EXTERN const xgateIntVector xgateIntVectorTable[121];

/* TODO Create the XGATE error handling thread in asm. */
// Xgate control value
#define XGATE_ERROR_HANDLER 0x0000


#else
/* let us know if we are being untidy with headers */
#warning "Header file XGATEVECTORS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
