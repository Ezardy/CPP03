all: test

src=main ClapTrap ScavTrap
obj=$(addsuffix .o, $(src))

test: $(obj)
	c++ -o $@ $(obj)

iflags=-Wall -Wextra -Werror -std=c++98
command=c++ $(iflags) -o $@ -c $<

main.o: main.cpp ClapTrap.hpp ScavTrap.hpp Makefile
	$(command)

ClapTrap.o: ClapTrap.cpp ClapTrap.hpp Makefile
	$(command)

ScavTrap.o: ScavTrap.cpp ScavTrap.hpp ClapTrap.hpp Makefile
	$(command)

clean:
	rm -f $(obj)

fclean: clean
	rm -f test

re: fclean test

debug: iflags+=-g
debug: test