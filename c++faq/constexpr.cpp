/*
 * constexpr.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: rong
 */
#include "vebtree.hpp"

#include <string>
#include <iostream>
#include <vector>
using std::string;
using std::cout;
using std::endl;
using std::vector;

int main(void) {
  // const key_type k = intSqrt(24);
  int arr[intSqrt(24)];

  for (auto x : arr) {
    cout << ' ' << x;
  }
  cout << endl;

  vector<int> v(intSqrt(24));
  for (auto x : v) {
    cout << ' ' << x;
  }
  cout << endl;

  return 0;
}



