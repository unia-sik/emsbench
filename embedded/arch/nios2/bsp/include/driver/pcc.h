/**
* $Id: head.tpl 499 2014-05-07 11:24:34Z klugeflo $
* @file pcc.h
* @brief Register map and bit definitions for PCC (Performance Counter Core)
* @author Andreas Meixner <meixnean@student.uni-augsburg.de>
* @copyright GNU General Public License v3.
*/

#ifndef DRIVER_PCC_H
#define DRIVER_PCC_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <io.h>

/**
 * @author Andreas Meixner
 * @brief Global clock cycle counter lower 32 bits.
 * Offset for the 32 bit register holding the lower part of the 64 bit global clock cycle counter.
 */
#define PCC_LCTR 0x00
/**
 * @author Andreas Meixner
 * @brief Global clock cycle counter high 32 bits.
 * Offset for the 32 bit register holding the high part of the 64 bit global clock cycle counter.
 */
#define PCC_HCTR 0x04
/**
 * @author Andreas Meixner
 * @brief Global event counter
 * Offset for the global event counter register.
 */
#define PCC_EV 0x08
/**
 * @author Andreas Meixner
 * @brief Section 1 clock cycle counter lower 32 bits.
 * Offset for the 32 bit register holding the lower part of the 64 bit section 1 clock cycle counter.
 */
#define PCC_S1_LCTR 0x10
/**
 * @author Andreas Meixner
 * @brief Section 1 clock cycle counter high 32 bits.
 * Offset for the 32 bit register holding the high part of the 64 bit section 1 clock cycle counter.
 */
#define PCC_S1_HCTR 0x14
/**
 * @author Andreas Meixner
 * @brief Section 1 event counter
 * Offset for the section 1 event counter register.
 */
#define PCC_S1_EV 0x18
/**
 * @author Andreas Meixner
 * @brief Section 2 clock cycle counter lower 32 bits.
 * Offset for the 32 bit register holding the lower part of the 64 bit section 2 clock cycle counter.
 */
#define PCC_S2_LCTR 0x20
/**
 * @author Andreas Meixner
 * @brief Section 2 clock cycle counter high 32 bits.
 * Offset for the 32 bit register holding the high part of the 64 bit section 2 clock cycle counter.
 */
#define PCC_S2_HCTR 0x24
/**
 * @author Andreas Meixner
 * @brief Section 2 event counter
 * Offset for the section 2 event counter register.
 */
#define PCC_S2_EV 0x28
/**
 * @author Andreas Meixner
 * @brief Section 3 clock cycle counter lower 32 bits.
 * Offset for the 32 bit register holding the lower part of the 64 bit section 3 clock cycle counter.
 */
#define PCC_S3_LCTR 0x30
/**
 * @author Andreas Meixner
 * @brief Section 3 clock cycle counter high 32 bits.
 * Offset for the 32 bit register holding the high part of the 64 bit section 3 clock cycle counter.
 */
#define PCC_S3_HCTR 0x34
/**
 * @author Andreas Meixner
 * @brief Section 3 event counter
 * Offset for the section 3 event counter register.
 */
#define PCC_S3_EV 0x38
/**
 * @author Andreas Meixner
 * @brief Section 4 clock cycle counter lower 32 bits.
 * Offset for the 32 bit register holding the lower part of the 64 bit section 4 clock cycle counter.
 */
#define PCC_S4_LCTR 0x40
/**
 * @author Andreas Meixner
 * @brief Section 4 clock cycle counter high 32 bits.
 * Offset for the 32 bit register holding the high part of the 64 bit section 4 clock cycle counter.
 */
#define PCC_S4_HCTR 0x44
/**
 * @author Andreas Meixner
 * @brief Section 4 event counter
 * Offset for the section 4 event counter register.
 */
#define PCC_S4_EV 0x48

/**
 * @author Andreas Meixner
 * @brief ID of the global performance counter
 * This defines an ID to reference the global performance counter. It can be used with all macros
 * and functions affecting performance measuring.
 * @see
 */
#define PCC_GLOBAL 0
/**
 * @author Andreas Meixner
 * @brief ID of the first section performance counter
 * This defines an ID to reference the first section performance counter. It can be used with all macros
 * and functions affecting performance measuring.
 * @see
 */
#define PCC_SECTION1 1
/**
 * @author Andreas Meixner
 * @brief ID of the second section performance counter
 * This defines an ID to reference the second section performance counter. It can be used with all macros
 * and functions affecting performance measuring.
 * @see
 */
#define PCC_SECTION2 2
/**
 * @author Andreas Meixner
 * @brief ID of the third section performance counter
 * This defines an ID to reference the third section performance counter. It can be used with all macros
 * and functions affecting performance measuring.
 * @see
 */
#define PCC_SECTION3 3
/**
 * @author Andreas Meixner
 * @brief ID of the fourth section performance counter
 * This defines an ID to reference the fourth section performance counter. It can be used with all macros
 * and functions affecting performance measuring.
 * @see
 */
#define PCC_SECTION4 4
/**
 * @author Andreas Meixner
 * @brief Stops all counters and resets them to 0.
 * All counters, global and section 1 to 4 will be stopped and the counter values will be reset to 0.
 */
#define PCC_RESET() IOWR32(A_PCC, PCC_LCTR, 1)
/**
 * @author Andreas Meixner
 * @brief Starts the specified counter.
 * @param counter Specifies the counter to start.
 */
#define PCC_START(counter) IOWR32(A_PCC, ((counter * 4) + 1)*4, 0)
/**
 * @author Andreas Meixner
 * @brief Stops the specified counter.
 * @param counter Specifies the counter to stop.
 */
#define PCC_STOP(counter) IOWR32(A_PCC, counter * 4, 0)
/**
 * @author Andreas Meixner
 * @brief Gets the lower 31 bits of the current value of the specified counter.
 * @param counter Specifies the counter to for which to return the current value.
 * @return The lower portion (31bit) of the current counter value.
 */
#define PCC_GET_LOW(counter) (unsigned int)IORD32(A_PCC, counter * 4)
/**
 * @author Andreas Meixner
 * @brief Gets the higher 31 bits of the current value of the specified counter.
 * @param counter Specifies the counter to for which to return the current value.
 * @return The higher portion (31bit) of the current counter value.
 */
#define PCC_GET_HIGH(counter) (unsigned int)IORD32(A_PCC, counter * 4)
/**
 * @author Andreas Meixner
 * @brief Gets the current value of the specified counter.
 * @param counter Specifies the counter to for which to return the current value.
 * @return The full 62 bit value of the current counter.
 */
#define PCC_GET(counter) ((unsigned long int)PCC_GET_HIGH(counter) << 32) | PCC_GET_LOW(counter)
#ifdef __cplusplus
}
#endif

#endif // !DRIVER_PCC_H
