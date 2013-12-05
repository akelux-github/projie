/*
 * obj_scoped.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: rong
 */


#include <iostream>

using namespace std;
using std::cout;
using std::endl;

class Test {
public:
  void print(int i) {
    cout << i << endl;
  }
  ~Test() {
    cout << "dtor" << endl;
  }
};

int main(int argc, char** args) {
  for (auto i = 0; i<10; i++) {
    Test t;     // t get a fresh copy in each iteration
    int s{0};   // s got a fresh copy for each loop
    s+=i;
    t.print(s);
  }
  return 0;
}

