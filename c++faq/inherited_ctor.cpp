/*
 * inherited_ctor.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: rong
 */

#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

class Base {
  string _first{"Rong"};
public:
  Base() = default;
  Base(const string& n) : _first(n) {}
  void print() {
    cout << _first;
  }
};

class Derived : public Base {
  string _last{"Xiao"};
public:
  using Base::Base; // not including the default ones
  Derived() = default;
  Derived(const string& first, const string& last) : Base(first), _last(last) {}
  void print() {
    Base::print();
    cout << ' ' << _last;
  }
};

int main(void) {
  Base b;
  b.print();
  cout << endl;
  Base b1("Sichun");
  b1.print();
  cout << endl;

  Derived d;
  d.print();
  cout << endl;
  Derived d2("Nianzheng");
  d2.print();
  cout << endl;

  Derived d3("Weiwei", "Sun");
  d3.print();
  cout << endl;

  return 0;
}




