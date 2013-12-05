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
    T _data;
    _RBTreeNode<T>* _left;
    _RBTreeNode<T>* _right;
    bool _red;
    static _RBTreeNode<T> NullNode;

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

    inline void set_color(bool c) {
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

    void print(unsigned width=2, unsigned max_width = 64, unsigned max_height = 8, const _RBTreeNode<T>* mark_node = nullptr ) const {
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

        unique_ptr<_RBTreeNode<T>> separator{new _RBTreeNode<T>{T{}, nullptr, nullptr}};
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
                    /* if (node == mark_node) {
                        cout << '<';
                    } else 
                    */
                    if (!node->is_null()) {
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
};


template <class T> _RBTreeNode<T> _RBTreeNode<T>::NullNode{T{}, nullptr, nullptr};


template <class T> class RedBlackTree {
    typedef typename _RBTreeNode<T>::ParentInfo ParentInfo;
    _RBTreeNode<T>* _root;
    auto delete_fixup(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents) -> decltype(node);
    auto insert_fixup(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents) -> decltype(node);
    bool revise_parents(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents); // return is _root changed
public:
    RedBlackTree(_RBTreeNode<T>* root = &_RBTreeNode<T>::NullNode) : _root(root) { }
    ~RedBlackTree() {
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

        node = new _RBTreeNode<T>(data, node, node, true); // node points NullNode before assignment

        revise_parents(node, parents);
        // rebalancing the tree for Case 3-6
        _root = insert_fixup(node, parents); // Invariant: current node is red; a tree rooted at it is red-black if changing its color to black
        cout << "--------------Insert finished--------------------" << endl;
    }

    bool remove(const T& data) {
        cout << "Before remove: " << data << endl;
        print(2,64,8);
        std::vector<ParentInfo> parents;
        auto node = _root->search(data, parents);

        if (node->is_null()) {
            return false;
        }

        auto to_delete = node;
        // search for the largest left descandant or smallest right descandant of to_delete
        if (!node->_right->is_null()) {
            parents.push_back(ParentInfo(node, false));
            node = node->_right;
            while (!node->_left->is_null()) {
                parents.push_back(ParentInfo(node, true));
                node = node->_left;
            }
        } else if (!node->_left->is_null()) {
            parents.push_back(ParentInfo(node, true));
            node = node->_left;
            while (!node->_right->is_null()) {
                parents.push_back(ParentInfo(node, false));
                node = node->_right;
            }
        }

        to_delete->_data = std::move(node->_data);
        auto remain_child  = node->_right;
        if (remain_child->is_null()) {
            remain_child = node->_left;
        }

        to_delete = node; // mark to_delete the actual node to be delete

        revise_parents(remain_child, parents);

        if (to_delete->is_red()) {
            // Nothing need to be done
        } else if (remain_child->is_red()) {
            remain_child->set_black();
        } else {
            node = remain_child;
            _root = delete_fixup(node, parents); // Invariant: node is black, all path pass it has one less black node than the paths don't
        }


        delete to_delete;
        return true;
    }

    inline void print(unsigned width=2, unsigned max_width = 64, unsigned max_height = 8, const _RBTreeNode<T>* mark_node = nullptr ) {
        _root->print(width, max_width, max_height, mark_node);
    }
};

template <class T> bool RedBlackTree<T>::revise_parents(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents) {
    if (parents.empty()) {
        _root = node; // only for debug purpose
        return true;
    } else { // T.B.D.: reorganizing as an inline function call
        auto p = parents.back();
        if (p.second) {
            p.first->_left = node;
        } else {
            p.first->_right = node;
        }
        return false;
    }
}

template <class T> auto RedBlackTree<T>::insert_fixup(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents)-> decltype(node) {
    while (!parents.empty()) {
        cout << "Current tree: " << endl;
        print(2, 64);
        cout << "Current node: " << endl;
        node -> print(2, 64);

        auto p = parents.back();
        parents.pop_back();
        _RBTreeNode<T>* parent = p.first;
        if (parent->is_black()) {
            // Case 2
            cout << "Case 2" << endl;
            print(2, 64);
            return _root; //parents.front().first;
        }

        bool is_left = p.second;
        auto gp = parents.back();
        _RBTreeNode<T>* gparent = gp.first;
        if (parent == gparent) {
            cout << "Wild 1" << endl;
        }
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
            parents.pop_back(); // pop grand parent out
            node = gparent;
            cout << "Case 3" << endl;
            print(2, 64);

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
                cout << "Case 4" << endl;
                print(2, 64);

            } else {
                // Case 5

                cout << "Case 5" << endl;

                parents.pop_back(); // pop grand parent out
                gparent->set_red();
                parent->set_black();

                if (is_left) {
                    gparent->right_rotate();
                } else {
                    gparent->left_rotate();
                }

                /*
                if (parents.empty()) {
                    cout << "Before return : " << endl;
                    print(2,64,8,node);
                    return parent;
                } else {
                    auto gpp = parents.back();
                    if (gpp.second) {
                        gpp.first->_left = parent;
                    } else {
                        gpp.first->_right = parent;
                    }
                }
                 */

                if (revise_parents(parent, parents)) {
                    return parent; // new root
                } else {
                    parents.push_back(p);
                }

                print(2,64,8,node);
            }
        }
    }
    cout << "Case 1" << endl;
    node ->set_black();
    return node;
}

