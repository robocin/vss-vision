#PIPE_OPTION=-pipe

MAIN_EXECUTABLE=RCClient
MAIN_SRC_FOLDER=src/main
MAIN_SRC=$(MAIN_SRC_FOLDER)/*.cpp
MAIN_LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -std=c++11 -fopenmp
MAIN_OHTER_FLAGS=-Wno-deprecated-declarations

TEST_EXECUTABLE=test
TEST_SRC_FOLDER=src/test
TEST_SRC=$(TEST_SRC_FOLDER)/*.cpp
TEST_LIBS=-lsfml-system -lsfml-network -std=c++11
TEST_INC=-Iinclude -I../include


compile:
	g++ $(MAIN_SRC) -o $(MAIN_EXECUTABLE) $(MAIN_LIBS) $(MAIN_OHTER_FLAGS) $(PIPE_OPTION)

run:
	./$(MAIN_EXECUTABLE)

run_async:
	./$(MAIN_EXECUTABLE) --testing 1> log.txt &

testc:
	g++ $(TEST_SRC) $(TEST_INC) -o $(TEST_EXECUTABLE) $(TEST_LIBS) $(PIPE_OPTION)

testr:
	./$(TEST_EXECUTABLE)

test: compile testc run_async testr

all: compile run
