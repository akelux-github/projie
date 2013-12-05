/*
 * rbtree.cpp
 *
 *  Created on: 2013-11-27
 *      Author: Rong Xiao
 */
/*
 * printrbtree.cpp
 *
 *  Created on: 2013-11-26
 *      Author: Rong Xiao
 */

#include "redblacktree.hpp"
#include <iostream>

using std::cout;
using std::endl;

// extern template class RedBlackTree<int>; // extern template

int main(int argc, char** args) {
    RedBlackTree<int> rbtree;
    rbtree.insert(1);
    rbtree.insert(2);
    rbtree.insert(3);
    rbtree.insert(4);
    rbtree.insert(-3);
    rbtree.insert(-3);
    rbtree.insert(-2);
    rbtree.insert(-5);
    rbtree.insert(2);

    rbtree.print();

    cout << "Removing 4: " << endl;
    rbtree.remove(4);
    rbtree.print();

    cout << "Inserting 3: " << endl;
    rbtree.insert(3);
    rbtree.print();


    cout << "Removing 5: " << endl;
    rbtree.remove(5);
    rbtree.print();

    cout << "Inserting -3: " << endl;
    rbtree.insert(-3);
    rbtree.print();


    cout << "Removing 3: " <<  endl;
    rbtree.remove(3);
    rbtree.print();

    cout << "Inserting 3: " << endl;
    rbtree.insert(3);
    rbtree.print();

    cout << "Removing 3: " <<endl;
    rbtree.remove(3);
    rbtree.print();

    cout << "Inserting 3: " << endl;
    rbtree.insert(3);
    rbtree.print();

    cout << "Removing -3: " << endl;
    rbtree.remove(-3);
    rbtree.print();
   
    cout << "Inserting 3: " << endl;
    rbtree.insert(3);
    rbtree.print();

    cout << "Inserting 3: " << endl;
    rbtree.insert(3);
    rbtree.print();


    cout << "Removing -3: " << endl;
    rbtree.remove(-3);
    rbtree.print();

    cout << "Inserting -3: " << endl;
    rbtree.insert(-3);
    rbtree.print();

   
    cout << "Removing -2: " << endl;
    rbtree.remove(-2);
    rbtree.print();
    cout << "Removing 1: " << endl;
    rbtree.remove(1);
    rbtree.print();
    cout << "Removing 3: " << endl;
    rbtree.remove(3);
    rbtree.print();
    cout << "Removing 3: " << endl;
    rbtree.remove(3);
    rbtree.print();
    cout << "Removing 3: " << endl;
    rbtree.remove(3);
    rbtree.print();
     cout << "Removing -5: " << endl;
    rbtree.remove(-5);
    rbtree.print();
     cout << "Removing 3: " << endl;
    rbtree.remove(3);
    rbtree.print();
    cout << "Removing -3: " << endl;
    rbtree.remove(-3);
    rbtree.print();
    cout << "Removing -3: " << endl;
    rbtree.remove(-3);
    rbtree.print();
    cout << "Removing 2: " << endl;
    rbtree.remove(2);
     cout << "Removing 2: " << endl;
    rbtree.remove(2);
    rbtree.print();
    return 0;
}




