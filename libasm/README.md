# Libasm이란?
- c의 문자열 처리 함수 strcmp, strcpy, strdup, strlen 등을 인텔 어셈블리어로 구현한다.
- 인텔의 64비트의 어셈블리어 문법 규칙을 따라야 하며 함수 호출 규약을 따라야 한다.
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

### 1. 레지스터

레지스터는 C언어에서의 변수와 같이 사용됩니다

* 범용 레지스터 (64bit - 32bit - 16bit - up 8bit - down - 8bit)
    - rax (- eax - ax - ah - al)
    - rbx (- ebx - bx - bh - bl)
    - rcx (- ecx - cx - ch - cl)
    - rdx (- edx - dx - dh - dl)
* 포인트 레지스터
    - rsp
    - rbp
* 인덱스 레지스터
    - rsi (src index)
    - rdi (dest index)
* 세그먼트 레지스터
    - cs
    - ds
    - ss
    - es

### 2. syscall

- syscall 명령어를 통해 시스템 상에 미리 선언되어 있는 함수를 호출할 수 있습니다.
- 이 때 syscall 코드는 rax에 들어 있어야 하며 반환값 또한 rax에 저장됩니다.
- syscall 코드는 시스템 마다 다르며 맥은 [https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master] 해당 문서를 참고하십시오.
- syscall 후 에러 발생 시 이는 __error 함수를 이용해 처리해야합니다.
- __error 함수는 sys/errno.h 에 선언되어 있습니다.


### 3. 자료형의 이름

- BYTE : 1 byte (char)
- WORD : 2 byte (short)
- DWORD : 4 byte (int)
- QWORD : 8 byte (double)

다음과 같은 링크에서 도움을 받았습니다.
> https://www.notion.so/Libasm-3c94bbc7df234499b012f6ae82b84dc2
> https://www.notion.so/Libasm-f4869fe5de17402b9054a7ca06bfc79c
