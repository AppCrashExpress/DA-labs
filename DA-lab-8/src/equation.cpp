#include <limits>
#include <stdexcept>
#include "equation.h"

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

TEquation::TEquation(std::vector<UnderlyingType> coefs,
                     UnderlyingType equationConstraint)
    : coefs_(coefs)
    , constraint_(equationConstraint)
{ }

TEquation::UnderlyingType& TEquation::operator [] (size_t coef) {
    return coefs_[coef];
}

TEquation::UnderlyingType TEquation::operator [] (size_t coef) const {
    return coefs_[coef];
}

bool TEquation::operator < (const TEquation& other) const {
    return constraint_ < other.constraint_;
}

TEquation TEquation::operator * (double rowMult) const {
    TEquation result = *this;

    for (size_t i = 0; i < result.CoefCount(); ++i) {
        result[i] *= rowMult;
    }

    return result;
}

TEquation& TEquation::operator += (const TEquation& other) {
    if (CoefCount() != other.CoefCount()) {
        throw std::out_of_range("In equation, sizes do not match ");
    }

    for (size_t i = 0; i < CoefCount(); ++i) {
        operator[](i) += other[i];
    }

    return *this;
}

TEquation& TEquation::operator *= (double rowMult) {
    for (size_t i = 0; i < CoefCount(); ++i) {
        operator[](i) *= rowMult;
    }

    return *this;
}

bool TEquation::CheckIfSolvable(void) const {
    for (const auto& coef : coefs_) {
        if (!ValIsZero(coef)) { return true; }
    }

    if (constraint_ == 0) { return true; };
    return false;
}

bool TEquation::CheckIfEmpty(void) const {
    for (const auto& coef : coefs_) {
        if (!ValIsZero(coef)) { return false; }
    }

    return true;
}
