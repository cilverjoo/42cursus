section .text
	global _ft_read
	extern ___error

; ft_read (rdi, rsi, rdx), rdi = file descriptor, rsi = string, rdx = byte count
_ft_read:
	mov	rax, 0x2000003
	syscall
	jc	error	; error sets carry flag, rax = errno
	ret

error:
	push	rax			;error value in rax -> backup in stack
	call	___error	;error's address stored in rax
	pop		rdx			;bring error value which was in rax
	mov		[rax], rdx  ; put errno in return value of __error (pointer to errno)
	mov		rax, -1
	ret
