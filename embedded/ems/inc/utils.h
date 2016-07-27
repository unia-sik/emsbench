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
 * @file utils.h
 * @ingroup allHeaders
 * @brief 
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_UTILS_H_SEEN
#define FILE_UTILS_H_SEEN


#include <stdint.h>

#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
/* If fail on warning is off, remove the definition such that we can redefine
 * correctly. */
#undef EXTERN
#endif


#ifdef UTILS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN unsigned short safeAdd(unsigned short, unsigned short);
EXTERN unsigned short safeTrim(unsigned short, signed short);
EXTERN unsigned short safeScale(unsigned short, unsigned short);

EXTERN void sleep(unsigned short) FPAGE_FE;
EXTERN void sleepMicro(unsigned short) FPAGE_FE;

EXTERN void adjustPWM(void) FPAGE_FE;
EXTERN void setupPagedRAM(unsigned char) FPAGE_F8;
EXTERN void resetToNonRunningState(void) FPAGE_F8;

EXTERN void sampleEachADC(ADCArray*) FPAGE_F8;
EXTERN void sampleLoopADC(ADCArray*) FPAGE_F8;

EXTERN unsigned char checksum(unsigned char *, unsigned short) FPAGE_F8;
EXTERN unsigned short stringCopy(unsigned char*, unsigned char*) FPAGE_F8;
// In unpaged flash as it needs to compare paged flash with unpaged things
EXTERN unsigned short compare(unsigned char*, unsigned char*, unsigned short);


#undef EXTERN


#else
/* let us know if we are being untidy with headers */
#warning "Header file UTILS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
