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


##################################################
#------------------- TESTS ----------------------#
##################################################
sqrt_tests.o: tests/sqrt_tests.cpp
	g++ -c tests/sqrt_tests.cpp

solve_tests.o: tests/solve_tests.cpp
	g++ -c tests/solve_tests.cpp

testfuncs.o: tests/testfuncs.cpp
	g++ -c tests/testfuncs.cpp
	
tests1: src/sqrt.o src/solve.o tests/sqrt_tests.o tests/testfuncs.o
	g++ src/sqrt.o src/solve.o tests/sqrt_tests.o tests/testfuncs.o -o sqrt_tests.out

tests2: src/sqrt.o src/solve.o tests/solve_tests.o tests/testfuncs.o
	g++ src/sqrt.o src/solve.o tests/solve_tests.o tests/testfuncs.o -o solve_tests.out


##################################################
#------------------ UTILITY ---------------------#
##################################################
clean:
	rm -rf **/*.o

purge:
	rm -rf **/*.o **.out
