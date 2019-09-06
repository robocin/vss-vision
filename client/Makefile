compile:
	g++ RCClient.cpp -o RCClient -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -std=c++11 -fopenmp

run:
	./RCClient

tesc:
	g++ test.cpp -o test -lsfml-system -lsfml-network -std=c++11

testr:
	./test

test: testc run testr

all: compile run
