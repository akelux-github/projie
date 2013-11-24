/*
 * defaultdelete.cpp
 *
 *  Created on: 2013-11-24
 *      Author: Rong Xiao
 */

/*
 * userliterals.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Rong
 */
#include <vector>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    auto v = {string("Rong"), string("Xiao")};
    vector<string> vs{v};

    decltype(vs) v2{v}; // An error if specifying decltype(v)

    for (auto& i: v) {
        cout << i << endl;
    }

    for (auto& v: vs) {
        cout << v << endl;
    }

    for (auto& v: v2) {
        cout << v << endl;
    }
    return 0;
}



