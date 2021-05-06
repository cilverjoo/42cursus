## CPP_MODULE_03에서의 핵심은 상속!

#### 1. 다중 상속이란?

```
<리스트 1> Diamond 예제

class CTop
{
public:
  int m_Top;
};

class CMiddleA : public CTop
{
public:
  int m_MiddleA;
};

class CMiddleB : public CTop
{
public:
  int m_MiddleB;
};

class CBottom : public CMiddleA, public CMiddleB
{
public:
  CBottom()
  {
    m_Top = 10;       // ① Error
    m_MiddleA = 21;
    m_MiddleB = 22;
    m_Bottom = 30;
  }
  int m_Bottom;
};
```
다이아몬드 구조에서 발생할 수 있는 문제는 최상위 부모인 CTop이 중간 부모 CMiddleA와 CMiddleB에게 상속되고, 중간 부모 CMiddleA와 CMiddleB는 모두 CBottom에 의해서 상속되면서 CTop의 모든 멤버가 CBottom에 두 번씩 중복으로 상속되는 데 있다. CTop의 멤버 m_Top은 CBottom에서 두 개가 존재하게 된다.

```
CMiddleA::m_Top = 10;
```
다음과 같이 범위연산자를 사용한다면 m_Top을 각자 사용할 수 있게 되지만, 하나의 m_Top만을 필요로 하기 때문에 사실상 두 번째 m_Top은 메모리 낭비만 일으키게 된다. 그래서 다중 상속의 다이아몬드 구조에 의한 메모리 낭비를 줄이기 위한 특별한 구조가 제시되는데 그것이 바로 지금부터 소개할 **가상 상속**이다.


#### 2. 가상 상속이란?

- 다중 상속은 **멤버의 중복**에 의한 메모리 낭비를 가져올 수 있다. 다중 상속으로 인한 모호성 문제와 메모리 낭비를 일거양득으로 해결할 수 있는 방법이 바로 **가상 상속**이다. 가상 상속은 실제 프로젝트에서 그리 많이 사용되지 않지만 개념은 짚어보자.

#### 3. 가상 기저 클래스(Virtaul Base Class)
- **중복을 제거하고 싶은 클래스에 대해 virtual 키워드를 붙여서 상속**하면 가상상속을 할 수 있다.

```
<리스트 2> 가상 기저 클래스

class CTop
{
public:
  CTop() {}    // 명시적 생성자
  int m_Top;
};

class CMiddleA : virtual public CTop    // ⓐ
{
public:
  int m_MiddleA;
};

class CMiddleB : virtual public CTop    // ⓑ
{
public:
  int m_MiddleB;
};

class CBottom : public CMiddleA, public CMiddleB
{
public:
  CBottom()
  {
    m_Top = 10;        // ①
    m_MiddleA = 21;
    m_MiddleB = 22;
    m_Bottom = 30;
  }

  int m_Bottom;
};
```

- CTop이 중복 상속되는 문제를 해결하기 위한 것이므로 CTop을 상속받을 때 virtual을 추가한다. **virtual로 상속되는 CTop 클래스를 가상 기저 클래스(Virtual Base Class)라고 한다**. 가상 기저 클래스는 여러 번 상속되더라도 **메모리 구조상 하나만** 존재하게 된다. 따라서 ①과 같이 사용해도 더 이상 모호성 문제로 인한 컴파일 에러가 발생하지 않게 된다. 그러나 ⓑ에서 실수로 virtual이 생략될 경우는 가상 기저 클래스인 CTop 하나와 CMiddleB의 부모인 CTop이 메모리에 각각 생성된다. 따라서 중복 제거의 효과가 사라지게 된다.

참고 : https://www.kdata.or.kr/info/info_04_view.html?field=&keyword=&type=techreport&page=12&dbnum=185561&mode=detail&type=techreport
