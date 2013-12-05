/*
 * dupdef.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: rong
 */
/*
 * lifetime.cpp
 *
 *  Created on: 2013-11-27
 *      Author: Rong Xiao
 */
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct emitter {
    string str;
    emitter(const string& s) : str(s) { cout << "Created " << str << endl; }
    ~emitter() { cout << "Destroyed " << str << endl; }
};

void foo(bool skip_first)
{
    if (!skip_first)
        static emitter a("in if");
    static emitter b("in foo");
}

int main(int argc, char*[])
{
    foo(argc != 2);
    if (argc == 3)
        foo(false);
    foo(true);
    foo(false);
    foo(true);
    foo(true);
}





