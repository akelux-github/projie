#include <algorithm>
#include <iostream>
using namespace std;

void merge(int A[], int m, int B[], int n) {  // Use B to store the bigger elements
    if (n==0) {
        return;
    }
    
    if (m==0) {
        for (size_t i=0; i<n; ++i) {  // copy B to A
            A[i] = B[i];
        }
        return;
    }
   
    for (int i=m-1; i>=0; --i) {  // copy A to free store
        A[n+i] = A[i];
    }

    // std::rotate(A, A+m, A+m+n);
    
    int i = 0; 
    int j = 0;
    int k = n;
    while (k<m+n && j<n) {
        // Invariant: placing i; the candidate is to find among A[i], B[j], and A[k]
        // all elements in B before B[j] have been placed
        if (A[k] <= B[j]) {
            A[i++] = A[k++];
        } else {
            A[i++] = B[j++];
        }
    }
    
    while (j<n) {
        A[i++] = B[j++];
    }
}

int main() {
    int A[] = {1,4};
    int B[] = {2};
    merge(A, 1, B, 1);
    for (int i=0; i<2; i++) {
        cout << ' ' << A[i];
    }
    cout << endl;
}
