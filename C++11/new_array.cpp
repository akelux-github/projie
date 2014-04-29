/*
 * =====================================================================================
 *
 *       Filename:  new_array.cpp
 *
 *    Description:  new array of class without default constructor, then initialize with placement new
 *
 *        Version:  1.0
 *        Created:  04/29/2014 16:04:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rong Xiao (rxiao), akelux@gmail.com
 *   Organization:  VRTalents
 *
 * =====================================================================================
 */
#include <new>
#include <iostream>
using namespace std;

class Test {
private:
    int id_;

public:
    // explicit Test(int i) : id_(i) {}
    Test(int i=0) : id_(i) {}
    Test(const Test& t) : id_(t.id_) {}
    Test& operator=(const Test& t) {
        id_ = t.id_;
        return *this;
    }
    operator int() {
        return id_;
    }
};

int main() {
    Test* arr = new Test[10];
    for (unsigned i=0; i<10; i++) {
        cout << arr[i] << endl;
    }

    cout << "cool" << endl;
    int* i_arr = new int[4];
    for (unsigned i=0; i<4; i++) {
        // cout << "i: "<< i << "<->" << i_arr[i] << endl;
        cout << i_arr[i] << endl;
    }

    delete [] i_arr;
    delete [] arr;

    return 0;
}
