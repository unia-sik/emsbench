/**
 * $Id: intrinsics.h 803 2014-03-05 14:57:59Z klugeflo $
 */

#ifndef NIOS2INTRINSICS_H_
#define NIOS2INTRINSICS_H_ 1


/****************************************************************** Includes */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************* Defines */

#define NOP "\tnop"

/****************************************************************** Typedefs */


/************************************************************** Global const */


/********************************************************** Global variables */


/************************************************ Global function prototypes */


/*************************************************** Global inline functions */


/******************************************************************** Macros */

#define __rdctl_status()                                    \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, status" : "=r"(val) : );   \
        val; })
#define __rdctl_estatus()                                   \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, estatus" : "=r"(val) : );  \
        val; })
#define __rdctl_bstatus()                                   \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, bstatus" : "=r"(val) : );  \
        val; })
#define __rdctl_ienable()                                   \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, ienable" : "=r"(val) : );  \
        val; })
#define __rdctl_ipending()                                  \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, ipending" : "=r"(val) : ); \
        val; })
#define __rdctl_cpuid()                                     \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, cpuid" : "=r"(val) : );    \
        val; })

#define __rdctl_badaddr()                                   \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, badaddr" : "=r"(val) : );  \
        val; })
#define __rdctl_exception()                                 \
    ({ uint32_t val;                                        \
        asm volatile ("rdctl %0, exception" : "=r"(val) : );\
        val; })


#define __wrctl_status(val)                             \
    { asm volatile ("wrctl status, %0" : : "r"(val)); }
#define __wrctl_ienable(val)                            \
    { asm volatile ("wrctl ienable, %0" : : "r"(val)); }
#define __wrctl_ipending(val) 0


#define IRQ_ENABLED SPR_SR_PIE

#ifdef __cplusplus
}
#endif

#endif /* NIOS2INTRINSICS_H_ */
