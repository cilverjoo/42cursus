section .text
	global _ft_strcpy

_ft_strcpy:
	mov	rcx, 0
	cmp	[rsi + rcx], 0
	jg	copy
	jmp	exit

copy:
	mov	al, BYTE[rsi + rcx]
	mov	BYTE[rdi + rcx], al
	inc	rcx
	cmp	BYTE[rsi + rcx], 0
	jg	copy
	jmp	exit

exit:
	mov	BYTE[rdi + rcx], 0
	mov	rax, rdi
	ret
