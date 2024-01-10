section .data
	hello: db "hello", 10
	hello2: db "hello2", 10
	hello3: db "hello3", 10
	hello4: db "hello4", 10
	hello5: db "hello5", 10
	hello6: db "hello6", 10
	hello7: db "hello7", 10
	hello8: db "hello8", 10
	hello9: db "hello9", 10
	helloa: db "helloa", 10
	hellob: db "hellob", 10
	helloc: db "helloc", 10
	hellod: db "hellod", 10
	helloe: db "helloe", 10
	hellof: db "hellof", 10
section .text
	global _main
_main:
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello
	mov rdx, 5
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello2
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello3
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello4
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello5
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello6
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello7
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello8
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hello9
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, helloa
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hellob
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, helloc
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hellod
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, helloe
	mov rdx, 6
	syscall
	mov rax, 0x02000004
	mov rdi, 1
	mov rsi, hellof
	mov rdx, 6
	syscall
	mov rax, 0x02000001
	mov rdi, 69
	syscall
