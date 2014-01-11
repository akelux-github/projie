/*
 * rawstring.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Rong
 */


#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
using std::cout;
using std::endl;
using std::string;

int main() {

	auto str = u" 肖溶";

	cout << str << endl;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > myconv;
	std::wstring ws(L"Hello world , 肖溶");
	std::string bs = myconv.to_bytes(ws);
	std::cout << bs << '\n';

	return 0;

}


