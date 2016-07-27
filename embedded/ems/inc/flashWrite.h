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
 * @file flashWrite.h
 * @ingroup allHeaders
 * @brief 
 * <h> original authors</h> Sean Keys, Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_FLASHWRITE_H_SEEN
#define FILE_FLASHWRITE_H_SEEN

#include <stdint.h>

#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
/* If fail on warning is off, remove the definition such that we can redefine
 * correctly. */
#undef EXTERN
#endif


#ifdef FLASHWRITE_C
#define EXTERN
#else
#define EXTERN extern
#endif


/// @todo TODO add mass erase function and replace ?? with the real value
/* Used to erase 128k flash blocks */
#define MASS_ERASE  	0x??
/* Word = 2 bytes, this is the minimum write size, 64K of these per block, 512
 * per sector	*/
#define WORD_PROGRAM	0x20
/* Sector = 1024 bytes, there are 128 sectors to a block, and 4 blocks to the
 * chip*/
#define SECTOR_ERASE	0x40
/// @todo TODO CBEIF mask hash define - is this still needed?


/* The following code must run from unpaged space for obvious reasons. Location
 * explicitly set to text. */
EXTERN unsigned short writeWord(unsigned short*, unsigned short) TEXT;
EXTERN unsigned short eraseSector(unsigned char, unsigned short*) TEXT;
EXTERN unsigned short writeSector(unsigned char, unsigned short*, unsigned char, unsigned short*) TEXT;
EXTERN unsigned short writeBlock(blockDetails*, void*) TEXT;


#undef EXTERN


#else
/* let us know ifunsigned short writeBlock(unsigned short* flashAddr, unsigned short* RAMAddr, unsigned short size){
 *  we are being untidy with headers */
#warning "Header file FLASHWRITE_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