template <class T> auto RedBlackTree<T>::delete_fixup(_RBTreeNode<T>* node, std::vector<ParentInfo>& parents)-> decltype(node) {
    while (!parents.empty()) { //Invariant: node is black; all paths pass node has one less black;
        cout << "delete fixup tree:" << endl;
        print(2,64,8,node);
        cout << "current node:" << endl;
        node->print(2,64,8,node);
        cout << "------------------------" << endl;
        auto p = parents.back();
        auto parent = p.first;
        decltype(parent) sibling = nullptr;
        if (p.second) {
            sibling = parent->_right;
        } else {
            sibling = parent->_left;
        }

        if (sibling->is_red()) {
            //Case 2
            // parent has to be black
            sibling->set_black();
            parent->set_red();
            parents.pop_back();

            revise_parents(sibling, parents);

            if (p.second) {
                parent->left_rotate();
                parents.push_back(ParentInfo(sibling, true));
            } else {
                parent->right_rotate();
                parents.push_back(ParentInfo(sibling, false));
            }

            cout << "Case 2" << endl;
            print(2,64,8,node);
            parents.push_back(p); // now becomes Case 3-6
        } else {
            // node has black sibling; sibling must not be a NullNode
            /*
            if (sibling->is_null()) {
                cout << "The tree was not red-black tree!" << endl;
                return _root;
            }
            */
            if (sibling->_left->is_black() and sibling->_right->is_black()) {
                // Case 3 - 4
                sibling->set_red();
                auto parent_was_red = parent->is_red();
                parent->set_black(); //
                if (parent_was_red) {
                    cout << "Case 4" << endl;
                    print(2,64,8,node);
                    // Case 4
                    return _root; // parents.front().first;
                }
                cout << "Case 3" << endl;
                print(2,64,8,node);
                node = parent;
                parents.pop_back();

            } else if (p.second and sibling->_right->is_black()) { // sibling->_left->is_red()
                // Case 5-L:
                sibling->set_red();
                sibling->_left->set_black();
                sibling = sibling->right_rotate();
                p.first->_right = sibling;

                /*
                if (p.second) {
                    p.first->_right = sibling;
                } else {
                    p.first->_left = sibling;
                }
                 */
                cout << "Case 5-L" << endl;
                print(2,64,8,node);

            } else if (!p.second and sibling->_left->is_black()) { // sibling->_right->is_red()
                // Case 5-R:
                sibling->set_red();
                sibling->_right->set_black();
                sibling = sibling->left_rotate();
                p.first->_left = sibling;
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
                parents.pop_back();

                revise_parents(sibling, parents);
                /*
                if (!parents.empty()) { // T.B.D.: reorganizing as an inline function call
                    auto gp = parents.back();
                    if (gp.second) {
                        gp.first->_left = sibling;
                    } else {
                        gp.first->_right = sibling;
                    }
                }
                 */

                if (p.second) {
                    parent->left_rotate();
                    sibling->_right->set_black();
                    parents.push_back(ParentInfo(sibling, true));
                } else {
                    parent->right_rotate();
                    sibling->_left->set_black();
                    parents.push_back(ParentInfo(sibling, false));
                }
                cout << "Case 6" << endl;
                print(2,64,8,node);
                parents.push_back(p);
                return _root;

            }
        }
    }

    // Case 1
    return node;
}
#endif /* REDBLACKTREE_HPP_ */
