#ifndef TACTICALMARINE_HPP
# define TACTICALMARINE_HPP

#include "ISpaceMarine.hpp"

#include <iostream>
#include <string>

class TacticalMarine : public ISpaceMarine
{

private:

public:
	TacticalMarine();
	~TacticalMarine();
	TacticalMarine(const TacticalMarine &ref);
	TacticalMarine &operator=(const TacticalMarine &ref);

    ISpaceMarine*   clone() const;
    void            battleCry() const;
    void            rangedAttack() const;
    void            meleeAttack() const;

};

#endif
