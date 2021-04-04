# 1. Philosopher 서브젝트 정리
## 1. 다음의 기본 규칙들을 따르며 3가지 프로그램을 만들어라
* 철학자들은 원형 테이블에 앉아서 다음의 세가지 행동 중 하나를 하고 있다 : eating, thinking or sleeping
* 테이블 위에는 가운데에 스파게티 그릇과, 몇몇의 포크가 있다.
* 스파게티를 포크 하나로 주거나 먹기 힘들기 때문에 철학자들에게는 두 개의 포크로만 먹을 수 있다고 가정하자.
* 철학자는 절대 굶어서는 안 되며 모든 철학자들이 식사를 해야 한다.
* 철학자는 다른 철학자가 언제 죽을지 모른다.
* 철학자가 식사를 끝내면 포크를 내려놓고 잠을 잘 것이다.
* 잠을 다 자면 철학자는 생각을 시작한다.
* 이 시뮬레이션은 한 철학자가 죽을 때까지 계속된다.
* 각 프로그램은 같은 선택지를 가져야 한다
	+ number_of_philosophers: 철학자들의 수이자 포크의 갯수
	+ time_to_die: 수 밀리초 안에 철학자가 'time_to_die'를 먹는것을 시작하지 않으면 그의 마지막 식사를 시작하거나 시뮬레이션이 시작한 지 수 초 안에 철학자는 죽는다.
	+ time_to_eat: 수 밀리초 이내이며 철학자가 먹는 데 걸리는 시간이다. 이 시간동안 철학자는 두 개의 포크를 가지고 있어야 한다.
	+ time_to_sleep: 수 밀리초 이내이며 철학자가 잠을 자는 데 걸리는 시간이다.
	+ number_of_times_each_philosopher_must_eat: 선택적으로 매개변수가 주어지며, 만약 모든 철학자들이 최소 'number_of_times_each_philosopher_must_eat'를 먹으면 시뮬레이션은 중지된다. 명시되지 않으면, 시뮬레이션은 한 철학자가 죽을 때만 멈춘다.
* 각 철학자들은 1부터 'number_of_philosophers'까지의 숫자가 주어져야 한다.
* 철학자1은 철학자'number_of_philosopher'의 옆에 있다. 철학자N은 철학자N-1과 철학자 N+1 사이에 있다.
* 철학자의 상태 변화는 다음과 같아야 한다. (X는 철학자 번호로, timestamp_in_ms는 밀리 초 단위의 현재 timestamp 값으로 대체될 수 있다)
	+ timestamp_in_ms X has taken a fork
	+ timestamp_in_ms X is eating
	+ timestamp_in_ms X is sleeping
	+ timestamp_in_ms X is thinking
	+ timestamp_in_ms X died
* 출력될 상태는 다른 철학자의 상태와 섞여서는 안 된다.
* 철학자의 죽음과 그 죽음을 인쇄 할 때 걸리는 시간은 10ms를 초과 할 수 없다.
* 철학자는 죽는 것을 피해야 한다!

## 2. 작성할 프로그램
* philo_one
	+ 각 철학자 사이에 포크가 하나씩 있으므로 각 철학자의 오른쪽과 왼쪽에 포크가 있습니다.
	+ 철학자가 포크를 복제하지 않도록하려면 각각에 대한 Mutex를 사용하여 포크 상태를 보호해야합니다.
	+ 각 철학자는 a thread 여야 한다.
	+ 허용 함수 : memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
* philo_two
	+ 모든 포크는 테이블 중앙에 있다.
	+ 메모리에 상태는 없지만 사용가능한 포크의 수는 semaphore로 표시된다.
	+ 각 철학자는 a thread 여야 한다.
	+ 허용 함수 : memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, sem_open, sem_close, sem_post, sem_wait, sem_unlink
* philo_three
	+ 모든 포크는 테이블의 중앙에 있다.
	+ 메모리에 상태는 없지만 사용가능한 포크의 수는 semaphore로 표시된다.
	+ 각 철학자는 process 여야 하며 메인 process는 철학자여서는 안 된다.
	+ 허용 함수 : memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink



# 2. philo_one

