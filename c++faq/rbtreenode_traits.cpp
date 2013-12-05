/*
 * rbtreenode_traits.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: rong
 */

template <class Node> struct RedBlackNodeTraitsCore {
  static Node* get_null_node() {
    return nullptr;  // return new Node;
  }

  static Node* left_child(Node* n) {
    return n->_left;
  }

  static Node* right_child(Node* n) {
    return n->_right;
  }

  static Node* parent(Node* n) {
    return n->_parent;
  }

  static bool is_black(Node* n) {
    return n->_black;
  }

  static void set_black(Node* n) {
    n->_black = true;
  }

  static void set_red(Node* n) {
    n->_black = false;
  }

  static void set_parent(Node* n, Node* p) {
    n->_parent = p;
  }

  static void set_left(Node* n, Node* l, bool set_parent = true) {
    n->_left = l;
    if (set_parent) {
      set_parent(l,n);
    }
  }

  static void set_right(Node* n, Node* r, bool set_parent = true) {
    n->_right = r;
    if (set_parent) {
      set_parent(r,n);
    }
  }

  static bool is_null(Node* n) {
    return n == nullptr;
  }
};

template <class Node, class Core = RedBlackNodeTraitsCore<Node> > struct RedBlackNodeTraits : public Core {
  typedef Node NodeType;

  /*
   * Make static funtion in Core available here
   */
  using Core::is_black;
  using Core::get_null_node;
  using Core::left_child;
  using Core::right_child;
  using Core::set_left;
  using Core::set_right;
  using Core::set_parent;
  using Core::set_black;
  using Core::is_null;
  using Core::parent;

  /*
     Non primary traits
   */
  static bool is_red(Node* n) {
    return !is_black(n);
  }

  static bool is_left(Node* n) {
    return left_child(parent(n)) == n;
  }

  static Node* sibling(Node* n) {
    if (is_left(n)) {
      return right_child(parent(n));
    } else {
      return left_child(parent(n));
    }
  }

  static Node* uncle(Node* n) {
    return sibling(parent(n));
  }

  static Node* left_rotate(Node* n, bool set_parent = true) {
    auto p = parent(n);
    bool was_left = false;
    if (set_parent and parent!=nullptr) {
      was_left = is_left(n);
    }

    auto right = right_child(n);
    auto leftchild_right = left_child(right);
    set_left(right, n, set_parent);
    set_right(n, leftchild_right, set_parent);
    set_parent(right, p);
    if (set_parent and p) {
      if (was_left) {
        set_left(p, right);
      } else {
        set_right(p, right);
      }
    }
    return right;
  }

  static Node* right_rotate(Node* n, bool set_parent = true) {
    auto p = nullptr;
    bool was_left = false;
    if (set_parent ) {
      p =  parent(n);
      if (p!=nullptr) {
        was_left = is_left(n);
      }
    }

    auto left = left_child(n);
    auto rightchild_left = right_child(left);
    set_right(left, n, set_parent);
    set_left(n, rightchild_left, set_parent);

    if (set_parent) {
      set_parent(left, p);
    }

    if (set_parent and p!=nullptr) {
      if (was_left) {
        set_left(p, left);
      } else {
        set_right(p, left);
      }
    }
    return left;
  }

};

template <class T> struct RBNode {
  RBNode<T>* _left{nullptr};
  RBNode<T>* _right{nullptr};
  RBNode<T>* _parent{nullptr};
  bool _black{true};
  T _data{};
};

template <class T, class RBNodeTraits = RedBlackNodeTraits<RBNode<T> > > struct RBTree {
  typedef typename RBNodeTraits::NodeType Node;
  Node* _root;
  void delete_fixup(Node* node);
  void insert_fixup(Node* node);
public:
  RBTree(Node* root = RBNodeTraits::get_null_node()) : _root(root) { }

};
