CXX = c++
CXXFLAGS = -std=c++11 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
LIBRARY = Vector.h
NAME = Sort.cpp

all: solution

solution: $(LIBRARY) $(NAME)
	$(CXX) $(CXXFLAGS) $(NAME) -o solution
clean:
	rm -f *.o solution
