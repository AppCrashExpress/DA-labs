SRC_DIR = ../src
INC_DIR = ../include
OBJ_DIR = ../obj
TEST_DIR = .

CXX = g++
CXXFLAGS = -I $(INC_DIR) -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

LIBNAME = bigint
NAME = test
FILES = $(TEST_DIR)/tests.cpp $(OBJ_DIR)/$(LIBNAME).o

.PHONY: all test $(LIBNAME) clean

all: test

test: $(LIBNAME) $(TEST_DIR)/tests.cpp
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

$(LIBNAME): $(INC_DIR)/$(LIBNAME).h $(SRC_DIR)/$(LIBNAME).cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(LIBNAME).cpp -c -o $(OBJ_DIR)/$(LIBNAME).o

clean:
	rm -f $(NAME)

