/*
 * defaultdelete.cpp
 *
 *  Created on: 2013-11-24
 *      Author: Rong Xiao
 */
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;


struct B1 {
    int y{0};
    B1() = delete;
    B1(int x) : y(x)  { }
    B1(const B1&& b) = delete; // disables auto-generated ctor and copy assignment
    B1(const B1& b) = default; // using the auto-generated one, on implementation is needed
    B1& operator=(const B1& b) = default; // default bring auto generated back

    void print(float f) const {
        cout << f+1 << endl;
    }
};

struct D1 : B1 {
    D1(int x=0) : B1(x) {}
    // using B1::B1; // implicitly declares D1(int) // not supported until gcc4.8
    // using B1::print;
    int x{2};
    void print() {
        cout << "x: " << x << "\ty:" << y << endl;
    }

    void print(int f) const {
        cout << f << endl;
    }
};

int main() {
    D1 d(6);    // Oops: d.x is not initialized
    d.print();
    d.print(3.5f);
    D1 d1;
    d1.print();

    B1 b(4);
    B1 b2{b};
    b2 = b;
    // D1 e;       // error: D1 has no default constructor
    return 0;
}



