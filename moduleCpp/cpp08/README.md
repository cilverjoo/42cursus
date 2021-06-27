## C++ 반복자(iterator)
- 반복자란 컨테이너에 저장되어 있는 모든 원소들을 전체적으로 훑어 나갈 때 사용하는 일종의 포인터이다.

### end()
- 컨테이너의 맨 마지막 원소가 아닌, 맨 마지막 원소 바로 다음번 원소를 가리킨다. 

### 반복자 개념을 포인터로 적용
- 정수형 배열을 가리키는 포인터 it를 선언하고, 배열의 첫 번째 요소의 번지에서 시작하여 끝 다음점 요소 직전까지 순회하면서 *it를 출력하면 배열 요소 전체가 출력된다. 

### 리스트를 이용한 반복자
begin ~ end 사이를 반복자가 순회하여 *it 표현식으로 순회중의 요소를 액세스 할 수 있다. 
```c++
#include <iostream>
#include <list>
using namespace std;

void main()
{
	int ari[] = { 1,2,3,4,5 };
	list<int> li(&ari[0], &ari[5]);
	list<int>::iterator it;
	for (it = li.begin() ; it != li.end() ; it++)
	{ 
		printf("%d\n",*it);
	}
}
```
벡터에서도 이와 같은 방법으로 동작한다.
```c++
#include <iostream>
#include <vector>
using namespace std;
void main()
{
	int ari[] = {1,2,3,4,5};
	vector<int> vi(&ari[0], &ari[5]);
	vector<int>::iterator it;
	for (it = vi.begin(); it! = vi.end(); it++)
	{
		printf("%d\n", *it);
	}
}
```
