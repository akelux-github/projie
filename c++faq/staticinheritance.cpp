/*
 * staticinheritance.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: rong
 */
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

struct BaseCore {
  static string name() {
      return string{"Base"};
    }
};

struct BaseRong {
  static string name() {
      return string{"Rong"};
    }
};

template <class Core = BaseCore> struct DerivedCore : public Core {
  using Core::name;
  static void call() {
    cout << name() << endl;
  }
};

class DerivedCore : public BaseCore  {
  using BaseCore::name;

  static void call() {
    cout << name() << endl;
  }

};


struct Base {
  static Base global_instance;
virtual string name() {
    return string{"Base"};
  }

  virtual void call() {
      cout << name() << endl;
    }
};


struct Derived : public Base {
  static Derived global_instance;
  virtual string name() {
    return string{"Derived"};
  }

  /*
  static void call() {
      cout << name() << endl;
    }
    */
  using Base::call;
};

Base Base::global_instance;
Derived Derived::global_instance;

int main() {

  Base b;
  b.call();
  Derived d;
  d.call();
  Base::global_instance.call();
  Derived::global_instance.call();


  DerivedCore<>::call();
  DerivedCore<BaseCore>::call();
  DerivedCore<BaseRong>::call();

  return 0;
}


