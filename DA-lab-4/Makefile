CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp
NAME = solution

all: example

example:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

debug:
	$(CXX) -std=c++11 -O0 -g -Wall -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME)