* mutex(Mutual Exclusion, 상호배제)란?

	+ mutex 는 여러개의 쓰레드가 공유하는 데이타를 보호하기 위해서 사용되는 도구로써, 보호하고자 하는 데이터를 다루는 코드영역을 단지 '한번에 하나의 쓰레드만' 실행가능 하도록 하는 방법으로 데이터를 보호한다. 
	+ 이러한 코드영역(하나의 쓰레드만 점유가능한)을 critical section 이라고 한다.

* critical section(임계구역)이란?

	+ 임계 구역(critical section) 또는 공유변수 영역은 병렬컴퓨팅에서 둘 이상의 스레드가 동시에 접근해서는 안되는 공유 자원(자료 구조 또는 장치)을 접근하는 코드의 일부를 말한다. 때문에 어떤 스레드(태스크 또는 프로세스)가 임계 구역에 들어가고자 한다면 지정된 시간만큼 또는 lock이 풀릴 때까지 대기해야 한다. 스레드가 공유자원의 배타적인 사용을 보장받기 위해서 임계 구역에 들어가거나 나올때는 세마포어 같은 동기화 매커니즘이 사용된다.
	+ 각 프로세스는 자신의 임계 구역에 진입하려면 진입허가를 요청해야 한다. 이런 요청을 구현하는 코드 부분을 입장 구역(entry section)이라고 한다. 입장 구역에서 기다리다가 진입 허가가 나면 임계 구역에 들어간다. 임계 구역 이후에는 임계 구역을 빠져나왔음을 알리는 코드 부분인 퇴장 구역(exit section)이 있다. 또한, 그밖의 나머지 코드 부분들을 총칭하여 나머지 구역(remainder section)이라 한다.


* pthread_t의 구조

	#define __PTHREAD_SIZE__		8176

	struct __darwin_pthread_handler_rec {
		void (*__routine)(void *);						// Routine to call
		void *__arg;									// Argument to pass
		struct __darwin_pthread_handler_rec *__next;
	};

	struct _opaque_pthread_t {
		long __sig;
		struct __darwin_pthread_handler_rec  *__cleanup_stack;
		char __opaque[__PTHREAD_SIZE__];
	};

	typedef struct _opaque_pthread_t *__darwin_pthread_t;

	typedef __darwin_pthread_t pthread_t;


- pthread_t는 현재 쓰레드의 식별자 정보를 담고 있다.


* pthread_mutex_t의 구조

		#define __PTHREAD_MUTEX_SIZE__		56

		struct _opaque_pthread_mutex_t {
			long __sig;
			char __opaque[__PTHREAD_MUTEX_SIZE__];
		};

		typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;

		typedef __darwin_pthread_mutex_t pthread_mutex_t;

- pthread_mutex_t는 현재 mutex의 식별자 정보를 담고 있다.


## 1. usleep

	int usleep(useconds_t microseconds);

* 헤더 : <unistd.h>

* microseconds : 몇 microseconds(1/1000000 초) 기다리게 할건지 입력.
* 1microseconds = 0.001miliseconds이므로 usleep(100)은 0.1miliseconds 동안 기다리라는 말이 된다.

* sleep보다 더 정밀하게 시간을 조절하고 싶을 때 사용한다.


## 2. gettimeofday

	int gettimeofday(struct timeval *tv, struct timezone *tz);
	int settimeofday(const struct timeval *tv, const struct timezone *tz);

* 헤더 : <sys/time.h>

* 매개변수
	첫번째 매개변수인 tv는 현재 시스템 시간을 저장하기 위한 구조체로 다음과 같이 정의되어 있다.
<pre>
<code>
struct timeval
{
    long tv_sec;       // second since Jan. 1, 1970
    long tv_usec;      // 마이크로세컨드 - 1/1,000,000초 사용, 밀리세컨드 - 1/1000초
}
</code>
</pre>

두번째 매개변수인 tz은 타임존을 설정하기 위해서 사용되었으나, 그냥 사용하지 말자.
두번째 매개변수는 NULL을 넣어주자.

* 반환값 : 성공하면 0, 실패하면 -1.


## 3. pthread_create

	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

* 새로운 쓰레드를 생성한다.
* routine이 return되면, routine의 리턴값을 exit_status로서 pthread_exit()을 부른것과 같다.
* 헤더 : <phread.h>

