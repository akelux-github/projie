#include "namespace.hpp"

namespace {
   int a = 0;
}


namespace prints {
void print1() {
    ++a;
    print();
}
}
