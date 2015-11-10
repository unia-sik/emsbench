#define __ASSEMBLY__
#include <ptrace.h>
#include <driver/board.h>
#include <driver/pio.h>
/*************************************************************************\
|                     Exception handler (.exceptions)                     |
\*************************************************************************/
    .set noat
    .set nobreak
    .section .exceptions.entry.label, "xa"

    .globl alt_exception
    .type alt_exception, @function
alt_exception:

    .section .exceptions
general_exception:
/* save stackframe */
    addi    sp,  sp, -SC_STACKFRAME_SIZE
    stw     r1,  GPR1(sp)
    rdctl   r1,  estatus
    stw     r1,  STATUS(sp)
    stw     ea,  EA(sp)
    stw     r2,  GPR2(sp)
    stw     r3,  GPR3(sp)
    stw     r4,  GPR4(sp)
    stw     r5,  GPR5(sp)
    stw     r6,  GPR6(sp)
    stw     r7,  GPR7(sp)
    stw     r8,  GPR8(sp)
    stw     r9,  GPR9(sp)
    stw     r10, GPR10(sp)
    stw     r11, GPR11(sp)
    stw     r12, GPR12(sp)
    stw     r13, GPR13(sp)
    stw     r14, GPR14(sp)
    stw     r15, GPR15(sp)
    stw     r16, GPR16(sp)
    stw     r17, GPR17(sp)
    stw     r18, GPR18(sp)
    stw     r19, GPR19(sp)
    stw     r20, GPR20(sp)
    stw     r21, GPR21(sp)
    stw     r22, GPR22(sp)
    stw     r23, GPR23(sp)
    stw     r24, GPR24(sp)
    stw     r25, GPR25(sp)
    /* global pointer: never modify
    stw     r26, GPR26(sp)*/
    /* stack pointer: do not save or load
    stw     r27, GPR27(sp)*/
    stw     r28, GPR28(sp)
    //stw     r29, GPR29(sp)
    stw     r30, GPR30(sp)
    stw     r31, GPR31(sp)

	/*
    movhi   et, %hi(A_S7CTL + S7_LUT)
    addi    et, et, %lo(A_S7CTL + S7_LUT)
    stwio   r2, 0(et)

	movhi	et, %hi(A_PIO_LRED + PIO_DATA)
	addi	et, et, %lo(A_PIO_LRED + PIO_DATA)
	movhi	r22, %hi(_irqctr)
	addi	r22, r22, %lo(_irqctr)
	ldw	r23, 0(r22)
	stw	r23, 0(et)
	roli	r23, r23, 1
	stw	r23, 0(r22)
	*/

/* read exception cause and store as first parameter */
    rdctl   r13, exception
    srli    r13, r13, 2
    andi    r13, r13, 0x001f
/* check for irq */
    movi    r14, 2
    beq	r13, r14, process_irq

    call exception_handle

	
/* restore stackframe */
exception_restore:
    ldw     r1,  STATUS(sp)
    wrctl   estatus, r1
    ldw     r1,  GPR1(sp)
    ldw     r2,  GPR2(sp)
    ldw     r3,  GPR3(sp)
    ldw     r4,  GPR4(sp)
    ldw     r5,  GPR5(sp)
    ldw     r6,  GPR6(sp)
    ldw     r7,  GPR7(sp)
    ldw     r8,  GPR8(sp)
    ldw     r9,  GPR9(sp)
    ldw     r10, GPR10(sp)
    ldw     r11, GPR11(sp)
    ldw     r12, GPR12(sp)
    ldw     r13, GPR13(sp)
    ldw     r14, GPR14(sp)
    ldw     r15, GPR15(sp)
    ldw     r16, GPR16(sp)
    ldw     r17, GPR17(sp)
    ldw     r18, GPR18(sp)
    ldw     r19, GPR19(sp)
    ldw     r20, GPR20(sp)
    ldw     r21, GPR21(sp)
    ldw     r22, GPR22(sp)
    ldw     r23, GPR23(sp)
    ldw     r24, GPR24(sp)
    ldw     r25, GPR25(sp)
    /* global pointer: never modify
    ldw     r26, GPR26(sp)*/
    /* stack pointer: do not save or load
    ldw     r27, GPR27(sp)*/
    ldw     r28, GPR28(sp)
    //ldw     r29, GPR29(sp)
    ldw     r30, GPR30(sp)
    ldw     r31, GPR31(sp)
    ldw     ea,  EA(sp)
    addi    sp,  sp, SC_STACKFRAME_SIZE
    eret


process_irq:
    /* copy saved stackframe as first parameter */
    mov     r4, sp
    /* call irq handler */
    call    do_irq
	
    ldw et,EA(sp)
    subi et,et,4
    stw et,EA(sp)
    /* return to exception handler */
    br      exception_restore
