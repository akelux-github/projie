/*
 * tuple.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: rong
 */

#include <string>
#include <iostream>
#include <tuple>
using std::string;
using std::cout;
using std::endl;


int main(void) {
  auto t = std::make_tuple(1, 2, "Rong Xiao", 165.5);
  cout << std::get<2>(t) <<endl;
  cout << std::get<3>(t) <<endl;
  return 0;
}



