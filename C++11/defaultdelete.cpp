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
    B1(int x) : y(x) { }
    int y;
};

struct D1 : B1 {
    // using B1::B1; // implicitly declares D1(int) // not supported until gcc4.8
    int x;
    void print() {
        cout << "x: " << x << "\ty:" << y << endl;
    }
};

int main() {
    D1 d(6);    // Oops: d.x is not initialized
    d.print();
    // D1 e;       // error: D1 has no default constructor
    return 0;
}



