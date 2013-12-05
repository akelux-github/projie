/*
 * redblacktree.cpp
 *
 *  Created on: 2013-11-27
 *      Author: Rong Xiao
 */
#include "redblacktree.hpp"

template <class T> struct _RBTreeNode;
template <class T> class RedBlackTree;

template <class T> _RBTreeNode<T> _RBTreeNode<T>::NullNode{T{}, nullptr, nullptr};

template <class T> RedBlackTree<T>::~RedBlackTree(){
    queue<_RBTreeNode<T>*> q;
    if (!_root->is_null()) {
        q.push(_root);
    }
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        if (!node->is_null()) {
            if (!node->_left->is_null()) {
                q.push(node->_left);
            }
            if (!node->_right->is_null()) {
                q.push(node->_right);
            }
            delete node;
        }
    }
}



