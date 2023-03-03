all: build

build: src/main.o src/funcs.o
	g++ src/main.o src/funcs.o -o build.out

main.o: main.cpp
	g++ -c src/main.cpp

funcs.o: funcs.cpp
	g++ -c src/funcs.cpp

clean:
	rm -rf **/*.o

purge:
	rm -rf **/*.o build
