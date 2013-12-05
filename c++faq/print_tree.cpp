/*
 * print_tree.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: rong
 */

#include "../rbtree/src/include/rbtree.hpp"

#include <stack>
#include <vector>
#include <queue>
#include <iostream>
using std::cout;
using std::endl;
using std::stack;
using std::vector;
using std::queue;

typedef RedBlackTree<int> Tree;
typedef typename Tree::Node Node;

bool printLevel(const Node* pNode, size_t level) {
  queue<const Node*> q;
  if (!pNode->is_null()) {
    q.push(pNode);
  }
  q.push(nullptr);
  size_t currentLevel = 0;
  while (!q.empty()) {
    pNode = q.front();
    q.pop();
    if (pNode == nullptr) { // level separator
      ++currentLevel;
      if (currentLevel > level) {  // level reached
        break;
      } else if (q.empty()) {  // end of tree
        break;
      } else {
        q.push(nullptr);
      }
    } else {
      if (!pNode->left()->is_null()) {
        q.push(pNode->left());
      }
      if (!pNode->right()->is_null()) {
        q.push(pNode->right());
      }
    }
  }

  while (!q.empty()) {
    pNode = q.front();
    q.pop();
    cout << ' ' << pNode->_data;
  }

  if (currentLevel > level) {
    cout << endl;
    return true;  // means has this level
  } else {
    return false;
  }
}

/*
 * Complexity: O(n), worst case space O(n)
 */
void bottomUpPrint(const Tree& tree) {
  vector<const Node*> fakeQueue;
  stack<size_t, vector<size_t>> levelBeginIndicies;
  size_t queueHead=0;
  const Node* pNode = tree.root();
  if (!pNode->is_null()) {
    fakeQueue.push_back(pNode);  // enque
  }
  fakeQueue.push_back(nullptr);  // use nullptr as level separator
  levelBeginIndicies.push(0);

  // breath first visiting the tree, saving all nodes in the queue
  while (true) {  // queueHead < fakeQueue.size()
    pNode = fakeQueue[queueHead++];  // ++queue head faking "pop" element out of the queue
    if (pNode == nullptr) { // level separator
      levelBeginIndicies.push(queueHead);
      if (queueHead < fakeQueue.size()) {
        fakeQueue.push_back(nullptr);
      } else {
        break;
      }
    } else {
      if (!pNode->left()->is_null()) {
        fakeQueue.push_back(pNode->left());
      }
      if (!pNode->right()->is_null()) {
        fakeQueue.push_back(pNode->right());
      }
    }
  }

  size_t currentLevelLast  = fakeQueue.size()-1;
  while (!levelBeginIndicies.empty()) {
    size_t currentLevelBegin = levelBeginIndicies.top();
    levelBeginIndicies.pop();
    for (auto i = currentLevelBegin; i < currentLevelLast; ++i) {
      cout << ' ' << (fakeQueue[i]->_data);
    }
    cout << endl;
    currentLevelLast = currentLevelBegin-1;
  }
}

/*
 * Complexity: height * O(n), space span, worst case = n/2
 */
void bottomUpPrint(const Tree& tree, size_t depth) {
  const Node* pRoot = tree.root();
  for (auto i = depth+1; i>0; ) {
    printLevel(pRoot, --i);
  }
}

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

  rbtree.insert(-1);
  rbtree.insert(-7);
  rbtree.insert(9);
  rbtree.insert(10);
  rbtree.insert(-11);

  cout <<"\n Bottom up print: " << endl;
  bottomUpPrint(rbtree);
  bottomUpPrint(rbtree, 4);
  return 0;
}

