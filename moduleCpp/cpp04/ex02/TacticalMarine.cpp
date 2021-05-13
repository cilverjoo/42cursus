#include "TacticalMarine.hpp"

TacticalMarine::TacticalMarine()
{
    std::cout << "Tactical Marine ready for battle!\n";
}

TacticalMarine::~TacticalMarine()
{
    std::cout << "Aaargh...\n";
}

TacticalMarine::TacticalMarine(const TacticalMarine &ref)
{
	*this = ref;
    std::cout << "Tactical Marine ready for battle!\n";
}

TacticalMarine 			&TacticalMarine::operator=(const TacticalMarine &ref)
{
    (void)ref;
	return (*this);	
}

ISpaceMarine*   TacticalMarine::clone() const
{
    TacticalMarine *clone = new TacticalMarine(*this);
    return (clone);
}
void            TacticalMarine::battleCry() const
{
    std::cout << "For the holy PLOT!\n";
}

void            TacticalMarine::rangedAttack() const
{
    std::cout << "* attacks with a bolter *\n";
}

void            TacticalMarine::meleeAttack() const
{
    std::cout << "* attacks with a chainsword *\n";
}
