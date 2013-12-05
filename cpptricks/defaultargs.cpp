#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void print(string* msg = new string("Hello world!")) { // OK but memory leak
    cout << (*msg) << endl;
}

string* getString(string s="") {
    return new string(s);
}

void print2(string* msg = getString("Hello world!")) { // OK again
    cout << (*msg) << endl;
}

int main() {
    string s("Rong Xiao");
    print();
    print(&s);
    print2();
    print2(&s);
    return 0;
}

