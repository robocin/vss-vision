compile:
	g++ server.cpp -o server -lsfml-system -lsfml-network -lsfml-window
	g++ client.cpp -o client -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
rccompile:
	g++ rcclient.cpp -o rcclient -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

run:
	./client & ./server &

rcrun:
	./rcclient &
rc: rccompile rcrun
all: compile run rc
