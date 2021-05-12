CXX = g++
CXXFLAGS = -std=c++11 -O0 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -g

.PHONY: all
all: solution

solution: menu.o b-tree.o
	$(CXX) $(CXXFLAGS) b-tree.o menu.o -o solution

menu.o: menu.cpp b-tree.o
	$(CXX) $(CXXFLAGS) -c menu.cpp

b-tree.o: b-tree.h b-tree.cpp
	$(CXX) $(CXXFLAGS) -c b-tree.cpp

.PHONY: clean
clean:
	rm -f *.o solution
