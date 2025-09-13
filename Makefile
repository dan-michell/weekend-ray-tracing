CPPC   = clang++
FLAGS  = -std=c++23 -O2 -DNDEBUG -pedantic-errors -g
RM     = rm -rf
SRCDIR = src/
BUILDDIR = build/
 
main: $(SRCDIR)main.cpp
	$(CPPC) $(FLAGS) $(SRCDIR)main.cpp -o $(BUILDDIR)main
