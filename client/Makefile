#PIPE_OPTION=-pipe

EXECUTABLE_FOLDER=bin
SOURCE_FOLDER=src


MAIN_EXECUTABLE=$(EXECUTABLE_FOLDER)/RCClient
MAIN_SRC_FOLDER=$(SOURCE_FOLDER)/main
MAIN_SHARED_SRC_FOLDER=$(SOURCE_FOLDER)/shared
MAIN_SHARED_SRC=$(MAIN_SHARED_SRC_FOLDER)/*.cpp
MAIN_SRC=$(MAIN_SRC_FOLDER)/*.cpp $(MAIN_SHARED_SRC_FOLDER)/Network/*.cpp
MAIN_LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -std=c++11 -fopenmp
MAIN_OHTER_FLAGS=-Wno-deprecated-declarations
MAIN_INC=-Iinclude -I../include

TEST_EXECUTABLE=$(EXECUTABLE_FOLDER)/test
TEST_SRC_FOLDER=$(SOURCE_FOLDER)/test
TEST_SHARED_SRC_FOLDER=$(SOURCE_FOLDER)/shared
TEST_SHARED_SRC=$(TEST_SHARED_SRC_FOLDER)/*.cpp
TEST_SRC=$(TEST_SRC_FOLDER)/*.cpp $(TEST_SHARED_SRC_FOLDER)/Network/*.cpp
TEST_LIBS=-lsfml-system -lsfml-network -std=c++11
TEST_INC=-Iinclude -I../include


compile:
	g++ $(MAIN_SRC) $(MAIN_INC) -o $(MAIN_EXECUTABLE) $(MAIN_LIBS) $(MAIN_OHTER_FLAGS) $(PIPE_OPTION)

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
