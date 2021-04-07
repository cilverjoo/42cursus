## 클래스

클론 특수문자와 함께 사용하는 public:을 접근 지정자라고 한다. 접근 지정자는 클래스의 멤버에 접근할 수 있는 사용자를 결정한다. 각 멤버는 접근 지정자의 접근 수준을 "획득"한다. (기본 접근 수준은 private)

C++은 public, priavte 및 protected 세 가지 접근 지정 키워드를 제공한다. public은 공개 멤버이므로 클래스 외부에서도 접근할 수 있고, private는 비공개 멤버이므로 클래스 내에서만 접근할 수 있다. protected는 나중에 "상속"을 다룰 때 설명할 예정이다.

	public: 공개 멤버, 클래스 외부에서도 접근 가능
	priavte: 비공개 멤버, 클래스 내에서만 접근 가능

클래스에는 여러 접근 지정자를 사용하여 각 멤버의 접근 수준을 설정할 수 있다. 한 클래스에서 사용할 수 있는 접근 지정자의 개수에는 제한이 없다.

일반적으로 멤버 변수는 비공개로 하고, 멤버 함수는 공개하는 것이 일반적이다.

출처: https://boycoding.tistory.com/242


## 생성자와 소멸자

소멸자 (Destructor)
소멸자는 객체가 소멸될 때 자동으로 실행되는 클래스의 멤버 함수다. 생성자는 클래스의 초기화를 돕도록 설계됐지만 소멸자는 청소를 돕도록 설계되었다.

지역에서 생성된 객체가 지역 범위를 벗어나거나 동적으로 할당된 객체가 삭제 키워드를 사용해 명시적으로 삭제되면, 객체가 메모리에서 제거되기 전에 필요한 정리를 수행하기 위해 클래스는 소멸자가 있는 경우 소멸자를 자동으로 호출한다.

클래스의 멤버 변수들이 단순하게 기본 자료형이 값 형식이라면 크게 필요 없지만 다른 리소스(예: 동적 메모리, 파일 또는 데이터베이스 핸들러)라면 객체가 소멸되기 전에 어떤 종류의 유지보수를 해야 한다. 이때 소멸자는 객체가 소멸되기 전에 마지막으로 호출되는 특별한 함수이므로 완벽한 장소가 된다.

소멸자 규칙
생성자처럼 소멸자도 특별한 규칙이 있다.

소멸자 이름은 클래스 이름과 같아야 하고 앞에 ~를 달아야 한다.
소멸자는 인수가 없다.
소멸자는 반환 값이 없다.
이런 규칙 때문에 소멸자는 클래스당 하나밖에 존재할 수 없다.

또한, 소멸자를 명시적으로 호출하는 경우는 없다.

출처: https://boycoding.tistory.com/249 [소년코딩]



## string에서 == 연산자의 오버로딩

* cpp에서는 string의 경우 ==를 통해 문자열을 비교할 수 있는데, 연산자 오버로딩 덕분이다.

* 연산자 오버로딩이란 객체 지향 프로그래밍에서 다형성의 특정 경우로 다른 연산자들이 함수 인자를 통해서 구현할 때를 말한다.

String 문자열을 비교할 때 == 연산자는 아래와 같이 오버로딩이 된다.

	Template<typename _CharT, typename _Traits, typename _Alloc>
	Inline bool
	operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
			const basic_string<_CharT, _Traits, _Alloc>& __rhs)
	{
		return __lhs.compare(__rhs) == 0;
	}


## STL(Standard Template Library)이란?

### 정의
* 표준 C++ 라이브러리 (Standard Template Library)
* 프로그램에 필요한 자료구조와 알고리즘을 Template로 제공하는 라이브러리 

### Container
- 객체를 저장하는 객체, 자료구조 라고도 한다. 클래스 템플릿으로 구현되어있다.
- container는 크게 sequence container, associative container로 나뉩니다.

	> Sequence Container 의 종류 : array (C++ 11), vector, list, deque
	> Associative Container 의 종류 : set, multiset, map, multimap

### Iterator
- 포인터와 비슷한 개념으로 컨테이너의 원소를 가리키고, 가리키는 원소에 접근하여 다음 원소를 가리키는 기능. 순회

### Algorithm
- 정렬, 삭제, 검색, 연산 등을 해결하는 일반화된 방법을 제공하는 함수 템플릿.

### Function Object
- 함수처럼 동작하는 객체로 operator() 연산자를 오버로딩 한 객체.
- 컨테이너와 알고리즘 등에 클라이언트 정책을 반영하게 한다.

### Container Adaptor
- 구성요소의 인터페이스를 변경해 새로운 인터페이스를 갖는 구성요소로 변경.

	> Container Adaptor 의 종류 : stack, queue, priority_queue
	Allocator
	- 컨테이너의 메모리 할당 정책을 캡슐화한 클래스 객체로 모든 컨테이너는 자신만의 할당기를 가지고 있다. 

출처: https://blockdmask.tistory.com/67 [개발자 지망생]

