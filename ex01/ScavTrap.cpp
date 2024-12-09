#include <iostream>

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap() {
	std::cout << _scavTrapName << ' ' << _name
		<< "'s default constructor was called\n";
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
	std::cout << _scavTrapName << ' ' << _name
		<< "'s copy constructor was called\n";
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	std::cout << _scavTrapName << ' ' << _name
		<< "'s constructor was called\n";
}

ScavTrap	&ScavTrap::operator=(const ScavTrap &other) {
	ClapTrap::operator=(other);
	return *this;
}

ScavTrap::~ScavTrap(void) {
	std::cout << _scavTrapName << ' ' << _name << "'s destructor was called\n";
}

const std::string	&ScavTrap::_getModelName(void) const {
	return _scavTrapName;
}

unsigned int	ScavTrap::_getMaxHitPoints(void) const {
	return _scavTrapMaxHitPoints;
}

unsigned int	ScavTrap::_getAttackDamage(void) const {
	return _scavTrapAttackDamage;
}

unsigned int	ScavTrap::_getMaxEnergyPoints(void) const {
	return _scavTrapMaxEnergyPoints;
}

void	ScavTrap::_printAttackMessage(const std::string &target) const {
	std::cout << _scavTrapName << ' ' << _name << " trying to take "
		<< _attackDamage << " hit points from " << target << " because it can: "
		<< _hitPoints << " hit points; " << _energyPoints << " energy points\n";
}

void	ScavTrap::guardGate(void) const {
	std::cout << _getModelName() << ' ' << _name << " guards the Gate\n";
}

const std::string	ScavTrap::_scavTrapName = "ScavTrap";
const unsigned int	ScavTrap::_scavTrapMaxHitPoints = 100;
const unsigned int	ScavTrap::_scavTrapAttackDamage = 20;
const unsigned int	ScavTrap::_scavTrapMaxEnergyPoints = 50;
