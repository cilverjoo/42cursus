#include <iostream>
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "Character.hpp"

int main(void)
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice()); //MaterialSource에 Ice랑 Cure 장착.
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp = NULL;
	AMateria* tmp2 = NULL;
	AMateria* first = NULL;
	tmp = src->createMateria("fire"); //정의된 fire이 없으므로 아무것도 리턴되지 않음
	me->equip(tmp);
	tmp = src->createMateria("ice"); //Ice는 이미 장착되어 있으므로 tmp에 새로운 AMateria가 리턴된다
	first = tmp; //first는 tmp를 깊은 복사
	me->equip(tmp);
	tmp2 = src->createMateria("cure"); //Cure는 이미 장착되어 있으므로 cure type의 AMateria가 리턴된다
	me->equip(tmp2); //equip은 포인터만 저장할 뿐 복사하지 않는다. 같은 tmp를 두 번 장착했을 때, 한 번만 되어야 한다
	me->equip(tmp2);
	tmp = src->createMateria("ice");
	tmp->use(*me);
	me->equip(tmp);
	tmp = src->createMateria("cure");
	tmp->use(*me);
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	delete tmp;
	me->equip(NULL);

	ICharacter* bob = new Character("bob");
	me->use(-1, *bob);
	std::cout << "materia exp: " << first->getXP() << std::endl;
	me->use(0, *bob);
	std::cout << "materia exp: " << first->getXP() << std::endl;
	me->use(0, *bob);
	std::cout << "materia exp: " << first->getXP() << std::endl;
	me->use(1, *bob);
	me->use(2, *bob);
	me->use(3, *bob);
	me->use(4, *bob);

	std::cout << "====unequip materia======\n";
	me->unequip(0);
	std::cout << "materia exp: " << tmp2->getXP() << std::endl; //unequip을 했지만 삭제한 것은 아님.
	me->use(0, *bob);
	std::cout << "materia exp : " << tmp2->getXP() << std::endl;
	me->use(1, *bob);
	std::cout << "materia exp : " << tmp2->getXP() << std::endl;
	me->unequip(-1);
	me->equip(first);
	delete bob;
	delete me;
	delete src;
	return (0);
}
