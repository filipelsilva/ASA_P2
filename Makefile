.PHONY: all clean test

all: p2.cpp randomDAG.cpp
	g++ -std=c++11 -O3 -Wall p2.cpp -lm -o p2.out
	g++ -std=c++11 -O3 -Wall randomDAG.cpp -lm -o randomDAG.out

clean: p2.out randomDAG.out
	rm *.out

test: p2.out
	./p2.out < test.txt
