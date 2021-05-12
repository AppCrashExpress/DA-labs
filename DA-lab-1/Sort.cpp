#include <iostream>
#include <stdlib.h>
#include <string.h> //For memset
#include "Vector.h"

constexpr size_t STR_LENGTH = 64 + 1; //Additional byte for '\0' symbol
constexpr size_t KEY_LIMIT = 32 + 1;  //Same
const     short  HEX_SIZE = 16;

struct Slot {
    Slot() {
        key[KEY_LIMIT - 1] = '\0';
    }
    char key[KEY_LIMIT];
    char str[STR_LENGTH];
};

TVector<Slot> RadixSort(const TVector<Slot>& vec, short i) {
    unsigned int count[HEX_SIZE] = {};
    for (TVector<Slot>::Iterator e = vec.Begin(); e != vec.End(); ++e) {
    ++count[ e->key[i] < 'a' ? e->key[i] - '0' : e->key[i] - 'a' + 10 ];
}

    --count[0];
    for (short c = 1; c < HEX_SIZE; ++c) {
        count[c] += count[c - 1];
    }

    TVector<Slot> res(vec.Size());
    short hex2num;
    for (TVector<Slot>::Iterator e = vec.End() - 1; e != vec.Begin() - 1; --e) {
        hex2num = e->key[i] < 'a' ? e->key[i] - '0' : e->key[i] - 'a' + 10;
        res[ count[hex2num] ] = *e;
        --count[hex2num];
    }
    return res;
}

int main() {
    TVector<Slot> vec;
    Slot buff;
    memset(buff.str, '\0', STR_LENGTH);
    while ( scanf("%s", buff.key) != EOF && scanf("%s", buff.str) != EOF ) {
        vec.Push_back(buff);
        memset(buff.str, '\0', STR_LENGTH);
    }
    if (vec.Empty()) {
        return 0;
    }

    for (short i = KEY_LIMIT - 2; i != -1; --i) {
        vec = RadixSort(vec, i);
    }

    for (TVector<Slot>::Iterator e = vec.Begin(); e != vec.End(); ++e) {
        printf("%s\t%s\n", e->key, e->str);
    }
}
