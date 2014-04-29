/*
 * =====================================================================================
 *
 *       Filename:  template_virtual.cpp
 *
 *    Description:  template class virtual functions
 *
 *        Version:  1.0
 *        Created:  04/25/2014 20:07:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rong Xiao (rxiao), akelux@gmail.com
 *   Organization:  VRTalents
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

template <class T> class RingInterface {
public:
    virtual const T operator+(const T& b) const = 0;
    virtual const T operator*(const T& b) const = 0;
};

class Integer : public RingInterface<Integer> {
private:
        int val_;
public:
    Integer(int i=0);
    virtual const Integer operator+(const Integer& b) const;
    virtual const Integer operator*(const Integer& b) const;
    operator int() const;
};


Integer::Integer(int i) : val_(i) {}

const Integer Integer::operator+(const Integer& b) const {
    return Integer(val_ + b.val_);
}

const Integer Integer::operator*(const Integer& b) const {
    return Integer(val_ * b.val_);
}

Integer::operator int() const {
    return val_;
}


int main() {
    Integer a(1), b(2);
    cout << a+b << endl;
}
