/*
 * initializer.cpp
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

#include <iostream>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

int main(int argc, char** args) {
    unique_ptr<vector<int>> p {new vector<int>{1,2,3,4}};

    for (auto v : *p) {
        cout << ' ' << v;
    }
    cout << endl;

    for (auto it = p->begin(); it != p->end(); ++it) {
        cout << ' ' << (*it);
    }
    cout << endl;

    int a[5] = {1,2,3,4,5};

    for (auto v : a) {
        cout << ' ' << v;
    }

    cout << endl;

    int* b = new int[5]{-1,-2,3}; // initialize partially array
    /*
    for (auto v : b) {
        cout << ' ' << v;
    }

    cout << endl;
     */
    for (unsigned i = 0; i<5; ++i) {
        cout << ' ' << b[i];
    }
    cout << endl;
    delete [] b;

    char* c = new char[5]{'a','b','c'}; // initialize partially array
        /*
        for (auto v : b) {
            cout << ' ' << v;
        }

        cout << endl;
         */
        for (unsigned i = 0; i<5; ++i) {
            cout << ' ' << c[i];
        }
        cout << endl;
        cout << c << endl;
        delete [] c;

        vector<int>* pv = new vector<int>[5]{{1,3,9,27},{2,3,4},{3,4,5}};
        for (unsigned i = 0; i<5; ++i) {
                    for (auto x : pv[i]) {
                        cout << ' ' << x;
                    }
                    cout << " --------"<< endl;
                }
                cout << endl;

               delete [] pv;
    return 0;
}



