section .text
	global _start

_start:
	mov rax, 0
	jmp	ft_strlen

ft_strlen:
	cmp BYTE [rdi + rax], 0
	je	exit
	inc	rax
	jmp	ft_strlen

exit:
	retld
