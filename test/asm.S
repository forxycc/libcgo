/*
 * %rdi、%rsi、%rdx，%rcx、%r8、%r9
 */ 

.data
.global startn
startn:
.long 4

.global teststack
teststack:
	push %rbp
	mov %rsp, %rbp

	sub $288, %rsp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp
	push %rbp


	add $448, %rsp

	mov -448(%rbp),%rax
	mov (%rax), %rax

	mov -440(%rbp),%rax
	mov (%rax), %rax

	mov -432(%rbp),%rax
	mov (%rax), %rax

	mov -424(%rbp),%rax
	mov (%rax), %rax

	mov -416(%rbp),%rax
	mov (%rax), %rax

	mov -408(%rbp),%rax
	mov (%rax), %rax

	mov -400(%rbp),%rax
	mov (%rax), %rax

	mov -392(%rbp),%rax
	mov (%rax), %rax

	mov -384(%rbp),%rax
	mov (%rax), %rax

	pop %rbp
	retq
