SRC_DIR = ./src

CXX = g++
DEBUG = -std=c++11 -O0 -g
NODEBUG = -std=c++11 -O2
CXXFLAGS = -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

FILES = $(SRC_DIR)/main.cpp 
NAME = solution

.PHONY: all solve debug clean

all: solve

solve: $(SRC_DIR)/main.cpp
	$(CXX) $(NODEBUG) $(CXXFLAGS) -o $(NAME) $(FILES)

debug: $(SRC_DIR)/main.cpp
	$(CXX) $(DEBUG) $(CXXFLAGS) -o $(NAME) $(FILES)

clean:
	rm -f $(OBJ_DIR)/*.o $(NAME)

