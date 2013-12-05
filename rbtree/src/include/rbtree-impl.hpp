/*
 * rbtree-impl.hpp
 *
 *  Created on: Nov 28, 2013
 *      Author: rong
 */

#ifndef RBTREE_IMPL_HPP_
#define RBTREE_IMPL_HPP_

#include "rbtree.hpp"

template <class T> void _RBTreeNode<T>::print(
    unsigned width,
    unsigned max_width,
    unsigned max_height,
    const _RBTreeNode<T>* mark_node
) const {
  // change width to a even number
  if (width % 2 != 0 ) {
    ++width;
  }

  unique_ptr<char[]> nullstrptr{new char[width+1]};
  auto ptr = nullstrptr.get();
  *(ptr+width) = '\0';
  for (unsigned i = 0; i< width; ++i) {
    *(ptr+i) = '*';
  }

  unsigned padx = 2;

  unsigned max_span = 1;
  unsigned height=0;
  while (max_span<max_width and height<max_height) {
    ++height;
    max_span<<=1;
  }

  max_width = max_span;

  unsigned nn_nodes = 2;

  unique_ptr<_RBTreeNode<T>> separator{new _RBTreeNode<T>{T{}, nullptr, nullptr, nullptr}};
  queue<const _RBTreeNode<T>*> to_print;
  to_print.push(this);
  to_print.push(separator.get());
  unsigned h = 0;
  bool first = true;
  padx = max_width/nn_nodes - width/2-1;
  cout << std::setw(width);
  while (!to_print.empty() and h<height) {
    auto node = to_print.front();
    to_print.pop();
    if (node == separator.get()) {
      to_print.push(separator.get());
      cout << endl;
      ++h;
      nn_nodes<<=1;
      if (max_width/nn_nodes <= width/2) {
        // cout <<width/2 -  max_width/nn_nodes;
        return;
      }
      padx = max_width/nn_nodes - width/2-1;

      // *(interlevelstr+i_offset) = '\n';
      // cout << interlevelstrptr.get(); // including newline at the every end
      // cout << levelstrptr.get();
      first = true;
    } else {
      if (first) {
        for (unsigned i = 0; i < padx; ++i) {
          cout << ' ';
        }
        first = false;
      } else {
        for (unsigned i = 0; i < 2*padx; ++i) {
          cout << ' ';
        }

      }
      if (node!=nullptr) {

        if (!node->is_null()) {
          if (node->is_black()) {
            cout << '(';
          } else {
            cout << ' ';
          }
        }
        if (node->is_null()) {
          cout << ' ' << nullstrptr.get();
        } else {
          cout << node->_data;
        }
        if (node == mark_node) {
          cout << '<';
        } else if (!node->is_null()) {
          if (node->is_black()) {
            cout << ')';
          } else {
            cout << ' ';
          }
        } else {
          cout << ' ';
        }
        to_print.push(node->_left);
        to_print.push(node->_right);
      } else {

        // cout << padding << nullstrptr.get();
        // print initial x padding

        // print padding
        for (unsigned i = 0; i < width+2; ++i) {
          cout << ' ';
        }
        // adding fake childs
        to_print.push(nullptr);
        to_print.push(nullptr);
      }
    }
  }



}

template <class T> void RedBlackTree<T>::insert(const T& data) {
  auto node = _root->search(data);

  // search till NullNode
  while (!node->is_null()) {
    if (node->_data>=data) {
      node = node->_left;
    } else {
      node = node->_right;
    }
  }

  auto parent = node->_parent;
  auto null = _RBTreeNode<T>::new_null();
  auto new_node = new _RBTreeNode<T>(data, parent, null, node, true);  // true means red node
  null->_parent = new_node;
  node->_parent = new_node;

  if (parent == nullptr) {
    _root = new_node;
    _root->set_black();
    return;
  }

  if (node == parent->_left) {
    parent->_left = new_node;
  } else {
    parent->_right = new_node;
  }

  insert_fixup(new_node); // Invariant: current node is red; a tree rooted at it is red-black if changing its color to black
  auto status = compute_blackness(_root);
  if (!status.is_redblack) {
    cout << "Fail node after insert: " << data << endl;
    print(2,64,8,status.info.failnode);
    cout << endl;
    status.info.failnode->print(2,64,8);
    cout << "*******" << endl;
  }
}


