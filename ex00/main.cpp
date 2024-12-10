#include "ClapTrap.hpp"
#include "test.hpp"

static bool	claptraps_attacks_each_other_heals_attacks_until_exhaust(void);
static bool	claptrap_attack(void);
static bool	claptrap_takeDamage(void);
static bool	claptrap_beRepaired(void);
static bool	claptrap_copy_constructor(void);
static bool	claptrap_copy_assignment(void);
static bool	claptrap_default_constructor(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		claptrap_default_constructor,
		claptrap_copy_constructor,
		claptrap_copy_assignment,
		claptrap_attack,
		claptrap_takeDamage,
		claptrap_beRepaired,
		claptraps_attacks_each_other_heals_attacks_until_exhaust
	};
	size_t	tests_count = sizeof(tests) / sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

TEST_LOGIC_START(claptraps_attacks_each_other_heals_attacks_until_exhaust)
	ClapTrap	matt("Matt");
	ClapTrap	sue("Sue");

	expected = "ClapTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n";
	for (int i = 0; i < 9; i += 1) {
		matt.attack(sue);
		sue.attack(matt);
		expected += "ClapTrap Matt attacks Sue, causing 0 points of damage!\n"
			"ClapTrap Sue attacks Matt, causing 0 points of damage!\n";
	}
	matt.beRepaired();
	sue.beRepaired();
	matt.attack(sue);
	sue.attack(matt);
	expected += "ClapTrap Matt attacks Sue, causing 0 points of damage!\n"
		"ClapTrap Sue attacks Matt, causing 0 points of damage!\n";
	matt.attack(sue);
	sue.attack(matt);
	sue.takeDamage(1);
	matt.takeDamage(1);
	matt.beRepaired();
TEST_LOGIC_END

TEST_LOGIC_START(claptrap_copy_assignment)
	ClapTrap	matt("Matt");
	ClapTrap	sue("Sue");

	matt.takeDamage(4);
	matt.beRepaired(2);
	sue.takeDamage(5);
	sue.beRepaired(1);
	sue.beRepaired(1);
	sue = matt;
	success = sue.getEnergyPoints() == 9 && sue.getHitPoints() == 8
		&& sue.getName() == matt.getName();
	expected = "ClapTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"ClapTrap Matt took 4 damage points and has 6 hit points now\n"
		"ClapTrap Matt was repaired and has 8 hit points now\n"
		"ClapTrap Sue took 5 damage points and has 5 hit points now\n"
		"ClapTrap Sue was repaired and has 6 hit points now\n"
		"ClapTrap Sue was repaired and has 7 hit points now\n"
		"ClapTrap Matt's copy assignment was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(claptrap_copy_constructor)
	ClapTrap	matt("Matt");

	matt.takeDamage(4);
	matt.beRepaired(2);
	ClapTrap	matt2 = matt;
	success = matt2.getEnergyPoints() == 9 && matt2.getHitPoints() == 8
		&& matt.getName() == matt2.getName();
	expected = "ClapTrap Matt's constructor was called\n"
		"ClapTrap Matt took 4 damage points and has 6 hit points now\n"
		"ClapTrap Matt was repaired and has 8 hit points now\n"
		"ClapTrap Matt's copy constructor was called\n"
		"ClapTrap Matt's copy assignment was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(claptrap_beRepaired) {
	ClapTrap	matt("Matt");

	matt.takeDamage(9);
	matt.beRepaired(1);
	matt.beRepaired();
	matt.beRepaired(1);
	matt.beRepaired();
	success = matt.getEnergyPoints() == 8;
	expected = "ClapTrap Matt's constructor was called\n"
		"ClapTrap Matt took 9 damage points and has 1 hit points now\n"
		"ClapTrap Matt was repaired and has 2 hit points now\n"
		"ClapTrap Matt was repaired and has 10 hit points now\n"
		"ClapTrap Matt's destructor was called\n";
} TEST_LOGIC_END

TEST_LOGIC_START(claptrap_takeDamage)
	ClapTrap	matt("Matt");
	ClapTrap	sue("Sue");

	matt.takeDamage(5);
	matt.takeDamage(5);
	matt.takeDamage(5);
	sue.takeDamage(100);
	sue.takeDamage(100);
	expected = "ClapTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"ClapTrap Matt took 5 damage points and has 5 hit points now\n"
		"ClapTrap Matt took 5 damage points and died\n"
		"ClapTrap Sue took 10 damage points and died\n";
	success = matt.getHitPoints() == 0 && sue.getHitPoints() == 0;
TEST_LOGIC_END

TEST_LOGIC_START(claptrap_attack)
	ClapTrap			matt("Matt");
	const std::string	target = "Rich";

	expected = "ClapTrap Matt's constructor was called\n";
	for (int i = 0 ; i < 10; i += 1) {
		matt.attack(target);
		expected += "ClapTrap Matt attacks Rich, causing 0 points of damage!\n";
	}
	matt.attack(target);
	matt.attack(target);
	matt.attack(target);
	matt.attack(target);
	success = matt.getEnergyPoints() == 0;
TEST_LOGIC_END

TEST_LOGIC_START(claptrap_default_constructor) {
	ClapTrap	unnamed;

	success = unnamed.getHitPoints() == 10 && unnamed.getEnergyPoints() == 10
		&& unnamed.getAttackDamage() == 0;
	expected = "ClapTrap default constructor was called\n"
		"ClapTrap Unnamed's destructor was called\n";
} TEST_LOGIC_END
