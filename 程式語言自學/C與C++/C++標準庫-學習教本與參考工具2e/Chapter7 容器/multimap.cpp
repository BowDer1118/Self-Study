#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main() {
    multimap<int, char> map;
    map.emplace(20, 'G');
    map.emplace(10, 'C');
    map.emplace(10, 'E');
    map.emplace(10, 'A');
    map.emplace(5, 'D');
    /*  
        equal_range(元素值):搜尋相同元素存在的區間
        會返回相同元素值存在的區間 返回值是pair<multimap<int>::iterator,multimap<int>::iterator>
        pair.first:第一個出現元素值的位置
        pair.second:最後一個出現元素值的位置
    */
    auto it = map.equal_range(10);
    //走訪迭代器--->迭代器會返回map中的pair物件位置
    for (auto i = it.first; i != it.second; i++) {
        cout << i->second << endl;
    }
    return 0;
}