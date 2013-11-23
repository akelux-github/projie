/*
 * userliterals.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Rong
 */
#include <complex>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::complex;
using std::string;

constexpr complex<double> operator "" _i(long double d) { // imaginary literal
	return complex<double>(0,2*d);	// complex is a literal type
}

constexpr string operator "" _p(const char* str, size_t len) {
	return string(str, len);
}

int main() {
	auto i = 1.0_i;
	cout << i << endl;
	auto s = "World"_p;

	cout << s << endl;
	return 0;
}
