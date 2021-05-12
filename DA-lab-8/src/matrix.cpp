#include <limits>
#include <algorithm>
#include "matrix.h"

template<typename T>
inline T abs(T val) {
    if (val < 0) {
        return -val;
    }
    return val;
}

template <typename T>
inline bool ValIsZero(const T& val) {
    return abs(val) <= std::numeric_limits<T>::epsilon();
}

TEquationMatrix::TEquationMatrix(const std::vector<TEquation>& equations) {
    matrix_.reserve(equations.size());

    size_t i = 0;
    for (const auto& eq : equations) {
        matrix_.push_back({++i, eq});
    }
}

void TEquationMatrix::SortEquations() {
    std::sort(matrix_.begin(), matrix_.end());
}

std::pair<TEquationMatrix, bool> TEquationMatrix::EliminateGauss() const {
    std::vector<int> pivotColumns(matrix_.size(), -1);
    std::vector<TIndexedEquation> result;
    size_t maxCoefCount = matrix_[0].equation.CoefCount();
    
    result.reserve(maxCoefCount);

    for (const auto& origEquation : matrix_) {
        TEquation equationCopy = origEquation.equation;

        for (size_t i = 0; i < result.size(); ++i) {
            equationCopy += result[i].equation * (-equationCopy[ pivotColumns[i] ]);
        }

        if (equationCopy.CheckIfEmpty()) {
            continue;
        }

        pivotColumns[result.size()] = FindPivotColumn(equationCopy);
        equationCopy *= (1 / equationCopy[ pivotColumns[result.size()] ]);
        result.push_back({origEquation.index, equationCopy});

        if (result.size() == maxCoefCount) {
            return std::make_pair(TEquationMatrix(std::move(result)), true);
        }
    }

    return std::make_pair(TEquationMatrix(std::move(result)), false);
}

std::vector<size_t> TEquationMatrix::GetMatrixIndecies() const {
    std::vector<size_t> indecies;
    indecies.reserve(matrix_.size());

    for (const auto& eq : matrix_) {
        indecies.push_back(eq.index);
    }

    return indecies;
}

int TEquationMatrix::FindPivotColumn(const TEquation& eq) const {
    int column = 0;
    for (; column < eq.CoefCount(); ++column) {
        if ( !ValIsZero(eq[column]) ) { return column; } 
    }
    return -1;
}