* 매개변수
	+ 첫 번째 매개변수인 thread는 생성된 thread를 인식하기 위한 식별자.
	+ 두 번째 매개변수 *attr은 쓰레드의 특성을 지정하기 위해 사용하며, 기본 쓰레드 특성을 사용할 경우 NULL을 준다.
	+ 세 번째 매개변수 start_routine은 분기시켜서 실행할 쓰레드 함수이다.
	+ 네 번째 매개변수 arg는 start_routine 쓰레드 함수의 매개변수로 넘겨진다.

* 반환값 : 성공하면 0, 실패하면 errno

<pre>
<code>

int value = 0;
void *runner(void *param);

int 				main(int ac, char **av)
{
	pid_t 			pid;
	pthread_t 		tid;
	pthread_attr_t	attr;

	pid = fork();

	if (pid == 0)
	{
		pthrad_attr_init(&attr);
		pthread_create(&tid, &attr, runner, NULL);
		pthread_join(tid, NULL);
		printf("CHILD : value = %d\n", value);
	}
	else if (pid > 0)
	{
		wait(NULL);
		printf("PARENT : value = %d\n", value);
	}
}

void 				*runner(void *param)
{
	value = 5;
	pthread_exit(0);
}

</code>
</pre>

	CHILD : value = 5;
	PARENT : value = 0;

<pre>
<code>

void			*runner(void *param);

int 			main(int ac, char **av)
{
	pid_t		pid;
	pthread_t	tid;

	printf("A = %d\n", getpid());
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);			//parent process waits until child process finished.
		printf("B = %d\n", pid);
	}
	if (pid == 0)
	{
		pid = fork();
		if (pid > 0)
		{
			wait(NULL);
			printf("C = %d\n", pid);
		}
		pthread_create(&tid, NULL, runner, NULL);
	}
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		printf("D = %d\n", pid);
	}
}

void		*runner(void *param)
{
	printf("I'm a thread\n");
	pthread_exit(0);
}
</code>
</pre>

	A = 18937
	I'm a thread!
	D = 18941
	C = 18939
	I'm a thread!
	D = 18943
	B = 18938
	D = 18944

* Thread Pools
create a number of threads in a pool where they await work.
* Fork & Join
explicit threading, but an excellent candidate for implicit threading.


## 4. pthread_detach

	int pthread_detach(pthread_t thread);

* pthread_create를 사용하면 쓰레드가 종료되어도 사용했던 자원들을 해제하지 않는다. pthread_join을 사용하면 쓰레드가 종료될 때 까지 **기다렸다가** 종료시점이 되면 자원을 반납하는데, join처럼 종료될 때 까지 대기하지 않고 분리하여 별도로 실행시키고, 종료되면 자동으로 자원을 반납하게 하고 싶다면 pthread_detach를 사용하면 된다.

* 헤더 : <pthread.h>

* 매개변수 thread는 thread를 구분하는 식별자!

* 사용법

	thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	pthread_detach(thr_id);

* 반환값 : 성공하면 0, 실패하면 errno.
* 현재 자원을 점유하고 있는 쓰레드를 확인하고 싶다면 다음 명령어를 입력해보자.

	while [ 1 ]; do ps -aux | grep pthread | grep -v grep | grep -v vim; sleep 1; done


## 5. pthread_join

	int pthread_join(pthread_t th, void **thread_return);

* 쓰레드가 종료될 때까지 기다렸다가 쓰레드에 할당된 리소스를 해제시킨다. 

* 헤더 : <phtread.h>

* 사용법

	thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	pthread_join(p_thread, (void *)&result);

* 매개변수

	첫번째 매개변수 th 는 기다릴 쓰레드의 식별자.
	두번째 매개변수 thread_return 은 쓰레드의 리턴값. thread_return이 NULL이 아닌 경우 해당 포인터로 쓰레드의 리턴 값을 받아올 수 있다.  

* 반환값 : 성공하면 0, 실패하면 errno


## 6. pthread_mutex_init

	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

* 헤더 : <pthread.h>

