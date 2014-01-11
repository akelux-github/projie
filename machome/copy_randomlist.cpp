#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
    void process(queue<RandomListNode *>& q, unordered_map<RandomListNode *, RandomListNode *>& copied) {
        auto node = q.front();
        q.pop();
        if (node->next) {
            auto it = copied.find(node->next);
            if (it!=copied.end()) {
                copied[node]->next = it->second;
            } else {
                auto left_copy = new RandomListNode(node->next->label);
                copied[node]->next = left_copy;
                copied.emplace(node->next, left_copy);
                q.push(node->next);
            }
        }
        
        if (node->random) {
            auto it = copied.find(node->random);
            if (it!=copied.end()) {
                copied[node]->random = it->second;
            } else {
                auto right_copy = new RandomListNode(node->random->label);
                copied[node]->random = right_copy;
                copied.emplace(node->random, right_copy);
                q.push(node->random);
            }
        }
    }

public:
    RandomListNode *copyRandomList(RandomListNode *head) {  // assume the next links forms a linked list no circle
        if (!head) {
            return nullptr;
        }
        unordered_map<RandomListNode *, RandomListNode *> copied;  // nodes has already being copied 
        queue<RandomListNode *> q;  // queue of nodes to finish its link copies
        
        auto copy_head = new RandomListNode(head->label);
        copied.emplace(head, copy_head);
        q.push(head);
        
        while (!q.empty()) {
            process(q, copied);
        }
        
        return copy_head;
    }
};

int main() {
    RandomListNode* node1 = new RandomListNode(1);
    RandomListNode* node2 = new RandomListNode(2);
    node2->next = node1;
    // node2->random = node1;
    // node4->next = node2;
    RandomListNode* node3 = new RandomListNode(3);
    node3->next = node2;
    RandomListNode* node4 = new RandomListNode(4);
    node4->next = node3;

    RandomListNode* head = new RandomListNode(0);
    head->random = node4;
    Solution().copyRandomList(head);
}
