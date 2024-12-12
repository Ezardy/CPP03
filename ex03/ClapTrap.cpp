#include <iostream>

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
	: _name("Unnamed"), _hitPoints(_getMaxHitPoints()),
		_energyPoints(_getMaxEnergyPoints()), _attackDamage(_getAttackDamage()) {
	std::cout << _clapTrapName << " default constructor was called\n";
}

ClapTrap::ClapTrap(const std::string name)
	: _name(name), _hitPoints(_getMaxHitPoints()),
		_energyPoints(_getMaxEnergyPoints()), _attackDamage(_getAttackDamage()) {
	std::cout << _clapTrapName << ' ' << name << "'s constructor was called\n";
}

ClapTrap::ClapTrap(const std::string name, const unsigned int hit,
	const unsigned int energy, const unsigned int attack)
		: _name(name), _hitPoints(hit), _energyPoints(energy),
			_attackDamage(attack) {
	std::cout << _clapTrapName << ' ' << name << "'s constructor was called\n";
}

ClapTrap::ClapTrap(const ClapTrap &other) {
	_name = other._name;
	_hitPoints = other._hitPoints;
	_energyPoints = other._energyPoints;
	_attackDamage = other._attackDamage;
	std::cout << _clapTrapName << ' ' << other._name
		<< "'s copy constructor was called\n";
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &other) {
	if (this != &other) {
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
		std::cout << _getModelName() << ' ' << getName()
			<< "'s copy assignment was called\n";
	}
	return *this;
}

ClapTrap::~ClapTrap(void) {
	std::cout << _clapTrapName << ' ' << _name << "'s destructor was called\n";
}

void	ClapTrap::attack(const std::string &target) {
	if (_energyPoints && _hitPoints) {
		std::cout << _getModelName() << ' ' << getName() << " attacks " << target
			<< ", causing " << _attackDamage << " points of damage!\n";
		_energyPoints -= 1;
	}
}

void	ClapTrap::attack(ClapTrap &target) {
	attack(target.getName());
	if (this != &target && _energyPoints && _hitPoints)
		target.takeDamage(_attackDamage);
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (amount && _hitPoints && _energyPoints) {
		std::cout << _getModelName() << ' ' << getName() << " took ";
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
	if (amount && _hitPoints && _energyPoints && _hitPoints < _getMaxHitPoints()) {
		if (amount >= _getMaxHitPoints() - _hitPoints)
			_hitPoints = _getMaxHitPoints();
		else
			_hitPoints += amount;
		_energyPoints -= 1;
		std::cout << _getModelName() << ' ' << getName() << " was repaired and has "
			<< _hitPoints << " hit points now\n";
	}
}

void	ClapTrap::beRepaired(void) {
	beRepaired(_getMaxHitPoints());
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

unsigned int	ClapTrap::getAttackDamage(void) const {
	return _attackDamage;
}

const std::string	&ClapTrap::_getModelName(void) const {
	return _clapTrapName;
}

unsigned int	ClapTrap::_getMaxHitPoints(void) const {
	return _clapTrapMaxHitPoints;
}

unsigned int	ClapTrap::_getAttackDamage(void) const {
	return _clapTrapAttackDamage;
}

unsigned int	ClapTrap::_getMaxEnergyPoints(void) const {
	return _clapTrapMaxEnergyPoints;
}

const unsigned int	ClapTrap::_clapTrapMaxHitPoints = 10;
const unsigned int	ClapTrap::_clapTrapAttackDamage = 0;
const unsigned int	ClapTrap::_clapTrapMaxEnergyPoints = 10;
const std::string	ClapTrap::_clapTrapName = "ClapTrap";
