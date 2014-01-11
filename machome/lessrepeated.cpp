#include <iostream>
#include <vector>
using namespace std;
int singleNumber(int A[], int n) {
    vector<int> count(sizeof(int)*8,0);
    int result = 0;
    for (int j = 0; j < n; j++) {
        cout << "processing: " << A[j] << endl;
        for (int i = 0; i < sizeof(int)*8; i++) {
            if ((A[j] >> i) & 1) {
                cout << "bit set at: " << i << endl;
                count[i]++;
            }
        }
    }
    
    for (int i = 0; i < sizeof(int)*8; i++) {
        count[i] %= 3;
        if (count[i] != 0 ) {
            cout << "result bit set at: " << i << endl;
            result |= (1 << i);
        }
    }
    
    return result;
}

int main() {
    int A[] = {0,0,0,1,1,1,99,99,99,99,99};
    cout << singleNumber(A, sizeof(A)/sizeof(int)) << endl; 
}
