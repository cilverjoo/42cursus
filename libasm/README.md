# Libasm이란?
- c의 문자열 처리 함수 strcmp, strcpy, strdup, strlen 등을 인텔 어셈블리어로 구현한다.
- x86-64 Intel Assembly 문법 규칙을 따라야 하며 함수 호출 규약을 따라야 한다.
- nasm 명령어로 컴파일하여야 한다.
- 한줄로 작성해선 안되며, '.s' 파일로 저장해야 한다.

### 주의사항
- 함수에서 매개변수는 rdi, rsi, rdx, rcx, r8, r9로 넘어 오게 된다.
- 함수 호출 규약에 따라 Callee(호출당하는 함수)는 RBX, RSI, RDI, RBP를 사용 후 초기값으로 돌려놓아야 한다.
- .s파일을 오브젝트 파일로 만들 때  옵션은 nasm -f macho64
- 디스어셈블 방법:
    1. -g 플래그 붙여서 컴파일
    2. gdb -q 실행파일
    3. set disassembly-flavor intel
    4. disassemble 함수명

### 학습 내용
> 개인블로그 : https://silverzoo-igutjgut.tistory.com/31

### 참고 링크
- https://www.notion.so/Libasm-3c94bbc7df234499b012f6ae82b84dc2
- https://www.notion.so/Libasm-f4869fe5de17402b9054a7ca06bfc79c
