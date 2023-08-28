# 42cursus
42Seoul에서 진행한 서브젝트들의 소스코드와 어떤 내용을 학습했는지 정리한 저장소입니다. 과제 별 자세한 설명은 과제 내 README.md로 다시 정리해 두었습니다.

## libft
- c의 <string.h>에서 사용하는 문자열 처리 함수들과 연결리스트의 생성 및 수정과 관련된 함수들을 직접 구현해보는 과제입니다.

## getnextline
- 임의의 파일이 입력으로 들어온다고 할 때, 호출될 때마다 '\n'을 기준으로 한 줄씩 리턴해주는 함수인 getnextline을 구현하는 과제입니다.
- 복수의 fd와 임의의 BUFFER_SIZE를 받는다고 가정할 때, read를 통해 읽은 buffer 안에서 '\n'을 찾아 그 앞까지의 내용을 리턴하거나, 새로 BUFFER_SIZE만큼 '\n'이 나올 때까지 읽습니다.
- 실행될 때마다 다음 줄을 반환해야 하므로 아직 return되지 않은, read를 통해 읽은 내용을 static 변수로 저장해둡니다.

## ft_printf
- c언어의 <stdio.h>의 printf를 구현하는 과제입니다.
- %c, %s, %d, %x, %X, %u, %%와 같은 형식의 구조를 이해하고 *, 0, -와 같은 플래그를 활용하며 width와 precision을 활용해 출력까지 할 수 있어야 합니다.

## cub3D
- 최초의 3D 게임 울펜슈타인과 같은 형식의 그래픽을 구현해보는 과제입니다.
- raycasting을 이해하여 특정 키를 눌러 플레이어가 이동할 때, 벽과 플레이어 사이의 거리를 기준으로 3D 맵을 구현해야 합니다.
- 동, 서, 남, 북의 벽 텍스처를 다르게 설정하고, 구현해야 하는 map의 지도가 사방이 벽으로 둘러싸인 구조가 맞는지 먼저 체크한 다음에 플레이 화면으로 넘어가야 합니다. dfs를 이해할 수 있어야 합니다.
- ./cub3D map.cub --save 와 같은 형식으로 실행할 때는 새로운 윈도우를 띄우지 않고 첫 플레이 화면을 bmp 파일로 만들어 저장해야 합니다.
- 플레이어가 이동하면서 발생할 수 있는 모든 에러를 방지해야 합니다.

## ft_server
- Kubernetes를 활용하여 wordpress, phpmyadmin, nginx, mysql을 연결해보는 과제입니다.
- Docker로 생성한 이미지로 컨테이너를 실행시켰을 때 localhost에서 wordpress, phpmyadmin이 nginx를 기반으로 잘 연결되는지 확인되어야 합니다.


## minishell
- 경량 bash를 구현해보는 과제입니다.
- echo, pwd, export, unset 등의 일부 명령어는 직접 구현하고, 그 외의 명령어는 execve와 pipe를 활용하여 구현하면 됩니다.
- |(파이프), ;(세미콜론), >, >> (리다이렉션)을 구현해야 합니다.
- fork를 통한 process의 이해, dup2 함수를 통한 fd의 input과 output의 연결 및 교환, execve함수를 통한 path와 상대경로, 절대경로 명령어의 실행방법에 대한 이해를 할 수 있습니다.

## libasm
- intel 어셈블리어를 활용하여 문자열 처리 함수를 구현해보는 과제입니다.

## ft_services
- Kubernetes를 활용하여 nginx, phpmyadmin, wordpress, grafana, influxdb, mysql, ftps를 파드별로 상태관리를 하고 연결해보는 과제입니다.
- mysqld, influxd는 파드가 죽어도 이전에 저장되었던 데이터의 내용이 휘발되면 안 되므로 적절한 처리가 필요합니다. 저는 supervisord를 실행시켜두고 volume의 타입을 Retain으로 고정해주었습니다.
- ClusterIP, NodePort 등 서비스 타입에 대한 이해가 필요하며, 외부에 노출할 서비스와 내부에서만 ClusterIP로 연결되는 서비스를 엄밀하게 분리해줘야 합니다.
- Pod, Service, Deployment의 개념을 이해하고, Kubernetes 내부에서 생성되는 메트릭 정보를 grafana로 모니터링하며 Volume의 특성을 이해하고 휘발되지 않는 데이터를 저장하려면 어떻게 해야하는지 적절한 처리를 해 줘야 합니다.

## pushswap
- 임의의 int 배열이 stack으로 주어질 때, 최소한의 명령어를 사용하여 stack 내의 element들을 정렬시키는 알고리즘을 짜는 과제입니다.

## philosophers
- 임의의 수의 철학자들과, 그 철학자들의 수와 동일한 포크가 주어지고 테이블 가운데에는 스파게티가 놓여져있다고 할 때, 모든 철학자들이 주어진 시간 내에 두개의 포크로 식사를 마치고 다른 철학자에게 포크를 넘겨주며 무한 반복할 수 있는 thread / process 구조를 짜는 과제입니다.
- semaphore, mutex, pthread, process에 대한 이해가 필요합니다.
- 라이브러리를 사용하지 않고 직접 MultiThreading, MultiProcessing을 직접 구현해 보면서 병행 처리의 이해를 높일 수 있는 과제입니다.

## moduleCPP(00~08)
- C++를 통해 객체지향프로그래밍을 이해하는 것이 목표인 과제셋입니다.
- 과제 넘버 별로 class, 예외처리, template, 상속 등 주제가 정해져있으므로 순서대로 클리어 해 가면서 객체지향 프로그래밍에 대한 감을 잡을 수 있습니다.
