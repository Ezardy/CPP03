#include "DiamondTrap.hpp"
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

static bool	fragtrap_default_constructor(void);
static bool	fragtrap_construction_destruction(void);
static bool	fragtrap_copy_constructor(void);
static bool	fragtrap_copy_assignment(void);
static bool	fragtrap_highFiveGuys(void);
static bool	frag_vs_clap(void);
static bool	frag_vs_scav(void);
static bool	frag_vs_frag(void);

static bool	diamondtrap_default_constructor(void);
static bool	diamondtrap_construction_deconstruction(void);
static bool	diamondtrap_copy_constructor(void);
static bool	diamondtrap_copy_assignment(void);
static bool	whoAmI(void);
static bool	diamondtrap_highFiveGuys(void);
static bool	diamondtrap_guardGate(void);
static bool	diamond_vs_clap_scav_frag(void);

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
		scav_vs_scav,

		fragtrap_default_constructor,
		fragtrap_construction_destruction,
		fragtrap_copy_constructor,
		fragtrap_copy_assignment,
		fragtrap_highFiveGuys,
		frag_vs_clap,
		frag_vs_scav,
		frag_vs_frag,

		diamondtrap_default_constructor,
		diamondtrap_construction_deconstruction,
		diamondtrap_copy_constructor,
		diamondtrap_copy_assignment,
		whoAmI,
		diamondtrap_highFiveGuys,
		diamondtrap_guardGate,
		diamond_vs_clap_scav_frag
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

TEST_LOGIC_START(diamond_vs_clap_scav_frag)
	DiamondTrap	matt("Matt");
	FragTrap	sue("Sue");
	ScavTrap	john("John");
	ClapTrap	peatacho("Peatacho");

	matt.guardGate();
	matt.whoAmI();
	peatacho.attack(matt);
	john.attack(matt);
	sue.attack(matt);
	matt.attack(peatacho);
	matt.attack(john);
	matt.attack(sue);
	success = matt.getHitPoints() == 50 && matt.getEnergyPoints() == 47;
	matt.beRepaired();

	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"FragTrap Sue's constructor was called\n"
		"ClapTrap John's constructor was called\n"
		"ScavTrap John's constructor was called\n"
		"ClapTrap Peatacho's constructor was called\n"
		"DiamondTrap Matt guards the Gate\n"
		"Matt_clap_name - Matt\n"
		"ClapTrap Peatacho attacks Matt, causing 0 points of damage!\n"
		"ScavTrap John tries to take 20 hit points from Matt because it can: "
			"100 hit points; 50 energy points\n"
		"DiamondTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Sue attacks Matt, causing 30 points of damage!\n"
		"DiamondTrap Matt took 30 damage points and has 50 hit points now\n"
		"DiamondTrap Matt tries to take 30 hit points from Peatacho because it can: "
			"50 hit points; 50 energy points\n"
		"ClapTrap Peatacho took 10 damage points and died\n"
		"DiamondTrap Matt tries to take 30 hit points from John because it can: "
			"50 hit points; 49 energy points\n"
		"ScavTrap John took 30 damage points and has 70 hit points now\n"
		"DiamondTrap Matt tries to take 30 hit points from Sue because it can: "
			"50 hit points; 48 energy points\n"
		"FragTrap Sue took 30 damage points and has 70 hit points now\n"
		"DiamondTrap Matt was repaired and has 100 hit points now\n";
TEST_LOGIC_END

TEST_LOGIC_START(diamondtrap_guardGate)
	DiamondTrap	matt("Matt");
	DiamondTrap	sue("Sue");

	matt.guardGate();
	matt.takeDamage(100);
	matt.guardGate();
	sue.guardGate();
	sue.takeDamage(99);
	std::ostringstream	ss;
	do {
		sue.beRepaired(1);
		ss << "DiamondTrap Sue was repaired and has " << sue.getHitPoints()
			<< " hit points now\n";
	} while (sue.getEnergyPoints());
	sue.guardGate();
	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n"
		"ClapTrap Sue_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Sue's constructor was called\n"
		"DiamondTrap Matt guards the Gate\n"
		"DiamondTrap Matt took 100 damage points and died\n"
		"DiamondTrap Sue guards the Gate\n"
		"DiamondTrap Sue took 99 damage points and has 1 hit points now\n"
		+ ss.str();
