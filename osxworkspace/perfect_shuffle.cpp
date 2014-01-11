/*
 * perfect_shuffle.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: Rong
 */
#include <iterator>
#include <iostream>     //  use the system input:/output
#include <vector>
#include <cstdlib>
using namespace std;    // to import the names like cout, endl, cin
using std::iterator_traits;
using std::swap;
// Input: a[0], a[1], a[2*k+1]
// Output: a[0], a[k+1], a[1], a[k+2],
// a[i] -> a[2*i+1], 0, 1, 2, 3, 4, 5 -> 3,0,4,1,5,2
// i -> 2*i+1, for i<k; i -> 2*i % 2*k; for i>=k
inline size_t mapIndex(size_t i, size_t k) {
  return (i<k) ? (2*i + 1) : 2*(i % k);
}

void swap (int &a, int& b) {
  cout << "calling my swap" << endl;
  a ^= b;
  b ^= a;
  a ^= b;
}

template <class RandomAccessIterator>
void perfectShuffle(RandomAccessIterator start, RandomAccessIterator last) {
  typedef typename iterator_traits<RandomAccessIterator>::value_type T;
  typedef typename iterator_traits<RandomAccessIterator>::difference_type size_t;
  size_t total = last - start;  // total
  if (total == 1) {
    return;
  }
  size_t half = total/2;
  size_t total_placed = 0;
  size_t placing_index = 0;
  T placing_value = start[0];
  size_t placed_before = 0;  // all indices before have been taken care
  while (total_placed < 2*half) {
    if (placing_index < placed_before) {
      // ++placed_before;
      placing_index = placed_before;
      placing_value = start[placing_index];
      continue;
    } else if (placing_index == placed_before) {
      ++placed_before;
    }
    size_t destinated_index = mapIndex(placing_index, half);
    cout << "Placing " << placing_index << " with value " << placing_value << " to " << destinated_index;
    cout << endl;
    swap(placing_value,start[destinated_index]);
    // start[destinated_index] = start[scanning];
    ++total_placed;
    placing_index = destinated_index;
  }
  // for total being odd, making sure the last one being placed to a different place
  if (2*half<total) {
    swap(start[2*half-1], start[2*half]);
  }
}

// The main function
int main(int argc, char** args) {
  if (argc<1) {
    return 1;
  }

  vector<int> vec(argc-1);
  for (size_t i=0; i<vec.size(); ++i) {
    vec[i] = atoi(args[i+1]);
    cout << ' ' << vec[i];
  }
  cout << endl;

  perfectShuffle(vec.begin(), vec.end());
  cout << "After shuffling: "<< endl;
  for (size_t i=0; i<vec.size(); ++i) {
    cout << ' ' << vec[i];
  }
  cout << endl;

  return 0;
}


