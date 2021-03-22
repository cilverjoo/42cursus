# 1. push_swap Instructions

* 이 프로젝트는 사람에 의해서만 평가되므로 파일을 원하는대로 작성해도 된다.
* 실행가능한 파일은 checker, push_swap이 있어야 한다.
* Makefile 필요, 필요할 때만 다시 컴파일 될 수 있게 해라.
* 개인 라이브러리를 사용한다면 루트에 위치시키고 라이브러리 폴더 안에 Makefile이 있어야 한다. Makefile이 라이브러리를 먼저 컴파일 하고 프로젝트를 컴파일해야 한다.
* 전역변수 금지!
* c언어로 작성하고 Norm을 따를 것.
* 사용가능 함수 : write, read, malloc, free, exit


# 2. Mandatory part
## 1. checker
* int 리스트 형태의 stack A를 인자로 받는다. (순서주의 - 첫 숫자가 스택의 top이다.) 아무 인자도 주어지지 않는다면 checker는 아무것도 하지 않고 종료.
* standard input에 instructions를 입력받으며, 각 인자 다음에 \n 이 온다.
* 모든 instructions를 읽은 다음에 checker는 인자로 받은 stack에 대해서 명령을 실행한다.
* instructions를 모두 실행한 다음에 stackA의 인자들이 정렬되어 있으면 standard output에 OK\n을 출력하고, 그 외의 모든 경우에 KO\n을 출력한다.
* 에러가 발생하면 standard error에 Error\n을 출력 (int 아니거나, int보다 크거나, 중복이거나, instruction이 아닌 값을 넣을 경우)

## 2. push_swap
* int 리스트 형태의 stack A를 인자로 받는다. (순서주의 - 첫 숫자가 스택의 top이다.)
* push_swap은 stack A가 오름차순으로 정렬되도록 가능한 한 적은 수의 instruction의 리스트를 보여줘야 한다.
* instructions\n 형태로 출력
* defence 동안, push_swap이 찾은 instructions의 수와 허용되는 최대작업수를 비교하고, 만약 instruction이 너무 많거나 stack이 제대로 정렬되지 않으면 평가는 종료.
* 에러가 나는 경우의 처리는 checker와 동일.
* 디펜스동안 다음 방법으로 두 가지 프로그램을 써라.

	ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

	ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG




