main: main.cpp
	clang++ -std=c++23 -O2 -DNDEBUG -pedantic-errors main.cpp -o build/main
