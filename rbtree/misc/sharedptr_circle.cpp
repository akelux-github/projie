/*
 * sharedptr_circle.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: rong
 */

#include <memory>
#include <iostream>
using std::cout;
using std::endl;
using std::shared_ptr;

class SharedPointerCircleDemo {
private:
  shared_ptr<SharedPointerCircleDemo> _holding{};
public:
  ~SharedPointerCircleDemo() {
    cout << "dtor" << endl;
  }
  void set_holding(const shared_ptr<SharedPointerCircleDemo>& holding) {
    _holding = holding;
  }
};

int main() {
  shared_ptr<SharedPointerCircleDemo> sp1{ new SharedPointerCircleDemo};
  shared_ptr<SharedPointerCircleDemo> sp2{ new SharedPointerCircleDemo};
  sp1->set_holding(sp2);
  // sp2->set_holding(sp1);
  return 0;
}





