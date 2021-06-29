## casting

#### ex00 : static_cast
* 임의의 숫자가 인자로 주어질 때, static_cast를 사용하여 char, int, float, double로 잘 변환할 수 있는지를 물어보는 문제.

#### ex01 : reinterpret_cast
* like the case of making bmp image file, make ramdonly mixed string and make it to original string again.
* serialize(직렬화) : 직렬화(直列化) 또는 시리얼라이제이션(serialization)은 컴퓨터 과학의 데이터 스토리지 문맥에서 **데이터 구조나 오브젝트 상태**를 동일하거나 다른 컴퓨터 환경에 저장(이를테면 파일이나 메모리 버퍼에서, 또는 네트워크 연결 링크 간 전송)하고 나중에 재구성할 수 있는 포맷으로 **변환**하는 과정이다.
* 즉, 메모리나 저장공간에 담을 수 있도록 직렬화 한다는 것으로 객체를 메모리나 저장매체에 저장하거나 상대방에게 전송하기 위해 일렬로 만드는 것을 의미한다. 거꾸로 얘기하면, 일반적인 객체는 저장하거나 통신 데이터로 사용할 수 없다는 말이 된다.
* 문자열 + int + 문자열의 raw 데이터를 void 포인터로 변환하여 다시 원래의 형태로 변환했을 때, 그 형태가 이전과 같은지 확인해보면서 reinterpret_cast의 동작 방법을 이해해보는 문제.

#### ex02 : dynamic_cast
* Base 클래스를 상속받은 A, B, C 클래스가 존재할 때, Base 클래스가 성공적으로 A, B, C 클래스로 변환되는지 dynamic_cast를 통해서 확인해보는 문제.
