all: build

build: src/main.o src/funcs.o
	g++ src/main.o src/funcs.o -o build.out

main.o: main.cpp
	g++ -c src/main.cpp

funcs.o: funcs.cpp
	g++ -c src/funcs.cpp

funcs_tests.o: tests/funcs_tests.cpp
	g++ -c tests/funcs_tests.cpp

tests: tests/funcs_tests.o #src/funcs.o
	g++ tests/funcs_tests.o -o tests.out

clean:
	rm -rf **/*.o

purge:
	rm -rf **/*.o **.out
