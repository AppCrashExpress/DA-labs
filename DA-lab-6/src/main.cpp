#include <iostream>
#include <string>
#include "bigint.h"


int main() {
    std::string aStr, bStr;
    char operation;

    while (std::cin >> aStr && std::cin >> bStr && std::cin >> operation) {
        TBigInt a(aStr);
        TBigInt b(bStr);

        switch(operation) {
            case '+':
                std::cout << (a + b) << std::endl;
                break;

            case '-':
                std::cout << (a - b) << std::endl;
                break;

            case '*':
                std::cout << (a * b) << std::endl;
                break;

            case '/':
                std::cout << (a / b) << std::endl;
                break;

            case '^':
                if (a == TBigInt(0)) {
                    std::cout << (b == TBigInt(0) ? "Error" : "0") << std::endl;
                } else if (a == TBigInt(1)) {
                    std::cout << "1" << std::endl;
                } else {
                    std::cout << (a ^ stoll(bStr)) << std::endl;
                }
                break;

            case '>':
                std::cout << ( (a > b) ? "true" : "false" ) << std::endl;
                break;

            case '<':
                std::cout << ( (a < b) ? "true" : "false" ) << std::endl;
                break;

            case '=':
                std::cout << ( (a == b) ? "true" : "false" ) << std::endl;
                break;

        }
    }
}
