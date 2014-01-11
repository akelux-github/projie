#include <iostream>
using namespace std;


class Test {
    public:
        static void print() {
            cout << "Test" <<endl;
        }
};

class Test2: public Test {
};

class Test3 {
    public:
        operator Test() {
            return Test();
        }
};


int main() {
    Test t;
    t.print();
    Test2 t2;
    t2.print();
    Test3 t3;
    static_cast<Test>(t3).print();
    return 0;
}