template <class T> void RedBlackTree<T>::insert_fixup(_RBTreeNode<T>* node){
  _RBTreeNode<T>* parent = node->_parent;

  cout << "Current tree: " << endl;
  print(2, 64, 8, node);
  cout << "-------------------------" << endl;



  if (parent==nullptr) {
    cout << "Case 1" << endl;
    node ->set_black();
    _root = node;
    return;
  }


  if (parent->is_black()) {
    // Case 2
    cout << "Case 2" << endl;
    return;
  }

  bool is_left = node->is_left();
  _RBTreeNode<T>* gparent = parent->_parent;

  bool parent_left = parent->is_left();
  _RBTreeNode<T>* uncle = node->get_uncle();


  if (uncle->is_red()) {
    // Case 3
    uncle->set_black();
    parent->set_black();
    gparent->set_red();
    node = gparent;
    cout << "Case 3" << endl;
    print(2, 64);
  } else {
    if (is_left != parent_left) { // parent red; uncle black
      // Case 4: keep grand parent unchanged ==> Case 5
      if (parent_left) {
        parent->left_rotate();
      } else {
        parent->right_rotate();
      }
      node = parent;
      cout << "Case 4" << endl;
      print(2, 64);
    } else {
      // Case 5
      cout << "Case 5" << endl;
      gparent->set_red();
      parent->set_black();
      if (is_left) {
        gparent->right_rotate();
      } else {
        gparent->left_rotate();
      }

      if (_root == gparent) {
        _root = parent;
      }
      return;
    }
  }

  return insert_fixup(node);
}

template <class T> bool RedBlackTree<T>::remove(const T& data){
  auto node = _root->search(data);

  if (node->is_null()) {
    return false;
  }

  auto to_delete = node;
  // search for the largest left descandant or smallest right descandant of to_delete
  if (!node->_right->is_null()) {
    node = node->_right;
    while (!node->_left->is_null()) {
      node = node->_left;
    }
  } else if (!node->_left->is_null()) {
    node = node->_left;
    while (!node->_right->is_null()) {
      node = node->_right;
    }
  }

  cout << "Before remove: " << data ;
  cout << endl;
  print(2,64,8, node);
  cout << "#################################" << endl;
  to_delete->_data = std::move(node->_data);
  auto remain_child  = node->_right;
  if (remain_child->is_null()) {
    remain_child = node->_left;
    delete node->_right;
  } else {
    delete node->_left;
  }

  to_delete = node; // mark to_delete the actual node to be delete
  if (to_delete->_parent!=nullptr) {
    if (to_delete->is_left()) {
      to_delete->_parent->_left = remain_child;
    } else {
      to_delete->_parent->_right = remain_child;
    }
  }
  remain_child->_parent = to_delete->_parent;

  if (to_delete->is_red()) {
    // Nothing need to be done
    cout << "Case 1-A: red node being removed" << endl;

  } else if (remain_child->is_red()) {
    cout << "Case 1-B: remaining node is red" << endl;
    remain_child->set_black();
  } else {
    delete_fixup(remain_child);  // Invariant: node is black, all path pass it \
    has one less black node than the paths don't
  }

  delete to_delete;
  auto status = compute_blackness(_root);
  if (!status.is_redblack) {
    cout << "Fail node after delete: " << data << endl;
    print(2,64,8,status.info.failnode);
    cout << endl;
    status.info.failnode->print(2,64,8);
    cout << "*******" << endl;
  }
  return true;
}


template <class T> void RedBlackTree<T>::delete_fixup(_RBTreeNode<T>* node) {
  cout << "Delete fixup tree:" << endl;
  print(2,64,8,node);
  cout << "------------------------" << endl;

  if (node->_parent == nullptr) {
    _root = node;
    return;
  }
  auto parent = node->_parent;
  decltype(parent) sibling = node->get_sibling();

  if (sibling->is_red()) {
    //Case 2
    // parent has to be black
    sibling->set_black();
    parent->set_red();

    if (node->is_left()) { // Check here!!!
      parent->left_rotate();
    } else {
      parent->right_rotate();
    }

    if (_root == parent) {
      _root = sibling;
    }

    cout << "Case 2" << endl;
    print(2,64,8,node);
  } else {
    // node has black sibling; sibling must not be a NullNode
    if (sibling->_left->is_black() and sibling->_right->is_black()) {

      auto parent_was_red = parent->is_red();
      sibling->set_red();
      parent->set_black();

      if (parent_was_red) {
        cout << "Case 4" << endl;
        return;
      }

      // Case 3 - 4
      cout << "Case 3" << endl;
      print(2,64,8,node);
      node = parent;
    } else if (node->is_left() and sibling->_right->is_black()) { // sibling->_left->is_red()
      // Case 5-L:
      sibling->set_red();
      sibling->_left->set_black();
      sibling->right_rotate();
      cout << "Case 5-L" << endl;
      print(2,64,8,node);

    } else if (!node->is_left() and sibling->_left->is_black()) { // sibling->_right->is_red()
      // Case 5-R:
      sibling->set_red();
      sibling->_right->set_black();
      sibling->left_rotate();
      cout << "Case 5-R" << endl;
      print(2,64,8,node);
    } else {
      // Case 6:
      // exchanging color of S and P; paint S's corresponding red child to be black; and stop
      if (parent->is_black()) {
        sibling->set_black();
      } else {
        sibling->set_red();
      }

      parent->set_black();

      if (node->is_left()) {
        sibling->_right->set_black();
        parent->left_rotate();
      } else {
        sibling->_left->set_black();
        parent->right_rotate();
      }

      cout << "Case 6" << endl;
      if (_root == parent) {
        _root = sibling;
      }
      return ;
    }
  }

  // Case 1
  return delete_fixup(node);
}


#endif /* RBTREE_IMPL_HPP_ */
