#include <iostream>

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
	: _name("Unnamed"), _hitPoints(_maxHitPoints), _energyPoints(10) {
	std::cout << _modelName << ' ' << _name
		<< "'s default constructor was called\n";
}

ClapTrap::ClapTrap(const std::string name)
	: _name(name), _hitPoints(_maxHitPoints), _energyPoints(10) {
	std::cout << _modelName << ' ' << name << "'s constructor was called\n";
}

ClapTrap::ClapTrap(const ClapTrap &other) {
	std::cout << _modelName << ' ' << other._name
		<< "'s copy constructor was called\n";
	*this = other;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &other) {
	if (this != &other) {
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		std::cout << _modelName << ' ' << _name
			<< "'s copy assignment was called\n";
	}
	return *this;
}

ClapTrap::~ClapTrap(void) {
	std::cout << _modelName << ' ' << _name << "'s destructor was called\n";
}

void	ClapTrap::attack(const std::string &target) {
	if (_energyPoints && _hitPoints) {
		std::cout << _modelName << ' ' << _name << " attacks " << target
			<< ", causing " << _attackDamage << " points of damage!\n";
		_energyPoints -= 1;
	}
}

void	ClapTrap::attack(ClapTrap &target) {
	if (this != &target && _energyPoints && _hitPoints)
		target.takeDamage(_attackDamage);
	attack(target.getName());
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (amount && _hitPoints) {
		std::cout << _modelName << ' ' << _name << " took ";
		if (amount >= _hitPoints) {
			std::cout << _hitPoints << " damage points and died\n";
			_hitPoints = 0;
		} else {
			_hitPoints -= amount;
			std::cout << amount << " damage points and has " << _hitPoints
				<< " hit points now\n";
		}
	}
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (amount && _hitPoints && _energyPoints && _hitPoints < _maxHitPoints) {
		if (amount >= _maxHitPoints - _hitPoints)
			_hitPoints = _maxHitPoints;
		else
			_hitPoints += amount;
		_energyPoints -= 1;
		std::cout << _modelName << ' ' << _name << " was repaired and has "
			<< _hitPoints << " hit points now\n";
	}
}

void	ClapTrap::beRepaired(void) {
	beRepaired(_maxHitPoints);
}

const std::string	&ClapTrap::getName(void) const {
	return _name;
}

unsigned int	ClapTrap::getEnergyPoints(void) const {
	return _energyPoints;
}

unsigned int	ClapTrap::getHitPoints(void) const {
	return _hitPoints;
}

const unsigned int	ClapTrap::_maxHitPoints = 10;
const unsigned int	ClapTrap::_attackDamage = 0;
const std::string	ClapTrap::_modelName = "ClapTrap";
