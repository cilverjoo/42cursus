//sem_open(forks, O_EXCL)
//포크를 사용중일 때 --> sem_wait()
//포크 사용 해제시 --> sem_post()
// deadlock과 starvation을 방지하려면 어떻게 해야하는가?
// mornitor solution
// -만약 양쪽 포크가 모두 사용가능할 때만 포크를 집어들게 하라.
// - 세 가지 상태를 구분하고
// - 포크가 사이에만 존재할 경우에는 양 옆이 먹고있지 않을 때만 eating 상태로 전환이 가능.

#include <sys/stat.h>
#include <semaphore.h>
