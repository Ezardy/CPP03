#ifndef EX01_CLAPTRAP_HPP
# define EX01_CLAPTRAP_HPP

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
protected:
	std::string					_name;
	unsigned int				_hitPoints;
	unsigned int				_energyPoints;
	unsigned int				_attackDamage;
private:
	static const std::string	_clapTrapName;
	static const unsigned int	_clapTrapMaxHitPoints;
	static const unsigned int	_clapTrapAttackDamage;
	static const unsigned int	_clapTrapMaxEnergyPoints;

	virtual const std::string	&_getModelName(void) const;
	virtual unsigned int		_getMaxHitPoints(void) const;
	virtual unsigned int		_getAttackDamage(void) const;
	virtual unsigned int		_getMaxEnergyPoints(void) const;
	virtual void				_printAttackMessage(const std::string &target) const;
};

#endif
