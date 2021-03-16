BITS 64

global _start

;-x-x-x-x- CONSTANTS -x-x-x-x-;
SYS_WRITE   equ 0x1         ; 1
KEY_ADDR    equ 0x1b        ; 16
;-x-x-x-x- CONSTANTS -x-x-x-x-;

section .text
_start:
	push rax
	push rcx
	push rdx
	push rdi

	jmp	parasite
	ys:	db	"x_x", 0xa

parasite:
	xor	rax, rax
	add	rax, SYS_WRITE
	mov rdi, rax
	lea rsi, [rel ys]
	xor rdx, rdx
	mov dl, 4
	syscall

ender:
	pop rdi
	pop rdx
	pop rcx
	pop rax
	
	push r12

	xor r12, r12
	xor r10, r10
	mov r12, 0xAAAAAAAAAAAAAAAA
	lea r10, [rel _start - KEY_ADDR]
	sub r10, r12

	pop r12

	jmp	r10
