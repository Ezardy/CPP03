#include <iostream>

#include "FragTrap.hpp"

FragTrap::FragTrap(void)
	: ClapTrap("Unnamed", _fragTrapMaxHitPoints, _fragTrapMaxEnergyPoints,
		_fragTrapAttackDamage) {
	std::cout << _fragTrapName << " default constructor was called\n";
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
	std::cout << _fragTrapName << ' ' << _name
		<< "'s copy constructor was called\n";
}

FragTrap::FragTrap(std::string name)
	: ClapTrap(name, _fragTrapMaxHitPoints, _fragTrapMaxEnergyPoints,
		_fragTrapAttackDamage) {
	std::cout << _fragTrapName << ' ' << _name << "'s constructor was called\n";
}

FragTrap	&FragTrap::operator=(const FragTrap &other) {
	ClapTrap::operator=(other);
	return *this;
}

FragTrap::~FragTrap(void) {
	std::cout << _fragTrapName << ' ' << _name << "'s destructor was called\n";
}

void	FragTrap::highFivesGuys(void) const {
	if (_hitPoints && _energyPoints)
		std::cout << "'High five, Guys!' - " << _getModelName() << ' '
			<< getName() << '\n';
}

const std::string	&FragTrap::_getModelName(void) const {
	return _fragTrapName;
}

unsigned int	FragTrap::_getMaxHitPoints(void) const {
	return _fragTrapMaxHitPoints;
}

unsigned int	FragTrap::_getAttackDamage(void) const {
	return _fragTrapAttackDamage;
}

unsigned int	FragTrap::_getMaxEnergyPoints(void) const {
	return _fragTrapMaxEnergyPoints;
}

const std::string	FragTrap::_fragTrapName = "FragTrap";
const unsigned int	FragTrap::_fragTrapMaxHitPoints = 100;
const unsigned int	FragTrap::_fragTrapAttackDamage = 30;
const unsigned int	FragTrap::_fragTrapMaxEnergyPoints = 100;

