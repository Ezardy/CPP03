#ifndef EX00_CLAPTRAP_HPP
# define EX00_CLAPTRAP_HPP

# include <string>

class ClapTrap {
public:
	ClapTrap(void);
	ClapTrap(const std::string name);
	ClapTrap(const ClapTrap &other);
	ClapTrap		&operator=(const ClapTrap &other);
	~ClapTrap(void);

	void				attack(const std::string &target);
	void				attack(ClapTrap &target);
	void				takeDamage(unsigned int amount);
	void				beRepaired(unsigned int amount);
	void				beRepaired(void);
	const std::string	&getName(void) const;
	unsigned int		getEnergyPoints(void) const;
	unsigned int		getHitPoints(void) const;
	unsigned int		getAttackDamage(void) const;
private:
	std::string					_name;
	unsigned int				_hitPoints;
	unsigned int				_energyPoints;
	static const std::string	_modelName;
	static const unsigned int	_maxHitPoints;
	static const unsigned int	_attackDamage;
};

#endif
