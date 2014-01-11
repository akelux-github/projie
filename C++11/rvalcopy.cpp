/*
 * rvalcopy.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: Rong
 */

#include <iostream>
using namespace std;

class C {
static int i;
public:
    C() : id(++i), v(nullptr) { cout << "default ctor: " << id << endl; }
    ~C() {cout << "dtor: " << id << endl;}
    C(const C& c) : id(++i), v(c.v) {
        cout << "copying ctor" << endl;
    }

    C(C&& c) : id(++i), v(c.v) {
        cout << "moving ctor" << endl;
        c.v = nullptr;
        c.id = -1;
    }

    C& operator=(const C& other) {
        cout << "copy" << endl;
        // copy contents of v[]
        return *this;
    }

    C& operator=(C&& other) {
        cout << "move" << endl;
        v = other.v;
        other.v = nullptr;
        other.id = -1;
        return *this;
    }

private:
    int id{0};
    int* v;
    friend ostream& operator<<(ostream&os, const C& c);
};

ostream& operator<<(ostream&os, const C& c) {
    os << "printing C object of id: " << c.id << endl;
    return os;
}

const C const_is_returned() { cout << "constructing a temporary object"<< endl; return C(); }

C nonconst_is_returned() { cout << "constructing a temporary object"<< endl; return C(); } // if move defined, then using move due by default

int C::i{0};

int main(int argc, char* argv[]) {
    C c;
    c = const_is_returned(); //
    c = nonconst_is_returned();
    C c1 = nonconst_is_returned(); // compiler optimization cause no copy ctor is actually called
    cout << "-----" << c1 << endl;
    // c1.~C();

    C c2(const_is_returned());
    cout << "-----" << c2 << endl;
    // c2.~C();
    return 0;
}



