#ifndef EQUATION_H
#define EQUATION_H

#include <vector>

class TEquation {
public:
    using UnderlyingType = double;

    TEquation() {  };
    TEquation(std::vector<UnderlyingType> coefs,
              UnderlyingType equationConstraint);

    UnderlyingType& operator [] (size_t coef);
    UnderlyingType operator [] (size_t coef) const;
    bool operator < (const TEquation& other) const;
    TEquation operator * (double rowMult) const;
    TEquation& operator += (const TEquation& other);
    TEquation& operator *= (double rowMult);

    bool CheckIfSolvable(void) const;
    bool CheckIfEmpty(void) const;

    size_t CoefCount() const { 
        return coefs_.size();
    }

private:
    std::vector<UnderlyingType> coefs_;
    UnderlyingType constraint_;

};

#endif
