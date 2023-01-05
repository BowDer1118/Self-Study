#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int> s = {20, 10, 2, 10, 10};
    /*  
        equal_range(元素值):搜尋相同元素存在的區間
        會返回相同元素值存在的區間 返回值是pair<multiset<int>::iterator,multiset<int>::iterator>
        pair.first:第一個出現元素值的位置
        pair.second:最後一個出現元素值的位置
    */

    //auto會被自動推導成pair<multiset<int>::iterator,multiset<int>::iterator>
    auto it = s.equal_range(10);

    //走訪迭代器--->迭代器會返回set中的物件位置
    for (auto i = it.first; i != it.second; i++) {
        cout << *i << endl;
    }

    return 0;
}