#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    find有三種形式
    1.InputIterator find(InputIterator begin,InputIterator end,const &T value)
    2.InputIterator find_if(InputIterator begin,InputIterator end,UnaryPredicate op)
    3.InputIterator find_if_not(InputIterator begin,InputIterator end,UnaryPredicate op)

    搜尋範圍:[begin,end)
    
    UnaryPredicate形式為 bool op(T t){....}
    
    函數不應該改動傳入的參數值

    第一種會返回 第一個 元素值等於value 的元素位置
    第二種會返回 UnaryPredicate 產生true 的元素位置
    第二種會返回 UnaryPredicate 產生false 的元素位置

    如果沒有查找到元素 則返回InputIterator.end()

    複雜度:線性

    [補充]
    1.如果搜尋範圍是 已序空間(Sorted Range) 則應使用lower_bound() upper_bound() equal_range() 或者是binary_search() 
      效能會更好
    2.Associative和unordered容器有提供成員函式find() 效率會比使用std::find()更好
        AssociativeContainer.find() 複雜度:對數等級
        UnorderedContainer.find() 複雜度:常數等級
*/

int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.emplace_back(i);
    }

    //auto的型別會推導成 vector<int>::iterator
    auto pos = find(v.begin(), v.end(), 8);

    //檢查返回位置
    if (pos != v.end()) {
        cout << *pos << endl;  //8
    } else {
        cout << "Not Found" << endl;
    }

    //以lambda表示參數
    auto compare = [](const int value) -> bool { return value > 10; };
    pos = find_if(v.begin(), v.end(), compare);

    if (pos != v.end()) {
        cout << *pos << endl;
    } else {
        cout << "Not Found" << endl;  //Not Found
    }

    pos = find_if_not(v.begin(), v.end(), compare);

    if (pos != v.end()) {
        cout << *pos << endl;  //0
    } else {
        cout << "Not Found" << endl;
    }
    return 0;
}