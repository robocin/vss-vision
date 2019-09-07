#PIPE_OPTION=-pipe
compile:
	g++ RCClient.cpp -o RCClient -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -std=c++11 -fopenmp -Wno-deprecated-declarations $(PIPE_OPTION)

run:
	./RCClient

run_async:
	./RCClient &

testc:
	g++ test.cpp Network.cpp -Iinclude -I../include -o test -lsfml-system -lsfml-network -std=c++11 $(PIPE_OPTION)

testr:
	./test

test: compile testc run_async testr

all: compile run
