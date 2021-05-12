#include <iostream>
#include <stdlib.h>
#include <string.h> //For memset
#include "Vector.h"

const size_t key_limit = 32 + 1; //Additional byte for '\0' symbol
const size_t str_length = 64 + 1; //Same
const short  hex_size = 16;

// inline int hex2num(const char& c) {
//   if (c>='0' && c<='9') return c - '0';
//   if (c>='A' && c<='F') return c - 'A' + 10;
//   if (c>='a' && c<='f') return c - 'a' + 10;
//   exit(0);
// }
struct Slot {
  Slot() {
    key[32] = '\0';
  };

  char key[key_limit];
  char str[str_length];
};

// Vector<Slot> radixsort(const Vector<Slot>& vec, short i) {
//   Vector<Slot> bucket[hex_size];
//   for (Vector<Slot>::iterator e = vec.begin(); e != vec.end(); ++e) {
//     bucket[ e->key[i] >= 'a' ? e->key[i] - 'a' + 10 : e->key[i] - '0' ].push_back(*e);
//   }
//
//   Vector<Slot> res;
//   for (short j = 0; j < hex_size; ++j) {
//     if (!bucket[j].empty()) {
//       Vector<Slot>& temp = bucket[j];
//       for (auto e = temp.begin(); e != temp.end(); ++e)
//         res.push_back(*e);
//     }
//   }
//   return res;
// }


Vector<Slot> radixsort(const Vector<Slot>& vec, short i) {
  short count[hex_size] = {};
  for (Vector<Slot>::iterator e = vec.begin(); e != vec.end(); ++e) {
    ++count[ e->key[i] < 'a' ? e->key[i] - '0' : e->key[i] - 'a' + 10 ];
  }

  --count[0];
  for (short c = 1; c < hex_size; ++c) {
    count[c] += count[c-1];
  }
  if (count[hex_size-1] != vec.size() - 1) exit(0);

  Vector<Slot> res(vec.size());
  short hex_to_num;
  for (Vector<Slot>::iterator e = vec.end() - 1; e != vec.begin() - 1; --e) {
    hex_to_num = e->key[i] < 'a' ? e->key[i] - '0' : e->key[i] - 'a' + 10;
    res[ count[hex_to_num] ] = *e;
    --count[hex_to_num];
  }
  return res;
}

int main() {
  Vector<Slot> vec;
  Slot buff;
  memset(buff.str, '\0', str_length);
  while ( scanf("%s", buff.key) != EOF && scanf("%s", buff.str) != EOF ) {
    vec.push_back(buff);
    memset(buff.str, '\0', str_length);
  }
  if (vec.empty()) {
    return 0;
  }

  for (short i = key_limit - 2; i != -1; --i) {
    vec = radixsort(vec, i);
  }

  for (Vector<Slot>::iterator e = vec.begin(); e != vec.end(); ++e) {
    printf("%s\t%s\n", e->key, e->str);
  }
}
