2021.04.07 평가 후기

subject : casting을 이해하고 있는지 묻는 과제

ex00 - 원래의 c언어에서처럼 int를 char로 캐스팅하는 등의 형변환이 가능한 형태인지를 보고 -> 변환해서 -> 출력해서 보여주는 문제.

ex01 - like the case of making bmp image file, make ramdonly mixed string and make it to original string again.

serialize : 직렬화
직렬화(直列化) 또는 시리얼라이제이션(serialization)은 컴퓨터 과학의 데이터 스토리지 문맥에서 **데이터 구조나 오브젝트 상태**를 동일하거나 다른 컴퓨터 환경에 저장(이를테면 파일이나 메모리 버퍼에서, 또는 네트워크 연결 링크 간 전송)하고 나중에 재구성할 수 있는 포맷으로 **변환**하는 과정이다.

즉, 메모리나 저장공간에 담을 수 있도록 직렬화 한다는 것으로 객체를 메모리나 저장매체에 저장하거나 상대방에게 전송하기 위해 일렬로 만드는 것을 의미한다. 거꾸로 얘기하면, 일반적인 객체는 저장하거나 통신 데이터로 사용할 수 없다는 말이 된다.

"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
==> 이걸 가져다가 

==> rand() % len 으로 임의로 뽑아서 진행하는 서브젝트. 함수는 의외로 serialize와 deserialize 두개만 있으면 된다.


ex02 - 부모 클래스를 상속받은 자식클래스들에게 각각 다른 타입을 선언했을 때, 제대로 캐스팅이 되어서 문제없이 호출이 되는지를 보는 문제.
