	/**
	 * $Id: freeems_hal_ubench.S 546 2016-07-15 06:51:19Z klugeflo $
	 */

	.data
	.align
array:	.space	64
	
	.set noat
	.text
        .global bm_stores
bm_stores:
	movhi	at, %hi(array)
	ori	at, at, %lo(array)

	movui	r2, 42
	stw	r2, 0(at)
	stw	r2, 4(at)
	stw	r2, 8(at)
	stw	r2, 12(at)
	stw	r2, 16(at)
	stw	r2, 20(at)
	stw	r2, 24(at)
	stw	r2, 28(at)
	stw	r2, 32(at)
	stw	r2, 36(at)
	stw	r2, 40(at)
	stw	r2, 44(at)
	stw	r2, 48(at)
	stw	r2, 52(at)
	stw	r2, 56(at)
	stw	r2, 60(at)

	ret

