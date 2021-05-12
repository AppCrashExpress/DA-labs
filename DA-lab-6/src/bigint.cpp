#include "bigint.h"

TBigInt::TBigInt() { }
TBigInt::TBigInt(const TBigInt& other) {
    container = other.container;
}
TBigInt::TBigInt(TBigInt&& other) {
    std::swap(container, other.container);
}
TBigInt::TBigInt(TPrimitive val) {
    if (val == 0) {
        container.push_back(0);
    } else {
        while (val) {
            container.push_back(val % BASE_VAL);
            val /= BASE_VAL;
        }
    }
}
TBigInt::TBigInt(const std::string& valStr) {
    long long nonZeroPos = valStr.find_first_not_of("0");    

    // Add size_t to appease the warning
    // If it ends up being -1, should not be a problem
    if ((size_t)nonZeroPos == std::string::npos) {
        container.push_back(0);
        return;
    }

    for (long long i = valStr.size() - 1; i >= nonZeroPos; i -= BASE_LEN) {
        TPrimitive parsed = 0;
        long long begin = i - BASE_LEN + 1;

        if (begin < 0) {
            begin = 0;
        }

        for (long long j = begin; j < i + 1; ++j) {
            parsed *= 10;
            parsed += valStr[j] - '0';
        }

        container.push_back(parsed);
    }

}

TBigInt& TBigInt::operator=(TBigInt& other) {
    container = other.container;
    return *this;
}

TBigInt& TBigInt::operator=(TBigInt&& other) {
    std::swap(container, other.container);
    return *this;
}

TBigInt TBigInt::operator+(const TBigInt& other) const {
    TBigInt result;
    size_t maxSize = std::max(container.size(), other.container.size());

    result.container.reserve(maxSize + 1);

    TPrimitive carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        TPrimitive sum = SumAtPos(other, i) + carry;
        result.container.push_back(sum % BASE_VAL);
        carry = sum / BASE_VAL;
    }

    if (carry) {
        result.container.push_back(carry);
    }

    return result;
}

TBigInt TBigInt::operator-(const TBigInt& other) const {
    TBigInt result;
    size_t maxSize = std::max(container.size(), other.container.size());

    result.container.reserve(maxSize + 1);

    if (*this < other) {
        return TBigInt(-1);
    }

    TPrimitive carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        TPrimitive sub = SubAtPos(other, i) + carry;
        carry = 0;
        if (sub < 0) {
            carry = -1;
            sub += BASE_VAL;
        }
        result.container.push_back(sub);
    }
    // Carry should not go outside of loop
    // Otherwise the second number is bigger than first

    result.RemoveLeadingZeroes();

    return result;
}

TBigInt TBigInt::operator*(const TBigInt& other) const {
    TBigInt result;
    const size_t thisSize  = container.size();
    const size_t otherSize = other.container.size();
    const size_t maxSize = thisSize + otherSize;

    result.container.resize(maxSize, 0);
    TPrimitive carry = 0;
    for (size_t j = 0; j < otherSize; ++j) {
        carry = 0;

        for (size_t i = 0; i < thisSize; ++i) {
            TPrimitive mult = container[i] *
                other.container[j] +
                result.container[i + j] +
                carry;

            result.container[i + j] = mult % BASE_VAL;
            carry = mult / BASE_VAL;
        }
        
        result.container[j + thisSize] = carry;
    }

    result.RemoveLeadingZeroes();

    return result;
}

