/*
 * nullptr.cpp
 *
 *  Created on: 2013-11-26
 *      Author: Rong Xiao
 */

/*
 * printrbtree.cpp
 *
 *  Created on: 2013-11-26
 *      Author: Rong Xiao
 */

#include "redblacktree.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    int* i = 0; // automatically set i = nullptr
    int* j = nullptr;

    cout <<  (i == j) << endl; // true
    cout <<  (nullptr == reinterpret_cast<int*>(0)) << endl; // true
    cout <<  (nullptr == reinterpret_cast<int*>(1)) << endl; // false


    return 0;
}




