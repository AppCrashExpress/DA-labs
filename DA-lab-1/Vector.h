#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>

template<typename T>
class TVector {
public:
    typedef T Type, *Iterator;


    TVector() : StorageUsed(0), StorageSize(0), storage(nullptr) { }
    TVector(int size, const Type& default_value = Type()) :
        TVector() {
            if (size <= 0) return;

            StorageUsed = StorageSize = size;
            storage = new Type[size];
            std::fill(storage, storage + StorageUsed, default_value);
        }

    TVector(const TVector& other) {
        TVector next(other.StorageSize);
        next.StorageUsed = other.StorageUsed;

        if (other.storage != nullptr)
        std::copy(other.storage, other.storage + other.StorageUsed, next.storage);
        Swap(*this, next);
    }

    ~TVector() {
        if (storage)
        delete[] storage;
    }

    TVector& operator = (TVector other) {
        Swap (*this, other);
        return *this;
    }

    Type& operator [] (size_t index) {
        if (index >= StorageUsed)
        std::out_of_range("Attempting to access non-existing slot");
        return storage[index];
    }

    size_t Size() const {
        return StorageUsed;
    }

    bool Empty() const {
        return Size() == 0;
    }

    Iterator Begin() const {
        return storage;
    }

    Iterator End() const {
        if (storage != nullptr) return storage + StorageUsed;
        return nullptr;
    }

    void Push_back(const Type& value) {
        if (StorageUsed < StorageSize) {
            storage[StorageUsed] = value;
            ++StorageUsed;
            return;
        }
        size_t next_size = 1;
        if (StorageSize) {
            next_size = StorageSize * 2;
        }

        TVector next(next_size);
        next.StorageUsed = StorageUsed;

        if (storage)
            std::copy(storage, storage + StorageUsed, next.storage);
        next.storage[next.StorageUsed] = value;
        ++next.StorageUsed;
        Swap(*this, next);
        return;
    }

    friend void Swap(TVector& lhs, TVector& rhs) {
        std::swap(lhs.StorageUsed, rhs.StorageUsed);
        std::swap(lhs.StorageSize, rhs.StorageSize);
        std::swap(lhs.storage    , rhs.storage    );
    }

private:
    size_t StorageUsed;
    size_t StorageSize;
    Type *storage;
};

#endif


