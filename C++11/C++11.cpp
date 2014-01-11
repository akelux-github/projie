//============================================================================
// Name        : C++11.cpp
// Author      : Rong Xiao <akelux@gmail.com>
// Version     :
// Copyright   : Copyleft as GPL or BSD
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main() {
	auto s = "Hello C++11!!!";
	cout << s << endl;
	string str{s};
	cout << str << endl;
	return 0;
}
