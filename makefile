all: build

build: src/main.o src/sqrt.o
	g++ src/main.o src/sqrt.o -o build.out

main.o: main.cpp
	g++ -c src/main.cpp

sqrt.o: sqrt.cpp
	g++ -c src/sqrt.cpp

sqrt_tests.o: tests/sqrt_tests.cpp
	g++ -c tests/sqrt_tests.cpp

tests: tests/sqrt_tests.o
	g++ tests/sqrt_tests.o -o sqrt_tests.out

clean:
	rm -rf **/*.o

purge:
	rm -rf **/*.o **.out
