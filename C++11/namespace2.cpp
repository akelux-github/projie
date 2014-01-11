#include "namespace.hpp"

namespace {
    int a = 1;
}


namespace prints {
    void print2() {
        ++a;
        print();
    }
}