TEST_LOGIC_END

TEST_LOGIC_START(diamondtrap_highFiveGuys)
	DiamondTrap	matt("Matt");
	DiamondTrap	sue("Sue");

	matt.highFivesGuys();
	matt.takeDamage(100);
	matt.highFivesGuys();
	sue.highFivesGuys();
	sue.takeDamage(99);
	sue.beRepaired(1);
	sue.takeDamage(1);
	std::ostringstream	ss;
	do {
		sue.beRepaired(1);
		ss << "DiamondTrap Sue was repaired and has " << sue.getHitPoints()
			<< " hit points now\n";
	} while (sue.getEnergyPoints());
	sue.highFivesGuys();
	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n"
		"ClapTrap Sue_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Sue's constructor was called\n"
		"'High five, Guys!' - DiamondTrap Matt\n"
		"DiamondTrap Matt took 100 damage points and died\n"
		"'High five, Guys!' - DiamondTrap Sue\n"
		"DiamondTrap Sue took 99 damage points and has 1 hit points now\n"
		"DiamondTrap Sue was repaired and has 2 hit points now\n"
		"DiamondTrap Sue took 1 damage points and has 1 hit points now\n"
		+ ss.str();
TEST_LOGIC_END

TEST_LOGIC_START(whoAmI)
	const std::string	dname = "Matt";
	const std::string	cname = dname + "_clap_name";
	DiamondTrap	matt("Matt");

	matt.whoAmI();

	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n";
	expected += cname + " - " + dname + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(diamondtrap_copy_assignment)
	DiamondTrap	matt("Matt");
	DiamondTrap	unnamed;

	matt.takeDamage(57);
	matt.beRepaired(1);
	unnamed = matt;
	success = unnamed.getName() == matt.getName() && unnamed.getHitPoints() == 44
		&& unnamed.getEnergyPoints() == 49;
	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n"
		"ClapTrap Unnamed_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap default constructor was called\n"
		"DiamondTrap Matt took 57 damage points and has 43 hit points now\n"
		"DiamondTrap Matt was repaired and has 44 hit points now\n"
		"DiamondTrap Matt's copy assignment was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(diamondtrap_copy_constructor)
	DiamondTrap	matt("Matt");

	matt.takeDamage(57);
	matt.beRepaired(1);
	DiamondTrap	matt2 = matt;
	success = matt2.getEnergyPoints() == 49 && matt2.getHitPoints() == 44;
	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n"
		"DiamondTrap Matt took 57 damage points and has 43 hit points now\n"
		"DiamondTrap Matt was repaired and has 44 hit points now\n"
		"ClapTrap Matt_clap_name's copy constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's copy constructor was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(diamondtrap_construction_deconstruction) {
	DiamondTrap	matt("Matt");

	success = matt.getHitPoints() == 100 && matt.getEnergyPoints() == 50
		&& matt.getAttackDamage() == 30;
	expected = "ClapTrap Matt_clap_name's constructor was called\n"
		"FragTrap default constructor was called\n"
		"ScavTrap default constructor was called\n"
		"DiamondTrap Matt's constructor was called\n"
		"DiamondTrap Matt's destructor was called\n"
		"ScavTrap Matt_clap_name's destructor was called\n"
		"FragTrap Matt_clap_name's destructor was called\n"
		"ClapTrap Matt_clap_name's destructor was called\n";
} TEST_LOGIC_END

TEST_LOGIC_START(diamondtrap_default_constructor) {
	const FragTrap	*unnamed = new DiamondTrap();

	if ((success = unnamed != NULL)) {
		success = unnamed->getHitPoints() == 100 && unnamed->getEnergyPoints() == 50
			&& unnamed->getAttackDamage() == 30;
		expected = "ClapTrap Unnamed_clap_name's constructor was called\n"
			"FragTrap default constructor was called\n"
			"ScavTrap default constructor was called\n"
			"DiamondTrap default constructor was called\n"
			"DiamondTrap Unnamed's destructor was called\n"
			"ScavTrap Unnamed_clap_name's destructor was called\n"
			"FragTrap Unnamed_clap_name's destructor was called\n"
			"ClapTrap Unnamed_clap_name's destructor was called\n";
	}
	delete unnamed;
} TEST_LOGIC_END

