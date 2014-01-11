/*
 * constexpr.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Rong
 */



/*
 * rangefor.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Rong
 */
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
	for (auto x : {1.0, 2.0, 3.0}) {
		cout << ' ' << x;
	}

	cout << endl;


	for (auto x : "Hello world") {
		cout << ' ' << x;
	}

	cout << endl;

	vector<string> vs{"Hello", "World"};

	cout << "Reference to vector of strings: "<< endl;
	for (auto& x : vs) {
		cout << ' ' << x;
	}

	cout << endl;

	return 0;

}




