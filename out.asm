section .data
	Hello: db "Hello", 10
section .bss
section .text
	global _main
_main:
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, Hello
	mov rdx, 5
	syscall
	mov rax, 0x02000001
	mov rdi, 0
	syscall
