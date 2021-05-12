#include <iostream>
#include <string>
#include <chrono>
#include "bigint.h"

std::string RepeatStr(std::string str, unsigned int count) {
    std::string result;
    for (unsigned int i = 0; i < count; ++i) {
        result += str;
    }

    return result;
}

int main(int argc, char** argv) {
    if (argc < 3) { 
        std::cerr << "Not enough arguments" << std::endl;
        return -1;
    }
    const std::string ONE_DIGIT = "99";

    TBigInt a = TBigInt( RepeatStr(ONE_DIGIT, std::stoi(argv[1])) );
    TBigInt b = TBigInt( RepeatStr(ONE_DIGIT, std::stoi(argv[2])) ) - 1;

    auto start = std::chrono::high_resolution_clock::now();
    TBigInt c =  a / b;
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}
