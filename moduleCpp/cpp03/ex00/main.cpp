#include "FragTrap.hpp"

int     main(void)
{
    FragTrap unknown;
    FragTrap ekim("ekim");
    FragTrap ekim2(ekim);

    unknown = FragTrap("bradpitt");

    ekim.takeDamage(unknown.rangedAttack(ekim._name));
    unknown.takeDamage(ekim2.meleeAttack(unknown._name));

    ekim.beRepaired(50);
    unknown.beRepaired(100);

    ekim.takeDamage(unknown.vaulthunter_dot_exe(ekim._name));

    return (0);
}