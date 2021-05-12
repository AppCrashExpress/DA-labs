#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "SuffTree.h"
using namespace NSuff;

std::string GetBestString(unsigned int n) {
    std::string result;

    for (unsigned int i = 0; i < n; ++i) {
        result += 'a' + i % 26;
    }

    return result;
}

std::string GetAverageString(unsigned int n) {
    std::string result;

    for (unsigned int i = 0; i < n; ++i) {
        result += 'a' + std::rand() % 26;
    }

    return result;
}

std::string GetWorstString(unsigned int n) {
    std::string result(n, 'a');

    return result;
}

int main(int argC, char** argV) {
    if (argC <= 1) {
        std::cout << "Not enough arguments" << std::endl;
        return -1;
    }

    std::srand(1);
    std::string str = GetWorstString(std::stol(argV[1]));

    auto start = std::chrono::high_resolution_clock::now();
    TSuffTree tree(str);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
}
