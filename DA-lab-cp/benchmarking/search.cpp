#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "diff.h"

std::vector<std::string> read_file(char* filename) {
    std::ifstream is(filename);
    std::string line;
    std::vector<std::string> text;

    while(std::getline(is, line)) {
        text.push_back(line);
    }

    return text;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout 
            << "Usage: " 
            << argv[0] 
            << " FILE1 FILE2" 
            << std::endl;
        return -1;
    }

    std::vector<std::string> text1 = read_file(argv[1]);
    std::vector<std::string> text2 = read_file(argv[2]);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<TAction> actions( find_diff(text1, text2) );

    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
}
