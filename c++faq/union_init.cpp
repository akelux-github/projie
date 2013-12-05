/*
 * union_init.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: rong
 */

#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

union FloatQudruple {
  float x,y,z,w;
  float arr[4];
};

union FloatQudruple2 {
  float arr[4];
  float x,y,z,w;
};

int main(void) {
  FloatQudruple q{1.0};// ,2.0,3.0, 4.0};  // by default, initialize only the first variant
  cout << q.x <<endl;
  cout << q.y <<endl;
  for (auto i = 0; i<4; ++i) {
    cout << ' ' << q.arr[i];
  }

  q.arr[0] = 2.0;
  q.arr[1] = 3.0;

  cout << q.x <<endl;
  cout << q.y <<endl;
  for (auto i = 0; i<4; ++i) {
    cout << ' ' << q.arr[i];
  }
  cout << endl;

  FloatQudruple2 q2={{1.0,2.0,3.0,4.0}};  // warning if NO outter braces.
  cout << q2.x <<endl;
  cout << q2.y <<endl;
  for (auto i = 0; i<4; ++i) {
    cout << ' ' << q2.arr[i];
  }
  cout << endl;

  return 0;
}
