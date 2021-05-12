#pragma once
#include <stdexcept>
#include <array>

template <typename T, size_t ArrSize, typename TSize = unsigned int>
class TStaticQueue {
public:
    TStaticQueue() {
        storage = std::array<T, ArrSize>();
        capacity = ArrSize;
        size = 0;
        first = 0;
    }

    TSize Size(void) {
        return size;
    }

    bool Empty(void) {
        return size == 0;
    }
    
    void Clear(void) {
        first = 0;
        size = 0;
    }

    T& operator [] (TSize num) {
        return storage[(first + num) % capacity];
    }

    void PushBack(T item) {
        if (size == capacity) throw std::out_of_range("STATIC_QUEUE:FULL");
        storage[(first + size) % capacity] = item;
        ++size;
    }

    void RemoveFirst(void) {
        first = (first + 1) % capacity;
        size -= 1;
    }

    T Front(void) {
        if (size == 0) throw std::out_of_range("STATIC_QUEUE:EMPTY");
        return storage[first];
    }
private:
    // using TSize = unsigned int;

    std::array<T, ArrSize> storage;
    TSize capacity;
    TSize size;
    TSize first;
};