TEST_LOGIC_START(frag_vs_frag)
	FragTrap	matt("Matt");
	FragTrap	sue("Sue");

	matt.attack(sue);
	sue.attack(matt);
	matt.highFivesGuys();
	sue.highFivesGuys();
	matt.beRepaired();
	sue.beRepaired();
	expected = "ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"FragTrap Sue's constructor was called\n"
		"FragTrap Matt attacks Sue, causing 30 points of damage!\n"
		"FragTrap Sue took 30 damage points and has 70 hit points now\n"
		"FragTrap Sue attacks Matt, causing 30 points of damage!\n"
		"FragTrap Matt took 30 damage points and has 70 hit points now\n"
		"'High five, Guys!' - FragTrap Matt\n"
		"'High five, Guys!' - FragTrap Sue\n"
		"FragTrap Matt was repaired and has 100 hit points now\n"
		"FragTrap Sue was repaired and has 100 hit points now\n";
TEST_LOGIC_END

TEST_LOGIC_START(frag_vs_scav)
	FragTrap	matt("Matt");
	ScavTrap	sue("Sue");

	matt.highFivesGuys();
	sue.attack(matt);
	matt.beRepaired();
	sue.attack(matt);
	matt.beRepaired();
	sue.attack(matt);
	matt.beRepaired();
	sue.attack(matt);
	matt.beRepaired();
	sue.attack(matt);
	matt.beRepaired();
	sue.attack(matt);
	matt.beRepaired(10);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	matt.attack(sue);
	sue.attack(matt);
	sue.guardGate();
	sue.beRepaired();
	sue.takeDamage(9);
	std::ostringstream	ss;
	do {
		matt.beRepaired(1);
		ss << "FragTrap Matt was repaired and has " << matt.getHitPoints()
			<< " hit points now\n";
	} while (matt.getEnergyPoints());
	matt.beRepaired();
	matt.attack(matt);
	matt.takeDamage(10);
	expected = "ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"ScavTrap Sue's constructor was called\n"
		"'High five, Guys!' - FragTrap Matt\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 50 energy points\n"
		"FragTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Matt was repaired and has 100 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 49 energy points\n"
		"FragTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Matt was repaired and has 100 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 48 energy points\n"
		"FragTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Matt was repaired and has 100 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 47 energy points\n"
		"FragTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Matt was repaired and has 100 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 46 energy points\n"
		"FragTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Matt was repaired and has 100 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 45 energy points\n"
		"FragTrap Matt took 20 damage points and has 80 hit points now\n"
		"FragTrap Matt was repaired and has 90 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"100 hit points; 44 energy points\n"
		"FragTrap Matt took 20 damage points and has 70 hit points now\n"
		"FragTrap Matt attacks Sue, causing 30 points of damage!\n"
		"ScavTrap Sue took 30 damage points and has 70 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"70 hit points; 43 energy points\n"
		"FragTrap Matt took 20 damage points and has 50 hit points now\n"
		"FragTrap Matt attacks Sue, causing 30 points of damage!\n"
		"ScavTrap Sue took 30 damage points and has 40 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"40 hit points; 42 energy points\n"
		"FragTrap Matt took 20 damage points and has 30 hit points now\n"
		"FragTrap Matt attacks Sue, causing 30 points of damage!\n"
		"ScavTrap Sue took 30 damage points and has 10 hit points now\n"
		"ScavTrap Sue tries to take 20 hit points from Matt because it can: "
			"10 hit points; 41 energy points\n"
		"FragTrap Matt took 20 damage points and has 10 hit points now\n"
		"FragTrap Matt attacks Sue, causing 30 points of damage!\n"
		"ScavTrap Sue took 10 damage points and died\n" + ss.str();
TEST_LOGIC_END

TEST_LOGIC_START(frag_vs_clap)
	ClapTrap	sue("Sue");
	FragTrap	matt("Matt");

	sue.attack(matt);
	matt.beRepaired();
	matt.attack(sue);
	sue.beRepaired();
	sue.attack(matt);
	matt.highFivesGuys();
	success = sue.getHitPoints() == 0 && sue.getEnergyPoints() == 9
		&& matt.getHitPoints() == 100 && matt.getEnergyPoints() == 99;
	expected = "ClapTrap Sue's constructor was called\n"
		"ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"ClapTrap Sue attacks Matt, causing 0 points of damage!\n"
		"FragTrap Matt attacks Sue, causing 30 points of damage!\n"
		"ClapTrap Sue took 10 damage points and died\n"
		"'High five, Guys!' - FragTrap Matt\n";
