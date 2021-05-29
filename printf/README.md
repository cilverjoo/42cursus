# ft_printf란
c의 <stdio.h>에서 사용할 수 있는 printf 함수를 구현해보는 과제입니다.

## 구현 내용
* ft_printf("%[flags][width][precision][cspdixX%]") 형태로 구현할 것.
* conversion specifier : c - char, s - char*, p - 주소의 16진수 값, d/i - int, x/X - 16진수 소문자/대문자
* flag : 0, -만 구현
