section .text
	global _ft_strcmp

_ft_strcmp:
	xor rax, rax
	xor	rcx, rcx
	jmp compare

;rdi, rsi, rdx
compare:
	mov	al, BYTE[rdi + rcx]
	cmp	al, 0
	je	exit
	mov bl, BYTE[rsi + rcx]
	cmp bl, 0
	je	exit
	cmp	al, bl
	jne	exit
	inc	rcx
	jmp	compare
	
exit:
	mov bl, BYTE[rsi + rcx]
	sub al, bl
	movsx rax, al
	ret
