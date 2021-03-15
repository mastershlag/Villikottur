BITS 64

global hello
extern helloC

section .text

message:	db	"hello :)", 0xa

hello:
	call helloC

hope: db 0x48, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xeb, 0x08, 0xff, 0xff, 0x48, 0x31, 0xc0, 0xeb, 0xf7, 0xe8
; 	jmp bye_decompiler+1
; bye_decompiler: db 0xE9
	; mov rax, 0xffff08ebffffffff
	xor	rax, rax
	add	rax, 1
	mov rdi, rax
	lea rsi, [rel message]
	xor rdx, rdx
	mov dl, 9
	syscall
	ret



; 	jmp bye_decompiler+1
; bye_decompiler: db 0xE9
; 	xor	rax, rax
; 	jmp bye_decompiler2+1
; bye_decompiler2: db 0xE9
; 	add	rax, 1
; 	jmp bye_decompiler3+1
; bye_decompiler3: db 0xE9
; 	mov rdi, rax
; 	jmp bye_decompiler4+1
; bye_decompiler4: db 0xE9
; 	lea rsi, [rel message]
; 	jmp bye_decompiler5+1
; bye_decompiler5: db 0xE9
; 	xor rdx, rdx
; 	jmp bye_decompiler6+1
; bye_decompiler6: db 0xE9
; 	mov dl, 9
; 	jmp bye_decompiler7+1
; bye_decompiler7: db 0xE9
; 	syscall
; 	ret

