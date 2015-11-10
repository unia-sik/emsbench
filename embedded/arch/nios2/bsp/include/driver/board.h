/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file board.h
* @brief Include file for the OR32 Board, uses the CPP define BOARD to
         select the correct board header file.
         The addresses in this file can also be used for assembly code. If
         you include this file into your assemly file, make sure that
         you have __ASSEMBLY__ defined.
*
* @author Florian Kluge <kluge@informatik.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/

#ifndef _BOARD_H
#define _BOARD_H 1

#define BOARD_INCLUDE 1

#if __BOARD==de2-70
#  include "nios2f-de2-70.h"
//#warning Building for DE2-70 board
#elif __BOARD==db_4ce10
#  include "nios2s-db_4ce10.h"
//#warning Building for DB 4CE10 board
//#elif __BOARD==your-board
//#include <your-board.h>
#else
#  error You need to define a board type in your Makefile!
#endif

#undef BOARD_INCLUDE


#define IRQ_MASK(irq_n) (1 << (irq_n))



#endif /* !_BOARD_H */
