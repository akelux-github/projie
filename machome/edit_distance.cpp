#include <vector>
#include <iostream>
using namespace std;

class Solution {
    // l1 >= l2
    int minDistanceAux(const string& word1, size_t l1, const string& word2, size_t l2) {
        vector<vector<int>> h(l1+1, vector<int>(l2+1));
        h[l1-1][l2] = 1;
        for (int j=l2; j>=0; --j) {
            h[l1][j] = l2-j;
        }
        for (int j=l1-1; j>=0; --j) {
            h[j][l2] = l1-j;
        }
        for (int i=l1-1; i>=0; --i) {
            for (int j=l2-1; j>=0; --j) {
                int m = h[i+1][j+1];
                cout << "h[" << (i+1) << "," << (j+1) <<"] = " << h[i+1][j+1] << endl;
                if (word1[i] != word2[j]) {
                    m = 1+min(m, min(h[i+1][j], h[i][j+1]));
                    cout << "h[" << (i+1) << "," << (j) <<"] = " << h[i+1][j] << endl;
                    cout << "h[" << (i) << "," << (j+1) <<"] = " << h[i][j+1] << endl;
                    int l = max(l1-i, l2-j);
                    cout << "l, m: " << l << "," << m << endl;
                    m = min(m,l);
                }
                h[i][j] = m;
                cout << "h[" << i << "," << j <<"] = " << m << endl;
            }
        }
        return h[0][0];
    }
public:
    int minDistance(const string& word1, const string& word2) {
        const size_t l1 = word1.size();
        const size_t l2 = word2.size();
        
        if (l1 == 0) {
            return l2;
        }
        if (l2 == 0) {
            return l1;
        }
        
        return minDistanceAux(word1, l1, word2, l2);
    }
};

int main() {
    Solution s;
    cout << s.minDistance("a", "b") << endl;
}
