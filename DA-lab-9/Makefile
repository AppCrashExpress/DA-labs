SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj

CXX = g++
DEBUG = -std=c++11 -O0 -g
NODEBUG = -std=c++11 -O2
CXXFLAGS = $(DEBUG) -I $(INC_DIR) -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = ${SRC_DIR}/main.cpp $(OBJ_DIR)/*.o
NAME = solution

all: solve

solve: network $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

debug: network $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

network: $(INC_DIR)/FlowNetwork.h $(SRC_DIR)/FlowNetwork.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/FlowNetwork.cpp -c -o $(OBJ_DIR)/FlowNetwork.o

clean:
	rm -f $(OBJDIR)/*.o $(NAME)

