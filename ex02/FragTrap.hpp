#ifndef EX02_FRAGTRAP_HPP
# define EX02_FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
	FragTrap(void);
	FragTrap(const FragTrap &other);
	FragTrap(const std::string name);
	FragTrap	&operator=(const FragTrap &other);
	~FragTrap(void);

	void		highFivesGuys(void) const;
protected:
	static const std::string	_fragTrapName;
	static const unsigned int	_fragTrapMaxHitPoints;
	static const unsigned int	_fragTrapAttackDamage;
	static const unsigned int	_fragTrapMaxEnergyPoints;
private:
	virtual const std::string	&_getModelName(void) const;
	virtual unsigned int		_getMaxHitPoints(void) const;
	virtual unsigned int		_getAttackDamage(void) const;
	virtual unsigned int		_getMaxEnergyPoints(void) const;
};

#endif
