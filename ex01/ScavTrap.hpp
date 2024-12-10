#ifndef EX01_SCAVTRAP_HPP
# define EX01_SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
	ScavTrap(void);
	ScavTrap(const ScavTrap &other);
	ScavTrap(const std::string name);
	ScavTrap	&operator=(const ScavTrap &other);
	~ScavTrap(void);

	void	guardGate(void) const;
protected:
	static const std::string	_scavTrapName;
	static const unsigned int	_scavTrapMaxHitPoints;
	static const unsigned int	_scavTrapAttackDamage;
	static const unsigned int	_scavTrapMaxEnergyPoints;
private:
	const std::string	&_getModelName(void) const;
	unsigned int		_getMaxHitPoints(void) const;
	unsigned int		_getAttackDamage(void) const;
	unsigned int		_getMaxEnergyPoints(void) const;
	void				_printAttackMessage(const std::string &target) const;
};

#endif
