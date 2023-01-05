#include <algorithm>
#include <iostream>

#include "UnionFindTestHelper.h"
using namespace std;

int main() {
    int n = 1000000;
    UnionFindTestHelper::testUF3(n);
    UnionFindTestHelper::testUF4(n);
    UnionFindTestHelper::testUF5(n);

    return 0;
}