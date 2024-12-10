#include "ScavTrap.hpp"
#include "test.hpp"

static bool	claptraps_attacks_each_other_heals_attacks_until_exhaust(void);
static bool	claptrap_attack(void);
static bool	claptrap_takeDamage(void);
static bool	claptrap_beRepaired(void);
static bool	claptrap_copy_constructor(void);
static bool	claptrap_copy_assignment(void);
static bool	claptrap_default_constructor(void);

static bool	scavtrap_default_constructor(void);
static bool	scavtrap_construction_destruction(void);
static bool	scavtrap_copy_constructor(void);
static bool	scavtrap_copy_assignment(void);
static bool	scavtrap_guardGate(void);
static bool	scav_vs_clap(void);
static bool	scav_vs_scav(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		claptrap_default_constructor,
		claptrap_copy_constructor,
		claptrap_copy_assignment,
		claptrap_attack,
		claptrap_takeDamage,
		claptrap_beRepaired,
		claptraps_attacks_each_other_heals_attacks_until_exhaust,

		scavtrap_default_constructor,
		scavtrap_construction_destruction,
		scavtrap_copy_constructor,
		scavtrap_copy_assignment,
		scavtrap_guardGate,
		scav_vs_clap,
		scav_vs_scav
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

TEST_LOGIC_START(scav_vs_scav)
	ScavTrap	matt("Matt");
	ScavTrap	sue("Sue");

	matt.guardGate();
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	matt.beRepaired();
	std::ostringstream	ss;
	do {
		sue.beRepaired(1);
		ss << "ScavTrap Sue was repaired and has " << sue.getHitPoints()
			<< " hit points now\n";
	} while (sue.getEnergyPoints());
	sue.beRepaired();
	sue.attack(matt);
	sue.takeDamage(10);
	expected = "ClapTrap Matt's constructor was called\n"
		"ScavTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"ScavTrap Sue's constructor was called\n"
		"ScavTrap Matt guards the Gate\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 50 energy points\n"
		"ScavTrap Matt took 20 damage points and has 80 hit points now\n"
		"ScavTrap Matt tries to take 20 hit points from Sue because it can: "
			"80 hit points; 50 energy points\n"
		"ScavTrap Sue took 20 damage points and has 80 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"80 hit points; 49 energy points\n"
		"ScavTrap Matt took 20 damage points and has 60 hit points now\n"
		"ScavTrap Matt tries to take 20 hit points from Sue because it can: "
			"60 hit points; 49 energy points\n"
		"ScavTrap Sue took 20 damage points and has 60 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"60 hit points; 48 energy points\n"
		"ScavTrap Matt took 20 damage points and has 40 hit points now\n"
		"ScavTrap Matt tries to take 20 hit points from Sue because it can: "
			"40 hit points; 48 energy points\n"
		"ScavTrap Sue took 20 damage points and has 40 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"40 hit points; 47 energy points\n"
		"ScavTrap Matt took 20 damage points and has 20 hit points now\n"
		"ScavTrap Matt tries to take 20 hit points from Sue because it can: "
			"20 hit points; 47 energy points\n"
		"ScavTrap Sue took 20 damage points and has 20 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"20 hit points; 46 energy points\n"
		"ScavTrap Matt took 20 damage points and died\n" + ss.str();
TEST_LOGIC_END

TEST_LOGIC_START(scav_vs_clap)
	ClapTrap	sue("Sue");
	ScavTrap	matt("Matt");

	matt.guardGate();
	sue.attack(matt);
	matt.beRepaired();
	matt.attack(sue);
	sue.beRepaired();
	sue.attack(matt);
	success = sue.getHitPoints() == 0 && sue.getEnergyPoints() == 9
		&& matt.getHitPoints() == 100 && matt.getEnergyPoints() == 49;
	expected = "ClapTrap Sue's constructor was called\n"
		"ClapTrap Matt's constructor was called\n"
		"ScavTrap Matt's constructor was called\n"
		"ScavTrap Matt guards the Gate\n"
		"ClapTrap Sue attacks Matt, causing 0 points of damage!\n"
		"ScavTrap Matt tries to take 20 hit points from Sue because it can: "
			"100 hit points; 50 energy points\n"
		"ClapTrap Sue took 10 damage points and died\n";
TEST_LOGIC_END

TEST_LOGIC_START(scavtrap_guardGate)
	ScavTrap	matt("Matt");
	ScavTrap	sue("Sue");

	matt.guardGate();
	matt.takeDamage(100);
	matt.guardGate();
	sue.guardGate();
	sue.takeDamage(99);
	std::ostringstream	ss;
	do {
		sue.beRepaired(1);
		ss << "ScavTrap Sue was repaired and has " << sue.getHitPoints()
			<< " hit points now\n";
	} while (sue.getEnergyPoints());
	sue.guardGate();
	expected = "ClapTrap Matt's constructor was called\n"
		"ScavTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"ScavTrap Sue's constructor was called\n"
		"ScavTrap Matt guards the Gate\n"
		"ScavTrap Matt took 100 damage points and died\n"
		"ScavTrap Sue guards the Gate\n"
		"ScavTrap Sue took 99 damage points and has 1 hit points now\n"
		+ ss.str();
TEST_LOGIC_END

TEST_LOGIC_START(scavtrap_copy_assignment)
	ScavTrap	matt("Matt");
	ScavTrap	unnamed;

	matt.takeDamage(57);
	matt.beRepaired(1);
	unnamed = matt;
	success = unnamed.getName() == matt.getName() && unnamed.getHitPoints() == 44
		&& unnamed.getEnergyPoints() == 49;
	expected = "ClapTrap Matt's constructor was called\n"
		"ScavTrap Matt's constructor was called\n"
		"ClapTrap Unnamed's constructor was called\n"
		"ScavTrap default constructor was called\n"
		"ScavTrap Matt took 57 damage points and has 43 hit points now\n"
		"ScavTrap Matt was repaired and has 44 hit points now\n"
		"ScavTrap Matt's copy assignment was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(scavtrap_copy_constructor)
	ScavTrap	matt("Matt");

	matt.takeDamage(57);
	matt.beRepaired(1);
	ScavTrap	matt2 = matt;
	success = matt2.getEnergyPoints() == 49 && matt2.getHitPoints() == 44;
	expected = "ClapTrap Matt's constructor was called\n"
		"ScavTrap Matt's constructor was called\n"
		"ScavTrap Matt took 57 damage points and has 43 hit points now\n"
		"ScavTrap Matt was repaired and has 44 hit points now\n"
		"ClapTrap Matt's copy constructor was called\n"
		"ScavTrap Matt's copy constructor was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(scavtrap_construction_destruction) {
	ScavTrap	matt("Matt");

	success = matt.getHitPoints() == 100 && matt.getEnergyPoints() == 50
		&& matt.getAttackDamage() == 20;
	expected = "ClapTrap Matt's constructor was called\n"
		"ScavTrap Matt's constructor was called\n"
		"ScavTrap Matt's destructor was called\n"
		"ClapTrap Matt's destructor was called\n";
} TEST_LOGIC_END

TEST_LOGIC_START(scavtrap_default_constructor) {
	ScavTrap	unnamed;

	success = unnamed.getHitPoints() == 100 && unnamed.getEnergyPoints() == 50
		&& unnamed.getAttackDamage() == 20;
	expected = "ClapTrap Unnamed's constructor was called\n"
		"ScavTrap default constructor was called\n"
		"ScavTrap Unnamed's destructor was called\n"
		"ClapTrap Unnamed's destructor was called\n";
} TEST_LOGIC_END

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
	matt.takeDamage(1);
	sue.takeDamage(1);
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
		"ClapTrap Matt's copy constructor was called\n";
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
