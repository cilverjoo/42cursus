section .text
	global _ft_read
	extern ___error

; ft_read (rdi, rsi, rdx)
_ft_read:
	mov	rax, 0x2000003
	syscall
	jc	error
	ret

error:
	push	rax			;error value in rax -> backup in stack
	call	___error	;error's address stored in rax
	pop		rdx			;bring error value which was in rax
	mov		rax, rdx
	mov		rax, -1
	ret