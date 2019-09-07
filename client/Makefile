compile:
	g++ RCClient.cpp -o RCClient -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -std=c++11 -fopenmp -Wno-deprecated-declarations

run:
	./RCClient

run_async:
	./RCClient &

testc:
	g++ test.cpp ../src/Network/Network.h -I. -o test -lsfml-system -lsfml-network -std=c++11

testr:
	./test

test: compile testc run_async testr

all: compile run
