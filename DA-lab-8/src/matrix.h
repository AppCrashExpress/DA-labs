#ifndef EQUATION_MATRIX_H
#define EQUATION_MATRIX_H

#include <utility>
#include <vector>
#include "equation.h"

class TEquationMatrix {
public:
    TEquationMatrix();
    TEquationMatrix(const std::vector<TEquation>& eq);

    void SortEquations();

    std::pair<TEquationMatrix, bool> EliminateGauss() const;

    std::vector<size_t> GetMatrixIndecies() const;

private:
    struct TIndexedEquation {
        size_t index;
        TEquation equation;
        bool operator < (const TIndexedEquation& other) const {
            return equation < other.equation;
        }
    };

    TEquationMatrix(std::vector<TIndexedEquation>&& vec)
        : matrix_(vec)
        { };

    int FindPivotColumn(const TEquation& eq) const;

    std::vector<TIndexedEquation> matrix_;
};

#endif
