section .text
    global _ft_strdup
    extern _ft_strlen
    extern _ft_strcpy
    extern _malloc

; ft_strdup(const char rdi)
_ft_strdup:
    push    rdi
    call    _ft_strlen
    inc     rax         ;space's size : len + 1
    mov     rdi, rax    ;give rdi a size to malloc space
    call    _malloc
    cmp     rax, 0      ;check malloc error
    je      exit
    pop     r9         ;give rdi's string(src) to r9
    mov     rdi, rax    ;give malloc space's address
	mov		rsi, r9
    call    _ft_strcpy  ;rdi : dest(malloc space), rsi : src
	ret

exit:
    ret