TBigInt TBigInt::operator/(const TBigInt& other) const {
    
    if (other == TBigInt(0)) {
        // This looks really stupid
        // but it will work for now
        return TBigInt(-1);
    }

    // This was infuriating
    // The idea of algo below is to perfom pen and paper division
    // To visualise with something familiar, it will look like
    //      
    //      this TBigInt     | other  TBigInt
    //    -                  +---------------
    //      other * mid      | result TBigInt 
    //      -----------------|
    //             remainder |

    TBigInt current;
    TBigInt result;

    result.container.resize(container.size());
    
    for (long long i = container.size() - 1; i >= 0; --i) {
        current.container.insert(current.container.begin(), container[i]);
        if (!current.container.back()) {
            // Remove the zero gained from subtraction, if any
            current.container.pop_back();
        }
        long long maxDivisor = 0;
        long long low  = 0;
        long long high = BASE_VAL;
        
        while(low <= high) {
            long long mid = (low + high) / 2;
            if ( !(other * TBigInt(mid) > current) ) {
                maxDivisor = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        result.container[i] = maxDivisor;
        current = current - other * maxDivisor;
    }

    result.RemoveLeadingZeroes();
    return result;
}

TBigInt TBigInt::operator^(TPrimitive power) const {
    if ((*this) == TBigInt(0) && power == 0) {
        return TBigInt(-1);
    }

    return Exponentate(power);
}

bool operator<(const TBigInt& a, const TBigInt& b) {
    const std::vector<long long>& aCont = a.container;
    const std::vector<long long>& bCont = b.container;

    if (aCont.size() != bCont.size()) {
        return aCont.size() < bCont.size();
    }

    // auto == std::vector<long long>::reverse_iterator
    for (auto aIter = aCont.crbegin(), bIter = bCont.crbegin();
              aIter != aCont.crend();
              ++aIter, ++bIter) {
        if ( *aIter != *bIter) {
            return *aIter < *bIter;
        }
    }

    // All parts are equal
    return false;
}

bool operator>(const TBigInt& a, const TBigInt& b) {
    const std::vector<long long>& aCont = a.container;
    const std::vector<long long>& bCont = b.container;

    if (aCont.size() != bCont.size()) {
        return aCont.size() > bCont.size();
    }

    // auto == std::vector<long long>::reverse_iterator
    for (auto aIter = aCont.crbegin(), bIter = bCont.crbegin();
              aIter != aCont.crend();
              ++aIter, ++bIter) {
        if ( *aIter != *bIter) {
            return *aIter > *bIter;
        }
    }

    // All parts are equal
    return false;
}

bool operator==(const TBigInt& a, const TBigInt& b) {
    return a.container == b.container;
}

std::ostream& operator<<(std::ostream& os, const TBigInt& bigint) {
    long long contSize = bigint.container.size();

    // Empty container is not expected and should contain at least 0

    if (bigint.container[0] == -1) {
        os << "Error";
        return os;
    }

    os << bigint.container[contSize - 1];
    for (long long i = contSize - 2; i >= 0; --i) {
        os << std::setfill('0') << std::setw(bigint.BASE_LEN) << bigint.container[i];
    }

    return os;
}

TBigInt::TPrimitive TBigInt::SumAtPos(const TBigInt& other, const size_t pos) const {
    TPrimitive sum = 0;

    if (pos < container.size()) {
        sum += container[pos];
    }
    if (pos < other.container.size()) {
        sum += other.container[pos];
    }

    return sum;
}


TBigInt::TPrimitive TBigInt::SubAtPos(const TBigInt& other, const size_t pos) const {
    TPrimitive sub = 0;

    if (pos < container.size()) {
        sub += container[pos];
    }
    if (pos < other.container.size()) {
        sub -= other.container[pos];
    }

    return sub;
}

void TBigInt::RemoveLeadingZeroes() {
    size_t zeroCount = 0;
    for (auto begin = container.crbegin(); begin != container.crend(); ++begin) {
        if (*begin == 0) {
            ++zeroCount;
        } else {
            break;
        }
    }

    // For when we get a zero value
    if (zeroCount == container.size()) {
        --zeroCount;
    }
    container.resize(container.size() - zeroCount);
}

TBigInt TBigInt::Exponentate(TPrimitive power) const {
    if (power == 0) {
        return TBigInt(1);
    }

    TBigInt halved = this->Exponentate(power/2);

    if (power % 2 == 0) {
        return halved * halved;
    } else {
        // When odd value is divided by two,
        // value that is equal to <(odd - 1) / 2> returned
        // so essentually their multiplication equals odd - 1
        // Additionally multiply by this value
        return halved * halved * (*this);
    }
}
