/*
 * redblacktree.hpp
 *
 *  Created on: 2013-11-25
 *      Author: Rong Xiao
 */

#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_
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
    typedef std::pair<_RBTreeNode<T>*, bool> ParentInfo;

    /*
     * data members
     */
    static _RBTreeNode<T> NullNode;
    _RBTreeNode<T>* _left;
    _RBTreeNode<T>* _right;
    T _data;
    bool _red;

    /*
     * ctor
     */
    // _RBTreeNode() = default; // member are default initialized by member initializers
    // _RBTreeNode( const _RBTreeNode<T>& ) = default;
    // _RBTreeNode<T>& operator=( const _RBTreeNode<T>& ) = default;
    _RBTreeNode(const T& d, _RBTreeNode<T>* l, _RBTreeNode<T>* r, bool c = false)
            : _data(d), _left(l), _right(r), _red(c) {}

    _RBTreeNode<T>* left_rotate() {
        auto root = this->_right;
        this->_right = root->_left;
        root->_left = this;
        return root;
    }

    /*
     * Utility member functions: rotate, search
     */
    _RBTreeNode<T>* right_rotate() { // becomes right node of its left child
        auto root = this->_left;
        this->_left = root->_right;
        root->_right = this;
        return root;
    }

    inline bool is_null() const {
        return this == &NullNode;
    }

    inline bool is_red() const {
        return _red;
    }

    inline bool is_black() const {
        return not _red;
    }

    inline void set_black() {
        _red = false;
    }

    inline void set_red() {
        _red = true;
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

    _RBTreeNode<T>* search(const T& data, std::vector<ParentInfo>& parents ) {
        auto res = this;
        parents.clear();
        while (!res->is_null()) {
            if (res->_data == data) {
                break;
            } else if (res->_data > data) {
                parents.push_back(ParentInfo(res, true));
                res = res->_left;
            } else {
                parents.push_back(ParentInfo(res, false));
                res = res->_right;
            }
        }
        return res;
    }

    void print(unsigned width, unsigned max_width = 80, unsigned max_height = 8, const _RBTreeNode<T>* mark_node = nullptr ) const {
        // change width to a even number
        if (width % 2 != 0 ) {
            ++width;
        }

        /*
        constexpr const char* padding = "  ";
        unique_ptr<char[]> levelstrptr{new char[max_width]};
        auto levelstr = levelstrptr.get();
        for (unsigned i = 0; i< max_width; ++i) {
            *(levelstr+i) = '\0';
        }
        unique_ptr<char[]> interlevelstrptr{new char[max_width]};
        auto interlevelstr = interlevelstrptr.get();
        for (unsigned i = 0; i< max_width; ++i) {
            *(interlevelstr+i) = '\0';
        }


         */

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

        decltype(this->_left) separator = new _RBTreeNode<T>(T{}, nullptr, nullptr);
        queue<const _RBTreeNode<T>*> to_print;
        to_print.push(this);
        to_print.push(separator);
        unsigned h = 0;
        bool first = true;
        padx = max_width/nn_nodes - width/2;
        cout << std::setw(width);
        while (!to_print.empty() and h<height) {
            auto node = to_print.front();
            to_print.pop();
            if (node == separator) {
                to_print.push(separator);
                cout << endl;
                ++h;
                nn_nodes<<=1;
                if (max_width/nn_nodes <= width/2) {
                    // cout <<width/2 -  max_width/nn_nodes;
                    return;
                }
                padx = max_width/nn_nodes - width/2;

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

                    if (node->is_null()) {
                        cout << nullstrptr.get();
                    } else {
                        cout << node->_data;
                    }
                    to_print.push(node->_left);
                    to_print.push(node->_right);
                } else {

                    // cout << padding << nullstrptr.get();
                    // print initial x padding

                    // print padding
                    for (unsigned i = 0; i < width; ++i) {
                        cout << ' ';
                    }
                    // adding fake childs
                    to_print.push(nullptr);
                    to_print.push(nullptr);
                }
            }
        }



    }
};


template <class T> _RBTreeNode<T> _RBTreeNode<T>::NullNode{T{}, nullptr, nullptr};


