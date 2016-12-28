.global main
main:
	mov	r0,	#15
	MOV r1, #15
	BL firstfunc
	SWI 0x11
firstfunc: 
	ADD r0, r0, r1
	mov pc, lr

