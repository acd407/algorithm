#include "List.hpp"
#include <cassert>
#include <stdio.h>
#include <vector>
void f (int &a) { a *= 2; }
int g (int &a) { return a; }

int main() {
    List l = List<int> {3, 2, 4, 8, 9, 4};
    assert (l.getLastError() == OK);
    l.push_back (6).push_back ({3, 5, 7, 9,8,4,1,1,9,4,5}).traverse (f);
    int (*gg)(int &) = [](int &a) -> int {return a;};
    vector v = l.traverse(gg);
    for (auto i : v)
        printf ("%d\t", i);
    printf("\n%d\t%d",l.length,l.size);
    return 0;
}