template <class T> class RedBlackTree {
    typedef typename _RBTreeNode<T>::ParentInfo ParentInfo;
    _RBTreeNode<T>* _root{&_RBTreeNode<T>::NullNode};
public:
    inline _RBTreeNode<T>* search(const T& data) {
        return _root->search(data);
    }

    void insert(const T& data) {
        std::vector<ParentInfo> parents;
        auto node = _root->search(data, parents);

        // search till NullNode
        while (!node->is_null()) {
            if (node->_data>=data) {
                parents.push_back(ParentInfo(node, true));
                node = node->_left;
            } else {
                parents.push_back(ParentInfo(node, false));
                node = node->_right;
            }
        }

        node = new _RBTreeNode<T>(data, node, node); // node points NullNode before assignment
        if /* (parents.empty()) {
            // Case 1
            node->set_black();
            _root = node;
            return;
        } else */

        (!parents.empty()) {
            auto p = parents.back();
            if (p.second) {
                p.first->_left = node;
            } else {
                p.first->_right = node;
            }

            /*
            // Case 2
            if (p.first->is_black()) {
                return;
            }
            */

            // rebalancing the tree for Case 3-6

        }
        _root = insert_fixup(node, parents); // Invariant: current node is red; a tree rooted at it is red-black if changing its color to black

    }

    bool del(const T& data) {
        std::vector<ParentInfo> parents;
        auto node = _root->search(data, parents);

        if (node->is_null()) {
            return false;
        }

        auto to_delete = node;
        // search for the largest left descandant or smallest right descandant of to_delete
        if (node->_left->is_null()) {
            parents.push_back(ParentInfo(node, false));
            node = node->_right;
            while (!node->_left->is_null()) {
                parents.push_back(ParentInfo(node, true));
                node = node->_left;
            }
        } else {
            parents.push_back(ParentInfo(node, true));
            node = node->_left;
            while (!node->_right->is_null()) {
                parents.push_back(ParentInfo(node, false));
                node = node->_right;
            }
        }

        if (node == to_delete) {

        } else {
            to_delete->_data = std::move(node->data);
        }


        return true;
    }

    inline void print(unsigned width, unsigned max_width = 80, unsigned max_height = 8, const _RBTreeNode<T>* mark_node = nullptr ) {
        _root->print(width, max_width, max_height, mark_node);
    }

private:
    void delete_node(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents);
    auto insert_fixup(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents) -> decltype(node);
};

template <class T> auto RedBlackTree<T>::insert_fixup(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents)-> decltype(node) {
    while (!parents.empty()) {
        auto p = parents.back();
        parents.pop_back();
        _RBTreeNode<T>* parent = p.first;
        if (parent->is_black()) {
            // Case 2
            return parents.front().first;
        }

        bool is_left = p.second;
        auto gp = parents.back();
        _RBTreeNode<T>* gparent = p.first;
        bool parent_left = gp.second;
        _RBTreeNode<T>* uncle = nullptr;
        if (parent_left) {
            uncle = gparent->_right;
        } else {
            uncle = gparent->_left;
        }

        if (uncle->is_red()) {
            // Case 3
            uncle->set_black();
            parent->set_black();
            gparent->set_red();
            parents.pop_back();
            node = gparent;
        } else {

            if (is_left != parent_left) {
                // Case 4: keep grand parent unchanged ==> Case 5
                node = parent;
                if (parent_left) {
                    gparent->_left = node->left_rotate();
                    parents.push_back(ParentInfo(gparent->_left, true));
                } else {
                    gparent->_right = node->right_rotate();
                    parents.push_back(ParentInfo(gparent->_right, false));
                }
            } else {
                // Case 5
                parents.pop_back(); // pop grand parent out
                gparent->set_red();
                parent->set_black();
                if (is_left) {
                    gparent->right_rotate();
                } else {
                    gparent->left_rotate();
                }

                if (parents.empty()) {
                    return parent;
                } else {
                    auto gpp = parents.back();
                    if (gpp.second) {
                        gpp.first->_left = uncle;
                    } else {
                        gpp.first->_right = uncle;
                    }
                    parents.push_back(p);
                }
            }
        }
    }
    node ->set_black();
    return node;
}

#endif /* REDBLACKTREE_HPP_ */
