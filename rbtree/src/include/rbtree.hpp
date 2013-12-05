/*
 * rbtree.hpp
 *
 *  Created on: Nov 28, 2013
 *      Author: rong
 */

#ifndef RBTREE_HPP_
#define RBTREE_HPP_
#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <memory>
using std::cout;
using std::endl;
using std::queue;
using std::unique_ptr;

template <class T> struct _RBTreeNode {

  /*
   * data members
   */
  T _data{};
  _RBTreeNode<T>* _parent{nullptr};
  _RBTreeNode<T>* _left{nullptr};
  _RBTreeNode<T>* _right{nullptr};
  bool _red{false};  // false means black
  // static _RBTreeNode<T> NullNode;

  /*
   * ctor
   */
  _RBTreeNode() = default; // member are default initialized by member initializers
  _RBTreeNode( const _RBTreeNode<T>& ) = delete;
  _RBTreeNode(const T& d, _RBTreeNode<T>* p, _RBTreeNode<T>* l, _RBTreeNode<T>* r, bool red = false)
  : _data(d), _parent(p), _left(l), _right(r), _red(red) {}

  static _RBTreeNode<T>* new_null() {
    return new _RBTreeNode<T>;
  }

  _RBTreeNode<T>* left_rotate() {
    auto parent = _parent;
    bool is_left = true;
    if (_parent!=nullptr) {
      is_left = this->is_left();
    }
    auto root = this->_right;
    root->_parent = this->_parent;
    this->_right = root->_left;
    root->_left->_parent = this;
    root->_left = this;
    this->_parent = root;

    if (parent!=nullptr) {
      if (is_left){
        parent->_left = root;
      } else {
        parent->_right = root;
      }
    }
    return root;
  }

  /*
   * Utility member functions: rotate, search
   */
  _RBTreeNode<T>* right_rotate() { // becomes right node of its left child
    auto parent = _parent;
    bool is_left = true;
    if (_parent!=nullptr) {
      is_left = this->is_left();
    }
    auto root = this->_left;
    root->_parent = this->_parent;
    this->_left = root->_right;
    root->_right->_parent = this;
    root->_right = this;
    this->_parent = root;

    if (parent!=nullptr) {
      if (is_left){
        parent->_left = root;
      } else {
        parent->_right = root;
      }
    }
    return root;
  }

  bool is_null() const {
    return (_left==nullptr); // or return _right==nullptr;
  }

  bool is_red() const {
    return _red;
  }

  bool is_black() const {
    return not _red;
  }

  void set_black() {
    _red = false;
  }

  void set_red() {
    _red = true;
  }

  void set_color(bool c) {
    _red = c;
  }

  void set_parent(_RBTreeNode<T>* parent) {
    _parent = parent;
  }

  bool is_left() {
    return _parent->_left == this;
  }

  _RBTreeNode<T>* get_uncle() {  // assume exists
    auto gparent = _parent->_parent;
    if (_parent->is_left()) {
      return gparent->_right;
    } else {
      return gparent->_left;
    }
  }

  _RBTreeNode<T>* get_sibling() {  // assume exists
    if (is_left()) {
      return _parent->_right;
    } else {
      return _parent->_left;
    }
  }

  _RBTreeNode<T>* search(const T& data) {
    auto res = this;
    while (!res->is_null()) {
      if (res->_data == data) {
        break;
      } else if (res->_data > data) {
        res = res->_left;
      } else {
        res = res->_right;
      }
    }
    return res;
  }

  void print(
      unsigned width=2,
      unsigned max_width = 64,
      unsigned max_height = 8,
      const _RBTreeNode<T>* mark_node = nullptr ) const;

  const _RBTreeNode* left() const {
    return _left;
  }

  const _RBTreeNode* right() const {
    return _right;
  }
};


template <class T> class RedBlackTree {
  _RBTreeNode<T>* _root;
  void delete_fixup(_RBTreeNode<T>* node);
  void insert_fixup(_RBTreeNode<T>* node);
  struct RBNodeCheckStatus {
    bool is_redblack;
    union {
      _RBTreeNode<T>* failnode;
      unsigned black_depth;
    } info;
  };
public:
  typedef _RBTreeNode<T> Node;
  RedBlackTree(_RBTreeNode<T>* root = _RBTreeNode<T>::new_null()) : _root(root) { }
  const Node* root() const {
    return _root;
  }

  static RBNodeCheckStatus compute_blackness(_RBTreeNode<T>* root) {
    RBNodeCheckStatus s;
    s.is_redblack = false;
    s.info.failnode = root;
    if (root == nullptr) {  // corner case of passing nullptr in
      return s;
    }

    if (root->is_null()) {
      if (root->_red) {
        return s;
      } else {
        s.is_redblack = true;
        s.info.black_depth = 1;
        return s;
      }
    } else if (root->_left==nullptr or  root->_right==nullptr) {
      return s;
    }

    if (root->_red) {
      if (root->_left->_red || root->_right->_red) {
        return s;
      }
    }

    auto l = compute_blackness(root->_left);
    if (!l.is_redblack) {
      return l;
    }

    auto r = compute_blackness(root->_right);
    if (!r.is_redblack) {
      return r;
    }

    if (l.info.black_depth==r.info.black_depth) {
      if (root->_red) {
        return l;
      } else {
        ++l.info.black_depth;
        return l;
      }
    } else {
      return s;
    }
  }

  ~RedBlackTree() {
    queue<_RBTreeNode<T>*> q;
    q.push(_root);  // _root is always not null
    while (!q.empty()) {
      auto node = q.front();
      q.pop();
      if (!node->is_null()) {
        q.push(node->_left);
        q.push(node->_right);
      }
      delete node;
    }
  }

  _RBTreeNode<T>* search(const T& data) {
    return _root->search(data);
  }

  void insert(const T& data);

  bool remove(const T& data);

  void print(unsigned width=2, unsigned max_width = 64, unsigned max_height = 8, const _RBTreeNode<T>* mark_node = nullptr ) {
    _root->print(width, max_width, max_height, mark_node);
  }
};

#include "rbtree-impl.hpp"

#endif /* RBTREE_HPP_ */
