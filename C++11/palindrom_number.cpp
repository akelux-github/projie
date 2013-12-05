/*
 * palindrom_number.cpp
 *
 *  Created on: Dec 5, 2013
 *      Author: Rong Xiao
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stack;

bool isPalindromAux(int x, int& y) {  // y is the number; x is the least digit
    if (x==0) {
        return true;
    }

    if (isPalindromAux(x/10, y)  && (x % 10) == (y % 10) ) {
        y /= 10;
        cout << "Before return: "<< x << ", " << y << endl;
        return true;
    } else {
        return false;
    }
}

bool isPalin(int *x, int y) {
    /*
    stack<int, vector<int>> s;
    bool back_trace = false;
    while (!s.empty() or !back_trace ) {
        if (back_trace) {
            y = s.top();
            s.pop();
            // cout << "Popping: " << y << endl;
            // cout << "x: " << (*x) << endl;
            if (y%10 == (*x) % 10) {
                (*x) /=10;
            } else {
                return false;
            }
        } else {
            if (y!=0) {
                s.push(y);
                // cout << "Pushing: " << y << endl;
                y /= 10;
            } else {
                back_trace = true;
            }
        }
    }
     */
    if(y==0) {
        return true;
    }

    if(!isPalin(x,y/10) || !( (*x)%10== (y%10)  )) {
        // cout << (*x) << ", " << y << endl;
        return false;
    }
    // cout << (*x) << ", " << y << endl;
    // cout << (*x)%10 << " == " << (y%10) << endl;
    *x= (*x)/10;
    return true;
}

bool isPalindrom(int x) {
    if (x<0) {
        return false;
    }
    // return isPalindromAux(x,x);
    return isPalin(&x, x);
}

int main(int argc, char** args) {
    int n = atoi(args[1]);
    /*
    const char* judge = isPalindrom(n) ? " " : " not ";
    cout << n << " is" << judge << "a palindrom number.\n";
    cout << "Test: " << isPalindrom(10) << endl;
    cout << "Test: " << isPalindrom(11) << endl;

     */
    for (int i = 0; i < n ; ++i) {
        isPalindrom(i);
    }
    return 0;
}
