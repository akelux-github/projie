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

int main(int argc, char** args) {
    RedBlackTree<int> rbtree;
    rbtree.insert(1);
    rbtree.insert(2);
    rbtree.insert(3);
    rbtree.insert(4);
    rbtree.print(unsigned(atoi(args[1])), unsigned(atoi(args[2])));

    _RBTreeNode<int> root{1, nullptr, nullptr};
    root._right = new  _RBTreeNode<int>(1, &_RBTreeNode<int>::NullNode, nullptr);
    root._left =  new  _RBTreeNode<int>(-100, nullptr, &_RBTreeNode<int>::NullNode);
    root._left->_left =  new  _RBTreeNode<int>(-2, &_RBTreeNode<int>::NullNode, &_RBTreeNode<int>::NullNode);
    root._right->_right = new  _RBTreeNode<int>(200, &_RBTreeNode<int>::NullNode, &_RBTreeNode<int>::NullNode);
    root.print(unsigned(atoi(args[1])), unsigned(atoi(args[2])));
    return 0;
}