* pthread_mutex_init는 첫 번째 인자로 주어지는 mutex를 초기화하고, 두 번째 인자를 통해서 그 속성을 변경시킬 수 있다.

* 매개변수

	첫 번째 매개변수 mutex는 초기화 받을 mutex 객체의 주소.
	두 번째 매개변수 attr을 통해 초기화 할 뮤텍스의 특징을 정의할 수 있다.
	mutex 특성(종류) 에는 "fast", "recurisev", "error checking"가 있으며, 디폴트으로 "fast" 가 사용된다. 디폴트값을 사용하려면 NULL을 넘겨주면 된다.

* 반환값 : 항상 0을 리턴한다.

- mutex를 초기화 하는 데에는 정적 방식과 동적 방식이 존재한다. 정적 방식은 

	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER

와 같이 상수롤 통해서 초기화 하는 방식이고 동적 방식은 위와 같이 pthread_mutex_init 함수를 사용하는 방식이다.
동적 방식을 사용했다면 pthread_mutex_destroy(&mutex)를 사용해서 mutex 객체를 해제시켜줘야 한다.


## 7. phread_mutex_destroy

	int pthread_mutex_destroy(pthread_mutex_t *mutex);

* 헤더 : <phtread.h>

* mutex 객체를 삭제하고 자원을 반환한다. 쓰레드가 종료되었다고 하더라도 mutex는 그대로 남아있으므로 mutex를 더 이상 사용하지 않는다면 이 함수를 호출해 삭제해줘야 한다.

* 매개변수 : 리소스를 해제할 mutex 객체의 주소.

* 반환값 : 성공하면 0, 실패하면 errno


## 8. phread_mutex_lock

	int pthread_mutex_lock(pthread_mutex_t *mutex);

* 임계 구역에 진입하기 위해 mutex 잠금을 요청. 임계 구역에 이미 다른 쓰레드가 진입해 lock을 건 상태라면 임계 구역을 나올 때까지 (pthread_mutex_unlock이 호출될 때까지) 기다린다.

* 반환값

	EINVAL
	뮤텍스가 잘못 초기화 되었다.

	EDEADLK
	이미 잠금을 얻은 쓰레드가 다시 잠금을 요청할 때 (error checking 뮤텍스일 경우 사용할 수 있다)
	
* 예제

	#include <pthread.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>

	pthread_mutex_t mutex;
	int cnt=0;

	void *count(void *arg)
	{
		int i;
		char* name = (char*)arg;

		pthread_mutex_lock(&mutex);

		//======== critical section =============
		cnt=0;
		for (i = 0; i <10; i++)
		{
			printf("%s cnt: %d\n", name,cnt);
			cnt++;
			usleep(1);
		}
		//========= critical section ============
		pthread_mutex_unlock(&mutex);
	}

	int main()
	{
		pthread_t thread1,thread2;

		pthread_mutex_init(&mutex,NULL);

		pthread_create(&thread1, NULL, count, (void *)"thread1");
		pthread_create(&thread2, NULL, count, (void *)"thread2");

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

		pthread_mutex_destroy(&mutex);
	}


## 9. pthread_mutex_unlock

	int pthread_mutex_unlock(pthread_mutex_t *mutex);

* mutex 잠금을 해제한다. 만약 fast 뮤텍스라면 pthread_mutex_unlock()는 언제나 unlocked 상태를 되돌려준다. recursive 뮤텍스라면 잠겨있는 뮤텍스의 수를 감소시키고 이 수가 0이 된다면 뮤텍스잠금을 되돌려주게 된다.


# 3. philo_two

* semaphore란?

* semaphore와 mutex의 차이점
	+ mutex는 동시 접근 동기화라면, semaphore는 접근 순서 동기화에 더 관련있다.
	+ mutex는 상호 배제를 함으로써 임계구역에 하나의 쓰레드만 들어갈 수 있다. semaphore는 하나의 쓰레드(binary semaphore)만 들어가거나 여러 개의 쓰레드(counting semaphore)가 들어가게 할 수 있다.
	+ semaphore는 mutex가 될 수 있지만 mutex는 semaphore가 될 수 없다.
	+ semaphore는 소유할 수 없는 반면 mutex는 소유할 수 있고 소유자가 이에 책임을 진다.
	+ mutex는 1개만 동기화가 되지만 semaphore는 하나 이상을 동기화 할 수 있다.

