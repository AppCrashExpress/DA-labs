SRC_DIR = .

CXX = g++
DEBUG = -std=c++11 -O0 -g
NODEBUG = -std=c++11 -O2
CXXFLAGS = -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

FILES = $(SRC_DIR)/main_mod.cpp 
NAME = bench

.PHONY: all solve debug clean

all: solve

solve: $(SRC_DIR)/main_mod.cpp
	$(CXX) $(NODEBUG) $(CXXFLAGS) -o $(NAME) $(FILES)

debug: $(SRC_DIR)/main_mod.cpp
	$(CXX) $(DEBUG) $(CXXFLAGS) -o $(NAME) $(FILES)

clean:
	rm -f $(OBJ_DIR)/*.o $(NAME)

