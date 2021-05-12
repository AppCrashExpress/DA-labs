#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <chrono>

#include "equation.h"
#include "matrix.h"

std::vector<TEquation> GetEquations(size_t eqCount, size_t coefCount, std::istream& is = std::cin) {
    std::vector<TEquation> equations(eqCount);
    std::vector<double> coefs(coefCount);
    double cost;

    for (size_t i = 0; i < eqCount; ++i) {
        for (size_t j = 0; j < coefCount; ++j) {
            is >> coefs[j];
        }
        is >> cost;

        equations[i] = TEquation(coefs, cost);
    }

    return equations;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    size_t equationCount, coefCount;
    std::cin >> equationCount >> coefCount;

    std::vector<TEquation> equations = GetEquations(equationCount, coefCount);
    
    TEquationMatrix matrix(equations);
    matrix.SortEquations();
    auto start = std::chrono::high_resolution_clock::now();
    std::pair<TEquationMatrix, bool> result = matrix.EliminateGauss();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}
