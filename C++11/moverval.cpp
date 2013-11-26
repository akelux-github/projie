/*
 * moverval.cpp
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
using std::ostream;

class Movable {
    vector<int> vec;
public:
    Movable(const vector<int>& v) : vec{v} {}
    Movable(const Movable& v) = delete;
    Movable(Movable&& rval) = default;
    Movable& operator=(Movable&& rval) = default;
    friend ostream& operator<<(ostream& os, const Movable& m);
    size_t size() {
        return vec.size();
    }
};

ostream& operator<<(ostream& os, const Movable& m) {
    for (auto it = m.vec.begin(); it != m.vec.end(); ++it) {
        os << ' ' << *it;
    }
    return os;
}

int main() {
    vector<int> v = {1,2,3,4,5};
    Movable m{v};
    cout << m << endl;

    Movable m1{std::move(m)};
    cout << m1 << endl;
    cout << m.size() << endl;

    m = std::move(m1); // m = m1 causes error
    cout << m.size() << endl;
    cout << m1.size() << endl;
    return 0;
}






