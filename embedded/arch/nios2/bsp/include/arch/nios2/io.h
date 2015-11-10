/**
 * $Id: io.h 803 2014-03-05 14:57:59Z klugeflo $
 * I/O access macros
 */

#ifndef NIOS2_IO_H
#define NIOS2_IO_H 1

#include <stdint.h>


#define __IOWR8(base, offset, val)					\
  asm volatile ("stbio %0, "#offset"(%1)" : : "r"(val), "r"(base))

#define __IOWR16(base, offset, val)					\
  asm volatile ("sthio %0, "#offset"(%1)" : : "r"(val), "r"(base))

#define __IOWR32(base, offset, val)					\
  asm volatile ("stwio %0, "#offset"(%1)" : : "r"(val), "r"(base))

#define IOWR8(base, offset, val)  __IOWR8((base), (offset), (val))
#define IOWR16(base, offset, val) __IOWR16((base), (offset), (val))
#define IOWR32(base, offset, val) __IOWR32((base), (offset), (val))





#define __IORD8(base, offset)						\
  ( {uint8_t val;							\
    asm volatile ("ldbio %0, "#offset"(%1)" : "=r"(val) : "r"(base));	\
    val; })

#define __IORD16(base, offset)						\
  ( {uint16_t val;						\
    asm volatile ("ldhio %0, "#offset"(%1)" : "=r"(val) : "r"(base));	\
    val; })

#define __IORD32(base, offset)						\
  ( {uint32_t val;						\
    asm volatile ("ldwio %0, "#offset"(%1)" : "=r"(val) : "r"(base));	\
    val; })

#define IORD8(base, offset)  __IORD8((base), (offset))
#define IORD16(base, offset) __IORD16((base), (offset))
#define IORD32(base, offset) __IORD32((base), (offset))


/* Byte order of the bus */
#define htonl(x) (x)
#define htons(x) (x)

#endif /* NIOS2_IO_H */
