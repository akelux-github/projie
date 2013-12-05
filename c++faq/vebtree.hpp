/*
 * vebtree.hpp
 *
 *  Created on: Dec 1, 2013
 *      Author: rong
 */

#ifndef VEBTREE_HPP_
#define VEBTREE_HPP_
typedef unsigned long long key_type;

/*
 * intSqrt(N) computes the integral square root of N at compile time
 */

key_type intSqrt(key_type N) {
  key_type res = 0;
  key_type S = 0;
  while (S<N) {
    S+=2*res+1;
    ++res;
  }
  return res;
}




#endif /* VEBTREE_HPP_ */
