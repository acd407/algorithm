#include "List.hpp"
#include <cassert>
#include <fmt/core.h>
#include <stdio.h>
#include <vector>

using fmt::print;
void test01_f (int &a) { a *= 2; }

void test01() {
    List l = List<int> {3, 2, 4, 8, 9, 4};
    l.push_back (6)
        .push_back ({3, 5, 7, 1, 9, 4, 5})
        .push_back ({7, 1, 9, 4, 5})
        .insert (3, 19)
        .rm (6)
        .rm()
        .traverse (test01_f);
    int (*g) (int &) = [] (int &a) -> int { return a; };
    vector v = l.traverse (g);
    for (auto i : v)
        print ("{}\t", i);
    print ("\n{}\t{}\n", l.length(), l.size());
}

shared_ptr<vector<double>> test02() {
    List l {0.2, 5.8, 3.5, 0.6};
    l[1] = 4.4;
    l.insert(2, 4.9);
    print ("{}\n", l.locate (3.5));
    l.succ (3.5) = 0.8;
    l.pred (4.4) = 0.1;
    print ("{}\n", l.pop());
    double (*f) (double &) = [] (double &e) { return e * 2 + 1; };
    return l.straverse (f);
}

int main() {
    test01();
    auto p = test02();
    for (auto i : *p)
        print ("{}\t", i);
    return 0;
}