TEST_LOGIC_END

TEST_LOGIC_START(fragtrap_highFiveGuys)
	FragTrap	matt("Matt");
	FragTrap	sue("Sue");

	matt.highFivesGuys();
	matt.takeDamage(100);
	matt.highFivesGuys();
	sue.highFivesGuys();
	sue.takeDamage(99);
	sue.beRepaired(1);
	sue.takeDamage(1);
	std::ostringstream	ss;
	do {
		sue.beRepaired(1);
		ss << "FragTrap Sue was repaired and has " << sue.getHitPoints()
			<< " hit points now\n";
	} while (sue.getEnergyPoints());
	sue.highFivesGuys();
	expected = "ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"ClapTrap Sue's constructor was called\n"
		"FragTrap Sue's constructor was called\n"
		"'High five, Guys!' - FragTrap Matt\n"
		"FragTrap Matt took 100 damage points and died\n"
		"'High five, Guys!' - FragTrap Sue\n"
		"FragTrap Sue took 99 damage points and has 1 hit points now\n"
		"FragTrap Sue was repaired and has 2 hit points now\n"
		"FragTrap Sue took 1 damage points and has 1 hit points now\n"
		+ ss.str();
TEST_LOGIC_END

TEST_LOGIC_START(fragtrap_copy_assignment)
	FragTrap	matt("Matt");
	FragTrap	unnamed;

	matt.takeDamage(57);
	matt.beRepaired(1);
	unnamed = matt;
	success = unnamed.getName() == matt.getName() && unnamed.getHitPoints() == 44
		&& unnamed.getEnergyPoints() == 99;
	expected = "ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"ClapTrap Unnamed's constructor was called\n"
		"FragTrap default constructor was called\n"
		"FragTrap Matt took 57 damage points and has 43 hit points now\n"
		"FragTrap Matt was repaired and has 44 hit points now\n"
		"FragTrap Matt's copy assignment was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(fragtrap_copy_constructor)
	FragTrap	matt("Matt");

	matt.takeDamage(57);
	matt.beRepaired(1);
	FragTrap	matt2 = matt;
	success = matt2.getEnergyPoints() == 99 && matt2.getHitPoints() == 44;
	expected = "ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"FragTrap Matt took 57 damage points and has 43 hit points now\n"
		"FragTrap Matt was repaired and has 44 hit points now\n"
		"ClapTrap Matt's copy constructor was called\n"
		"FragTrap Matt's copy constructor was called\n";
TEST_LOGIC_END

TEST_LOGIC_START(fragtrap_construction_destruction) {
	FragTrap	matt("Matt");

	success = matt.getHitPoints() == 100 && matt.getEnergyPoints() == 100
		&& matt.getAttackDamage() == 30;
	expected = "ClapTrap Matt's constructor was called\n"
		"FragTrap Matt's constructor was called\n"
		"FragTrap Matt's destructor was called\n"
		"ClapTrap Matt's destructor was called\n";
} TEST_LOGIC_END

TEST_LOGIC_START(fragtrap_default_constructor) {
	const ClapTrap	*unnamed = new FragTrap();

	if ((success = unnamed != NULL)) {
		success = unnamed->getHitPoints() == 100 && unnamed->getEnergyPoints() == 100
			&& unnamed->getAttackDamage() == 30;
		expected = "ClapTrap Unnamed's constructor was called\n"
			"FragTrap default constructor was called\n"
			"FragTrap Unnamed's destructor was called\n"
			"ClapTrap Unnamed's destructor was called\n";
	}
	delete unnamed;
} TEST_LOGIC_END

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
	const ClapTrap	*unnamed = new ScavTrap();

	if ((success = unnamed != NULL)) {
		success = unnamed->getHitPoints() == 100 && unnamed->getEnergyPoints() == 50
			&& unnamed->getAttackDamage() == 20;
		expected = "ClapTrap Unnamed's constructor was called\n"
			"ScavTrap default constructor was called\n"
			"ScavTrap Unnamed's destructor was called\n"
			"ClapTrap Unnamed's destructor was called\n";
	}
	delete unnamed;
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
