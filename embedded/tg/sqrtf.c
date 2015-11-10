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
 * $Id: sqrtf.c 506 2015-11-06 14:31:02Z meixnean $
 * @file sqrtf.c
 * @brief Implementation of a sqrtf
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>, based on code
 * by Chris Stifter
 */
float sqrtf_babylonian(float x);
float sqrtf_quake3(float x);


/**
 * Babylonian derived fast square root function
 * for reference visit: www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
 */
float sqrtf_babylonian(float x) {
  union {
    int i;
    float x;
  } u;
  u.x = x;
  u.i = (1<<29) + (u.i >> 1) - (1 << 22);

  u.x = u.x + x/u.x;
  u.x = 0.25f*u.x + x/u.x;

  return u.x;
}


/**
 * the Magic Number fast square root function derived from Quake 3;
 * for reference visit: www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Funktion-Precisi
 * alternative magic number: 0x5f375a86
 * will most likely not use this one due to insufficient precision
 */
float sqrtf_quake3( float x ) {
  const float xhalf = 0.5f * x;
  union {
    float x;
    int i;
  } u;
  u.x = x;
  u.i = 0x5f3759df - ( u.i >> 1 );
  return x * u.x * (1.5f - xhalf * u.x * u.x);
}

/**
 * x86_64-pc-linux-gnu-gcc (Gentoo 4.8.3 p1.1, pie-0.5.9) 4.8.3
 * with -O0 calls this function always, -O1 or more generates sqrtss
 * instruction and only conditionally calls sqrtf.
 */
float sqrtf(float x) __attribute__ ((weak, alias("sqrtf_babylonian")));
