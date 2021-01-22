section .text
	global _ft_strcmp

_ft_strcmp:
	xor	rcx, rcx
	jmp compare

;rdi, rsi, rdx
compare:
	cmp	BYTE[rdi + rcx], 0
	je	exit
	cmp BYTE[rsi + rcx], 0
	je	exit
	cmp	BYTE[rdi + rcx], [rsi + rcx]
	jne	exit
	inc	rcx
	jmp	compare
	
exit:
	mov	al, BYTE[rdi + rcx]
	mov	bl, BYTE[rsi + rcx]
	sub al, bl
	movzx rax, al
	ret