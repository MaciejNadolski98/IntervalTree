main: main.o
	g++ main.o -o main

main.o: main.cpp tree.h
	g++ -std=c++17 -Wall -Wextra -O2 main.cpp -c
