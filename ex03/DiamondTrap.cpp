#include <iostream>

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void)
	: ClapTrap("Unnamed_clap_name", _fragTrapMaxHitPoints,
		_scavTrapMaxEnergyPoints, _fragTrapAttackDamage), _name("Unnamed") {
	std::cout << _diamondName << " default constructor was called\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
	: ClapTrap(other), FragTrap(), ScavTrap(), _name(other._name) {
	std::cout << _diamondName << ' ' << _name
		<< "'s copy constructor was called\n";
}

DiamondTrap::DiamondTrap(const std::string name)
	: ClapTrap(name + "_clap_name", _fragTrapMaxHitPoints,
		_scavTrapMaxEnergyPoints, _fragTrapAttackDamage), FragTrap(),
		ScavTrap(), _name(name) {
	std::cout << _diamondName << ' ' << name << "'s constructor was called\n";
}

DiamondTrap	&DiamondTrap::operator=(const DiamondTrap &other) {
	if (this != &other) {
		_name = other._name;
		ClapTrap::operator=(other);
	}
	return *this;
}

DiamondTrap::~DiamondTrap(void) {
	std::cout << _diamondName << ' ' << _name << "'s destructor was called\n";
}

const std::string	&DiamondTrap::getName(void) const {
	return _name;
}

void	DiamondTrap::whoAmI(void) const {
	std::cout << ClapTrap::_name << " - " << _name << '\n';
}

const std::string	&DiamondTrap::_getModelName(void) const {
	return _diamondName;
}

unsigned int	DiamondTrap::_getMaxHitPoints(void) const {
	return _fragTrapMaxHitPoints;
}

unsigned int	DiamondTrap::_getAttackDamage(void) const {
	return _fragTrapAttackDamage;
}

unsigned int	DiamondTrap::_getMaxEnergyPoints(void) const {
	return _scavTrapMaxEnergyPoints;
}

const std::string	DiamondTrap::_diamondName = "DiamondTrap";
