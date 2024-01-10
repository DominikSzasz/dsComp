section .data
	hello: db "hello", 10
section .text
	global _main
_main:
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello
	mov rdx, 5
	syscall
	mov rax, 0x02000001
	mov rdi, 0
	syscall
