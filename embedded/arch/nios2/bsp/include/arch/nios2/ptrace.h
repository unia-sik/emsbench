/**
 * $Id: ptrace.h 803 2014-03-05 14:57:59Z klugeflo $
 */

#ifndef _NIOS2_PTRACE_H
#define _NIOS2_PTRACE_H

/* plucked from linux-2.6.24, adjusted for RTOS training (06.11.2009 FAK) */

//#include <spr-defs.h>

// if you change anything on the data structures below, you must also adjust
// this value!
#define SC_STACKFRAME_SIZE 120

#ifndef __ASSEMBLY__

#include <stdint.h>

typedef struct {
  uint32_t ea;
  uint32_t status;  // estatus
  uint32_t gpr1; // at
  uint32_t gpr2;
  uint32_t gpr3;
  uint32_t gpr4;
  uint32_t gpr5;
  uint32_t gpr6;
  uint32_t gpr7;
  uint32_t gpr8;
  uint32_t gpr9;
  uint32_t gpr10;
  uint32_t gpr11;
  uint32_t gpr12;
  uint32_t gpr13;
  uint32_t gpr14;
  uint32_t gpr15;
  uint32_t gpr16;
  uint32_t gpr17;
  uint32_t gpr18;
  uint32_t gpr19;
  uint32_t gpr20;
  uint32_t gpr21;
  uint32_t gpr22;
  uint32_t gpr23;
  uint32_t gpr24; // et
  uint32_t gpr25; // bt
  //uint32_t gpr26; // gp // never change gp after system initialisation
  //uint32_t gpr27; // sp
  uint32_t gpr28; // fp // FIXME: save?!
  //uint32_t gpr29; // ea
  uint32_t gpr30; // ba
  uint32_t gpr31; // ra
} sc_stackframe_t;

#else


/*
 * Offsets used by 'ptrace' system call interface.
 */

/*
  You can use this defines as offsets for your load/store instructions, e.g.

l.sw  PC(r1), r9
l.sw  GPR9(r1), r9

l.lwz r3, GPR3(r1)

*/

#define EA        0
#define STATUS    4
#define GPR1      8
#define GPR2      12
#define GPR3      16
#define GPR4      20
#define GPR5      24
#define GPR6      28
#define GPR7      32
#define GPR8      36
#define GPR9      40
#define GPR10     44
#define GPR11     48
#define GPR12     52
#define GPR13     56
#define GPR14     60
#define GPR15     64
#define GPR16     68
#define GPR17     72
#define GPR18     76
#define GPR19     80
#define GPR20     84
#define GPR21     88
#define GPR22     92
#define GPR23     96
#define GPR24     100
#define GPR25     104
//#define GPR26
///define GPR27
#define GPR28     108
//#define GPR29     112
#define GPR30     112
#define GPR31     116
//#define RESULT    128
//#define SYSCALLNO 132

#endif /* __ASSEMBLY__ */

#define TASK_KSP 4

#endif /* _OR32_PTRACE_H */
