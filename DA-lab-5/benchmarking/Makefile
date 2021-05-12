SRC_DIR = ..
INC_DIR = ..
OBJ_DIR = ..
BENCH_DIR = .

CXX = g++
CXXFLAGS = -I $(INC_DIR) -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

LIBNAME = SuffTree
NAME = bench
FILES = $(BENCH_DIR)/search.cpp $(OBJ_DIR)/$(LIBNAME).o

.PHONY: all test $(LIBNAME) clean

all: test

test: $(LIBNAME) $(FILES)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

$(LIBNAME): $(INC_DIR)/$(LIBNAME).h $(SRC_DIR)/$(LIBNAME).cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(LIBNAME).cpp -c -o $(OBJ_DIR)/$(LIBNAME).o

clean:
	rm -f $(NAME)


