#include <cstdio>
#include <cstdlib>
#include <ctime>
/*
unsigned getSize() {
    return 10;
}
*/

unsigned getSize() {
    srand(time(0));
    auto s  =1+(rand() % 100);
    printf("Generated: %u\n", s);
    return s;
}

void printNumbers(unsigned s) {
    int arr[s];
    printf("Size of array: %u\n", (unsigned)(sizeof(arr)/sizeof(int)));
    auto i = 0;
    printf("\n");
    for (; i<s; ++i) {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main() {
    unsigned s = getSize();
    if (s>100) {
        s = s/2;
    } else if (s % 9 == 0) {
        s /= 9;
    }
    int arr[s];
    printf("Size of array: %u\n", (unsigned)(sizeof(arr)/sizeof(int)));
    int i = 0;
    printf("\n");
    for (; i<s; ++i) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    printNumbers(1+(rand() % 100));
    return 0;
}
