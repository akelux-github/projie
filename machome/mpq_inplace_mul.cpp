#include <gmp.h>
#include <iostream>
using std::cout;
using std::endl;

int main() {
    mpz_t q1, q2, q3; 
    mpz_init_set_ui(q1, 10);
    mpz_init_set_ui(q2, 11);
    mpz_init_set_ui(q3, 13);
    mpz_mul(q2,q2,q3);
    cout << mpz_get_ui(q2) << endl;
    return 0;
}
