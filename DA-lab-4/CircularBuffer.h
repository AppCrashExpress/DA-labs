#pragma once
#include <exception>
#include <memory>

template <typename T, typename TSize = unsigned int>
class TCircBuff {
public:
    TCircBuff(TSize capacity) {
        storage = std::unique_ptr<T[]>(new T[capacity]);
        this->capacity = capacity;
        size = 0;
        first = 0;
    }

    TSize Size(void) {
        return size;
    }

    bool Empty(void) {
        return size == 0;
    }

    T& operator [] (TSize num) {
        return storage[(first + num) % capacity];
    }

    TCircBuff& pushBack(T item) {
        if (size == capacity) throw std::out_of_range("Capacity full");
        storage[(first + size) % capacity] = item;
        ++size;
        return *this;
    }

    TCircBuff& removeFirst(TSize amount) {
        if (amount > size) amount = size;
        first = (first + amount) % capacity;
        size -= amount;
        return *this;
    }

private:
    // using TSize = unsigned int;

    std::unique_ptr<T[]> storage;
    TSize capacity;
    TSize size;
    TSize first;
};