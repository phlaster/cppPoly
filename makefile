all: build

build: src/main.o src/sqrt.o src/solve.o src/print.o
	g++ src/main.o src/sqrt.o src/solve.o src/print.o -o build.out

# # # # #
main.o: main.cpp
	g++ -c src/main.cpp

sqrt.o: sqrt.cpp
	g++ -c src/sqrt.cpp

solve.o: solve.cpp
	g++ -c src/solve.cpp

print.o: print.cpp
	g++ -c scr/print.cpp

# # # # #
sqrt_tests.o: tests/sqrt_tests.cpp
	g++ -c tests/sqrt_tests.cpp

solve_tests.o: tests/solve_tests.cpp
	g++ -c tests/solve_tests.cpp

tests1: tests/sqrt_tests.o
	g++ src/sqrt.o src/solve.o tests/sqrt_tests.o -o sqrt_tests.out

tests2: tests/solve_tests.o
	g++ src/sqrt.o src/solve.o tests/solve_tests.o -o solve_tests.out
# # # # #
clean:
	rm -rf **/*.o

purge:
	rm -rf **/*.o **.out