## 1. sem_open

	sem_t * sem_open( const char * sem_name, int oflags, ... );

* 헤더 : <semaphore.h>

* 매개변수

	+ sem_name : 생성 또는 접근하고자 하는 semaphore의 이름
	+ oflags : semaphore 생성시 플래그. O_CREAT, O_EXCL 두 가지만 가능하다.

		O_CREAT : sem_name이 존재하지 않으면 semaphore를 생성한다.
		O_EXCL : 생성하려는 semaphore가 이미 존재하면 에러.

	+ ... : O_CREAT 플래그를 사용하면 추가적으로 두 매개변수를 받을 수 있다.
		- mode_t mode : 플래그를 O_CREAT로 설정하면, mode 매개변수를 받을 수 있다. <sys/stat.h> 를 인클루드 하면 아래 상수들을 활용할 수 있다.

			S_IRWXR : 그룹 접근

			S_IRWXO : 타인 접근

			S_IRWXU : 개인 접근

			0644  의미 :
			소유자를위한 6 (읽기 및 쓰기)
			다른 그룹 사용자의 경우 4 (읽기 전용)
			다른 사람을 위한 4 (읽기 전용)

		- unsigned int value :  semaphore 초기 값으로 0 보다 큰 양수여야 한다. unlock된  semaphore의 수를 의미한다. 이 값은 SEM_VALUE_MAX를 초과할 수 없다.

	* semaphore를 생성하면 초기 value는 1이다.

* 반환값 : 실패시 SEM_FAILED 값을 리턴하고 errno를 설정한다. 성공시 semaphore descriptor를 반환한다.


## 2. sem_close

	int sem_close( sem_t *sem );

* semaphore의 사용을 종료하고 할당된 자원을 해제한다. 
* 헤더 : <semaphore.h>


## 3. sem_post

	int sem_post(sem_t *sem);

* sem이 참조하 semaphore가 unlock되고 semaphore의 value가 1 증가하며 semaphore에서 대기중인 스레드가 깨어난다.

## 4. sem_wait

	int sem_wait(sem_t *sem);

* semaphore를 lock하고 semaphore의 value값이 1 감소한다.
* 만약 sem_wait에서 받은 sem의 value가 0이라면 sem이 증가하거나 signal을 받을 때까지 wait호출자는 block(대기)상태가 된다.

* 반환값 : 성공하면 0, 실패시 -1을 리턴하고 errno에 다음과 같은 에러값이 설정되며, semaphore의 상태는 변하지 않는다.

	EAGAIN : semaphore가 이미 lock 되어 있다.

	EDEADLK : deadlock이 있을 때.

	EINTR : signal에 의해 call이 interrupt 될 때.

	EINVAL : sem이 사용가능한 상태가 아닐 때.


## 5. sem_unlink

	int sem_unlink(const char *name);

* name에 해당하는 semaphore를 제거한다. 만약  semaphore가 다른 프로세스에 의해 사용중이라면, name은 즉시 semaphore와 연결이 해제되지 semaphore 자체는 모든 참조가 해제될 때까지 제거되지 않는다. 이후에 이 name을 사용하여 sem_open을 호출하면 이름만 같은 새로운 semaphore가 생성된다.

* 반환값 : 성공하면 0, 실패하면 -1을 리턴하고 errno에 다음과 같은 에러값이 설정된다. semaphore의 상태는 변하지 않는다.

	EACCES : 이 semaphore를 제거할 권한이 없을 때
	
	ENAMETOOLONG : semaphore의 이름이 너무 길 때
	
	ENOENT : 이 이름의 semaphore가 존재하지 않을 때


# 4. philo_three

## waitpid

	pid_t waitpid(pid_t pid, int *status, int options);

* waitpid 함수는 인수로 주어진 pid 번호의 자식프로세스가 종료되거나, 시그널 함수를 호출하는 신호가 전달될때까지 waitpid 호출한 영역에서 일시 중지 된다. 

* 헤더 : <sys/wait.h>



# 5. 참고
* https://selvarajahkesavan.medium.com/the-dining-philosophers-problem-de586df365bc

