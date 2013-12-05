/*
 * test_forscope.c
 *
 *  Created on: Nov 28, 2013
 *      Author: rong
 */
#include <stdio.h>

int main(void) {
  // Demonstrates a bug: sum has a fresh copy in each loop iteration.
  for (int i = 0; i<10; ++i) {
    int sum = 0;  // s for collecting the summation
    sum += i;
    printf("The sum is: %d\n", sum);
  }
  return 0;
}

