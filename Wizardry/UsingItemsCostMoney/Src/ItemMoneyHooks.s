
	.thumb

	.global ItemsMoneyHook0809AAA8
	.type   ItemsMoneyHook0809AAA8, function

ItemsMoneyHook0809AAA8:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	@ implied   @ arg r0 = item
	mov r1, r5  @ arg r1 = color
	mov r2, r10 @ arg r2 = tm
	sub r2, #1

	bl BXR3

	@ replaced
	mov r0, #0x80

	ldr r3, =0x0809AAB8+1
BXR3:
	bx  r3

	.global ItemsMoneyHook0809A050
	.type   ItemsMoneyHook0809A050, function

ItemsMoneyHook0809A050:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	mov r0, r5       @ arg r0 = item
	mov r1, r4       @ arg r1 = color
	ldr r2, [sp, #8] @ arg r2 = tm
	sub r2, #1

	bl BXR3

	ldr r3, =0x0809A060+1
	bx r3

	.global ItemsMoneyHook0809B7E4
	.type   ItemsMoneyHook0809B7E4, function

ItemsMoneyHook0809B7E4:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	mov r0, r6
	mov r1, r7
	sub r2, r4, #1

	bl BXR3

	ldr r3, =0x0809B7F4+1
	bx r3

	.global ItemsMoneyHook0809D3DC
	.type   ItemsMoneyHook0809D3DC, function

ItemsMoneyHook0809D3DC:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	mov r0, r7
	mov r1, r5
	sub r2, r4, #1

	bl BXR3

	ldr r3, =0x0809D3EC+1
	bx r3

	.global ItemsMoneyHook08034D00
	.type   ItemsMoneyHook08034D00, function

ItemsMoneyHook08034D00:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	mov r0, r4
	mov r1, #2
	sub r2, r7, #1

	bl BXR3

	ldr r3, =0x08034D10+1
	bx r3

	.global ItemsMoneyHook08034DFC
	.type   ItemsMoneyHook08034DFC, function

ItemsMoneyHook08034DFC:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	@ implied
	mov r1, r5
	sub r2, r4, #1

	bl BXR3

	@ replaced
	ldr r4, [sp, #0x1C]

	ldr r3, =0x08034E0C+1
	bx r3

	.global ItemsMoneyHook08034F1C
	.type   ItemsMoneyHook08034F1C, function

ItemsMoneyHook08034F1C:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	mov r0, r6
	mov r1, r5
	sub r2, r4, #1

	bl BXR3

	ldr r3, =0x08034F2C+1
	bx r3

	.global ItemsMoneyHook0809D50C
	.type   ItemsMoneyHook0809D50C, function

ItemsMoneyHook0809D50C:
	ldr r3, =ItemsMoney_DrawDurabilityRaw

	mov r0, r6
	mov r1, r5
	sub r2, r4, #1

	bl BXR3

	ldr r3, =0x0809D51C+1
	bx r3
