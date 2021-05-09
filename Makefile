.PHONY: all clean test

all: p2.cpp
	g++ -std=c++11 -O3 -Wall p2.cpp -lm -o p2.out

clean: p2.out
	rm *.out

test: p2.out
	./p2.out < test.txt
