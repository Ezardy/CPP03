#ifndef EX03_DIAMONDTRAP_HPP
# define EX03_DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {
public:
	DiamondTrap(void);
	DiamondTrap(const DiamondTrap &other);
	DiamondTrap(const std::string name);
	DiamondTrap			&operator=(const DiamondTrap &other);
	~DiamondTrap(void);

	const std::string	&getName(void) const;
	void				whoAmI(void) const;
private:
	static const std::string	_diamondName;

	std::string			_name;

	const std::string	&_getModelName(void) const;
	unsigned int		_getMaxHitPoints(void) const;
	unsigned int		_getAttackDamage(void) const;
	unsigned int		_getMaxEnergyPoints(void) const;
};

#endif
