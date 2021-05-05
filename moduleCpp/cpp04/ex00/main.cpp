#include "Sorcerer.hpp"
#include "Victim.hpp"
#include "Peon.hpp"

int main()
{
	Sorcerer	robert("Robert", "the Magnificent");
	Victim		jim("Jimmy");
	Peon		joe("Joe");

	std::cout << robert ;
	robert.polymorph(jim);
	robert.polymorph(joe);  // Victim에서 polymorph를 가상함수로 만들었기 때문에 Peon에서 재정의한 함수가 호출됨

	Sorcerer	a;  // 인자없이 만들수 없음

	return 0;
}
