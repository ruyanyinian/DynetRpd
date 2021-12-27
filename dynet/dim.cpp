#include "dynet/dim.hpp"
#include <iostream>
using namespace std;


namespace dynet {
ostream& operator<<(ostream& os, const Dim& d) {
  os << '{';
  for (unsigned i = 0; i < d.nd; ++i) {
    if (i) os << ',';
    os << d.d[i];
  }
  if(d.bd != 1) os << 'X' << d.bd;
  return os << '}';
}
}

