section	.text
	global _ft_write
	extern ___error

; ft_write (rdi, rsi, rdx)
_ft_write:
	mov		rax, 0x2000004
	syscall
	jc		error
	jmp		exit

error:
	push	rax			;backup error value
	call 	___error
	pop		rdx			;save error value in rdx
	mov		[rax], rdx	;give error() the error value.
	mov		rax, -1		;return : -1
	ret

exit:
	mov rax, rdx
	ret
