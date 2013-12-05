/*
 * count_1_digitals.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: rong
 */

#include <iostream>
#include <sstream>

using namespace std;

const unsigned char N_DIGITS=30;
size_t one_zeros[N_DIGITS];  // stores 10, 100, 1000, ...
size_t one_zeros_count[N_DIGITS]; // stores the corresponding

inline void initializeOneZeros() { // [0, 1000], n = 10, 100, 1000, ..., 100000
  one_zeros[0] = 10;
  for (unsigned char i = 1; i<N_DIGITS; ++i) {
    one_zeros[i] = 10*one_zeros[i-1];
  }

  one_zeros_count[0]=1;
  for (unsigned char i = 1; i<N_DIGITS; ++i) {
    one_zeros_count[i] = 10*one_zeros_count[i-1]+one_zeros[i-1];
  }
}

/*
 * f(n+1) = f(n) + 10^n ==> f(n) = n*10^(n-1);  one_zeros = 10^100
 * N < 10^11
 * quotient*countOneZeros(one_zeros) + countOther(reminder) + (quotient>1?one_zeros:(reminder+1));
 */
size_t count1s (size_t n) {
  size_t total = 0;
  while (n>=10) {
    unsigned char i = 0;
    while (one_zeros[i+1]<=n) {
      ++i;
    }

    size_t quotient = n / one_zeros[i];  // n = quotient * one_zeros + reminder
    n  %= one_zeros[i];

    if (quotient == 10) {
      return total + one_zeros_count[i] + 1;
    } else {
      total += quotient*one_zeros_count[i] + (quotient>1 ? one_zeros[i] : (n+1));
    }
  }
  return total+(n+9)/10;
}


int main(int argc, char** args) {

  initializeOneZeros();  // MUST: initialization

  if (argc == 2) {
    istringstream iss(args[1]);
    size_t n = 0;
    iss >> n;
    cout << n << endl;
    cout << count1s(n) << endl;
  } else {
    for (size_t N=9999999999; N>0; --N) {
      if (N == count1s(N)) {
        cout << N << endl;
        return 0;
      }
    }
  }
  return 0;
}
