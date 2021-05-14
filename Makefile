.PHONY: all clean test

all: p2.cpp gen2procs.cpp
	g++ -std=c++11 -O3 -Wall p2.cpp -lm -o p2.out
	g++ -std=c++11 -O3 -Wall gen2procs.cpp -lm -o gen2procs.out

clean: p2.out gen2procs.out
	rm *.out

test: all
	./p2.out < test.txt
