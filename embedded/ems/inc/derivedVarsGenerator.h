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
 * @file derivedVarsGenerator.h
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
#ifndef FILE_DERIVEDVARSGENERATOR_H_SEEN
#define FILE_DERIVEDVARSGENERATOR_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
/* If fail on warning is off, remove the definition such that we can redefine
 * correctly. */
#undef EXTERN
#endif


#ifdef DERIVEDVARSGENERATOR_C
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN void generateDerivedVars(void) FPAGE_FE;


#undef EXTERN


#else
/* let us know if we are being untidy with headers */
#warning "Header file DERIVEDVARSGENERATOR_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
