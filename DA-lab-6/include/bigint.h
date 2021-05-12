#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
#include <iomanip>
#include <vector>

class TBigInt {
public:
    using TPrimitive = long long;

    TBigInt();
    TBigInt(const TBigInt&);
    TBigInt(TBigInt&&);
    TBigInt(TPrimitive);
    TBigInt(const std::string&);

    TBigInt& operator=(TBigInt&);
    TBigInt& operator=(TBigInt&&);

    TBigInt  operator+(const TBigInt&) const;
    TBigInt  operator-(const TBigInt&) const;

    TBigInt  operator*(const TBigInt&) const;
    TBigInt  operator/(const TBigInt&) const;

    TBigInt  operator^(TPrimitive)     const;

    friend bool          operator< (const TBigInt&, const TBigInt&);
    friend bool          operator> (const TBigInt&, const TBigInt&);
    friend bool          operator==(const TBigInt&, const TBigInt&);

    friend std::istream& operator>>(std::istream&, TBigInt&);
    friend std::ostream& operator<<(std::ostream&, const TBigInt&);

private:
    std::vector<TPrimitive> container;
    
    // base value is one digit less than max signed
    // const TPrimitive BASE_VAL = 100000000000000000;
    // const TPrimitive BASE_LEN = 17;
    const TPrimitive BASE_VAL = 100;
    const TPrimitive BASE_LEN = 2;

    TPrimitive SumAtPos(const TBigInt&, const size_t) const;
    TPrimitive SubAtPos(const TBigInt&, const size_t) const;
    void       RemoveLeadingZeroes();
    TBigInt    Exponentate(TPrimitive) const;
};
    
#endif
