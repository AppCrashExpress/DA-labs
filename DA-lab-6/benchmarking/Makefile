SRC_DIR = ../src
INC_DIR = ../include
OBJ_DIR = ../obj

CXX = g++
DEBUG = -std=c++11 -O0 -g
NODEBUG = -std=c++11 -O2
CXXFLAGS = $(DEBUG) -I $(INC_DIR) -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

FILES = operation.cpp $(OBJ_DIR)/*.o
LIBNAME = bigint
NAME = bench

.PHONY: all solve $(LIBNAME) clean

all: solve

solve: $(LIBNAME) operation.cpp
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

$(LIBNAME): $(INC_DIR)/$(LIBNAME).h $(SRC_DIR)/$(LIBNAME).cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(LIBNAME).cpp -c -o $(OBJ_DIR)/$(LIBNAME).o

clean:
	rm -f $(OBJ_DIR)/*.o $(NAME)

