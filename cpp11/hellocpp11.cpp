/*
 * hellocpp11.cpp
 *
 *  Created on: 2013-11-22
 *      Author: Rong Xiao
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    auto i = 1; // auto keyword
    decltype(i) j = i; // decltype keyword
    cout << i + j << endl;
    vector<int> vec={1, 2, 3, 4};
    for (vector<int>::size_type i = 0; i<vec.size(); ++i) {
        cout << ' ' << vec[i];
    }

    cout << endl;

    vector<int>* pVec = nullptr; // nullptr keyword

    pVec = new vector<int>(vec);

    auto p = pVec;

    for (auto i = p->size(); i>0; ) {
        cout << ' ' << p->at(--i);
    }
    cout << endl;

    for (auto it = p->begin(); it!=p->end(); ++it) {
        decltype(it) cur;
        cout << ' ' << *it;
        cur = it;
        cout << ' ' << *cur;
    }
    cout << endl;

    delete pVec;

    return 0;
}



