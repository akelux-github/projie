//============================================================================
// Name        : rbtree.cpp
// Author      : Rong Xiao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "include/rbtree.hpp"

#include <iostream>
using namespace std;
using std::cout;
using std::endl;

// extern template class RedBlackTree<int>; // extern template

int main(int argc, char** args) {
  RedBlackTree<int> rbtree;
  rbtree.insert(1);
  rbtree.print();

  rbtree.insert(2);
  rbtree.print();

  rbtree.insert(3);
  rbtree.print();

  rbtree.insert(4);
  rbtree.print();

  rbtree.insert(-3);
  rbtree.print();

  rbtree.insert(-3);
  rbtree.print();

  rbtree.insert(-2);
  rbtree.print();

  rbtree.insert(-5);
  rbtree.print();

  rbtree.insert(2);
  rbtree.print();

  rbtree.print();

  cout << "Removing 4: " << endl;
  rbtree.remove(4);
  rbtree.print();
  rbtree.insert(-3);
  rbtree.insert(-3);
  rbtree.insert(-2);
  rbtree.insert(-5);
  rbtree.insert(2);
  cout << "Removing 1: " << endl;
  rbtree.remove(1);
  rbtree.print();
  rbtree.insert(1);
  rbtree.print();

  rbtree.insert(2);
  rbtree.print();

  rbtree.insert(3);
  rbtree.print();

  rbtree.insert(4);
  rbtree.print();
  cout << "Removing -3: " << endl;
  rbtree.remove(-3);
  rbtree.print();

  cout << "Removing 3: " << endl;
  rbtree.remove(3);
  rbtree.print();
  rbtree.insert(1);
  rbtree.print();
  rbtree.insert(-3);
  rbtree.insert(-3);
  rbtree.insert(-2);
  rbtree.insert(-5);
  rbtree.insert(2);
  rbtree.insert(2);
  rbtree.print();

  rbtree.insert(3);
  rbtree.print();

  rbtree.insert(4);
  rbtree.print();
  cout << "Inserting 3: " << endl;
  rbtree.insert(3);
  rbtree.print();

  cout << "Removing 3: " << endl;
  rbtree.remove(3);
  rbtree.print();

  cout << "Removing 2: " << endl;
  rbtree.remove(2);
  rbtree.print();
  rbtree.insert(1);
  rbtree.print();

  rbtree.insert(2);
  rbtree.print();

  rbtree.insert(3);
  rbtree.print();

  rbtree.insert(4);
  rbtree.print();
  cout << "Removing -5: " << endl;
  rbtree.remove(-5);
  rbtree.print();
  rbtree.insert(1);
  rbtree.print();

  rbtree.insert(2);
  rbtree.print();

  rbtree.insert(3);
  rbtree.print();
  cout << "Removing -3: " << endl;
  rbtree.remove(-3);
  rbtree.print();
  rbtree.insert(4);
  rbtree.print();
  cout << "Removing 4: " << endl;
  rbtree.remove(4);
  rbtree.print();

  rbtree.insert(-3);
  rbtree.insert(-3);
  rbtree.insert(-2);
  rbtree.insert(-5);
  rbtree.insert(2);

  cout << "Removing -5: " << endl;
  rbtree.remove(-5);
  rbtree.print();

  cout << "Removing -5: " << endl;
  rbtree.remove(-5);
  rbtree.print();

  rbtree.remove(2);
  rbtree.remove(2);
  rbtree.remove(2);
  rbtree.remove(2);
  rbtree.remove(2);
  rbtree.remove(2);

  rbtree.remove(3);
  rbtree.remove(3);
  rbtree.remove(3);
  rbtree.remove(3);
  rbtree.remove(3);
  rbtree.remove(3);

  rbtree.remove(4);
  rbtree.remove(4);
  rbtree.remove(4);
  rbtree.remove(4);
  rbtree.remove(4);
  rbtree.remove(4);

  rbtree.remove(1);
  rbtree.remove(1);
  rbtree.remove(1);
  rbtree.remove(1);
  rbtree.remove(1);
  rbtree.remove(1);

  rbtree.remove(2);
  rbtree.remove(2);
  rbtree.remove(2);
  rbtree.remove(2);

  rbtree.remove(-3);
  rbtree.remove(-3);
  rbtree.remove(-3);
  rbtree.remove(-3);

  rbtree.remove(-2);
  rbtree.remove(-2);
  rbtree.remove(-2);
  rbtree.remove(-2);

  rbtree.remove(-3);
  rbtree.remove(-3);

  rbtree.remove(-5);
  rbtree.remove(-5);
  rbtree.print();


  return 0;
}
