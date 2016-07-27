	/**
	 * $Id: freeems_hal_ubench.S 546 2016-07-15 06:51:19Z klugeflo $
	 */



	.text
        .thumb_func
        .global bm_stores
bm_stores:
	ldr	r0, array
	mov	r1, #42
	str	r1, [r0, #0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	str	r1, [r0, #32]
	str	r1, [r0, #36]
	str	r1, [r0, #40]
	str	r1, [r0, #44]
	str	r1, [r0, #48]
	str	r1, [r0, #52]
	str	r1, [r0, #56]
	str	r1, [r0, #60]
	mov	r0, #42
	bx	lr

	.align
array:	.space	64
