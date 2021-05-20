.PHONY: all gen clean debug test

all: p2.cpp
	g++ -std=c++11 -O3 -Wall p2.cpp -lm -o p2.out

gen: gen2procs.cpp
	g++ -std=c++11 -O3 -Wall gen2procs.cpp -lm -o gen2procs.out

clean:
	rm *.out

debug: p2.cpp
	g++ -g -std=c++11 -O3 -Wall p2.cpp -lm -o p2.out
	valgrind ./p2.out < test.txt

test: all
	./p2.out < test.txt
