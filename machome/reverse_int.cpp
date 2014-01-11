#include <iostream>
using namespace std;


class Solution {
public:
    int reverse(int x) {
        // special cases: 1200 -> 21, overflow say max = 31, 14 -> 41? 
        
        // we assume no overflow happens after reverser
        int sign = 1;
        if(x<0) {
            sign = -1;
        }
        int m = 1;
        int t = sign*(x/10);
        while (m <= t) {  // get digits of x
            m *=10;
        }

        if (m==1) {
            return x;
        }
        cout << "m: " << endl;
        int h = 1;
        int res = 0;
        while (x!=0) {
            int r = x % 10; // take lower digit
            int q = x / m;  // take highest digit
            x %= m;
            x /= 10;
            cout << "r, q, x: " << r << ", " << q << ", " << x << endl;
            cout << "m, h: " << m << ", " << h << endl;
            res += (r*m+ q*h);
            m /= 10;
            h *= 10;
        }
        
        return res;
    }
};

int main() {
    Solution s;
    cout << s.reverse(901000) << endl;
    cout << s.reverse(9010001) << endl;
    cout << s.reverse(9010001) << endl;
    cout << s.reverse(1) << endl;
    cout << s.reverse(101) << endl;
    cout << s.reverse(1001) << endl;
    cout << s.reverse(-1001) << endl;
    cout << s.reverse(-101) << endl;
    cout << s.reverse(-1) << endl;
}
