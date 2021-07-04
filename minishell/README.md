# minishell이란
* You must program a mini UNIX command interpreter.
* 명령 프롬프트(ex. $> )를 띄우고 사용자가 command line을 입력할 때 까지 기다려야 한다.
* 프롬프트는 명령이 완전히 실행된 후에만 다시 표시된다.
* PATH 변수 및 상대/절대 경로에 기반한 실행 파일(The executable)을 올바르게 찾아 실행한다.
* 실행 파일을 찾을 수없는 경우 오류 메시지를 표시하고 프롬프트를 다시 표시해야 한다.
* 다음과 같은 기능을 bash와 동일하게 동작하도록 구현한다.
```
echo (with option -n)
cd (with only relative or absolute path)
pwd
export
unset
env (without any options and any arguments)
exit
multiline commands를 제외한 ' , "
' 또는 " 가 홀수개로 들어오면 사용자 입력을 기다리게 되는데 이건 구현 안해도 된다는 뜻.
file descriptor aggregation를 제외한 리다이렉션(<, >, >>)
파이프(|)
환경변수($ followed by characters)
$?
ctrl-C, ctrl-D, ctrl-\
```
## Allowed Functions
```
malloc, free
read, write, open, close,
opendir, readdir, closedir
getcwd, chdir
stat, lstat, fstat
fork, execve
wait, waitpid, wait3, wait4
signal, kill
exit
strerror, errno
dup, dup2, pipe
```
위의 함수의 자세한 사용방법은
> https://silverzoo-igutjgut.tistory.com/35
여기에 정리해두었습니다.
