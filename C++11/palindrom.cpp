/*
 * palindrom.cpp
 *
 *  Created on: Dec 5, 2013
 *      Author: Rong Xiao
 */

#include <vector>
#include <iostream>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
pair<size_t, size_t> longestPalindrom(const string& s) {
    size_t len = s.size();
    vector<size_t> palindroms(2*len-1);
    palindroms[0]=1;
    size_t center = 0;
    size_t right_bound = 0;
    // bool center_anchored = true;
    size_t left_checking = 0;
    size_t right_checking = 1;
    if (s.at(left_checking) == s.at(right_checking)) {
        palindroms[1]=2;
        center = 1;
        right_bound = 1;
    } else {
        palindroms[1]=0;
    }

    for (size_t i = 2; i<2*len-1; ++i) {
        /*
        if (i>2*center) {
            //
            cout <<"Wired: " << center << ", " << i << endl;
            if (i % 2 == 0) {
                palindroms[i] = 1;
                left_checking = i/2;
                right_checking = i/2;
            } else {
                palindroms[i] = 0;
                left_checking = (i+1)/2;
                right_checking = (i-1)/2;
            }
        } else {
         */
        size_t i_mirror = 2*center - i;
        palindroms[i] = palindroms[i_mirror];
        if ((i+palindroms[i]+1)/2<right_bound) {
            cout << left_checking << ", (" << i << "," << right_bound << "," << palindroms[i] << "), " << right_checking << endl;
            continue;  //
        } else {
            left_checking =  (i-palindroms[i]+1)/2;
            right_checking = (i+palindroms[i]-1)/2;
        }

        cout << left_checking << ", (" << i << "," << palindroms[i] << "), " << right_checking << endl;

        while (left_checking>0 and right_checking<len-1) {
            --left_checking;
            ++right_checking;
            if (s.at(left_checking) == s.at(right_checking)) {
                palindroms[i]+=2;
                cout << left_checking << ", (" << i << "," << palindroms[i] << "), " << right_checking << endl;
            } else {
                break;
            }


            /*
        if (palindroms[i]>palindroms[center]) {
            center = i;
            right_bound = right_checking;
        }
             */

            if (right_checking>right_bound) {  // shift the center
                center = i;
                right_bound = right_checking;
            }
        }
    }

    center = 0;
    for (size_t i = 1; i<2*len-1; ++i) {
        if (palindroms[i]>palindroms[center]) {
            center = i;
        }
    }
    return pair<size_t, size_t>(center, palindroms[center]);
}


int main(int argc, char** args) {
    auto max_palindrom = longestPalindrom(args[1]);
    auto start = max_palindrom.first;
    if (start % 2 == 0) {
        cout << "Centered at " << start/2;
    } else {
        cout << "Centered between " << (start-1)/2 << " and " << (start+1)/2;
    }
    cout << " with length "<< max_palindrom.second;

    return 0;
}

