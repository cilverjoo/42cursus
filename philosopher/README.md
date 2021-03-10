1. Philosopher 서브젝트 정리
=========================
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
	+ time_to_sleep: 수 밀리초 이내이며 철학자가 잠을 자는데 걸리는 시간이다.
	+ number_of_times_each_philosopher_must_eat: 선택적으로 인자가 주어지며, 만약 모든 철학자들이 최소 'number_of_times_each_philosopher_must_eat'를 먹으면 시뮬레이션은 중지된다. 명시되지 않으면, 시뮬레이션은 한 철학자가 죽을 때만 멈춘다.
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
	+ 허용 함수 : memset, printf, malloc, free, write, usleep, gettimeofday pthread_create, pthread_detach, pthread_join, pthread_mutex_init pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
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