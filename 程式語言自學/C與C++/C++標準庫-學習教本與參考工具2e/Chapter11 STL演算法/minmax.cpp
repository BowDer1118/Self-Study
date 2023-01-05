#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;
/*
    找最小值有兩個版本
    1.ForwardIterator min_element(ForwardIterator beg,ForwardIterator end)
    2.ForwardIterator min_element(ForwardIterator beg,ForwardIterator end,CompFunc op)

    找最大值有兩個版本
    1.ForwardIterator max_element(ForwardIterator beg,ForwardIterator end)
    2.ForwardIterator max_element(ForwardIterator beg,ForwardIterator end,CompFunc op)

    同時找最大值與最小值有兩個版本
    1.ForwardIterator minmax_element(ForwardIterator beg,ForwardIterator end)
    2.ForwardIterator minmax_element(ForwardIterator beg,ForwardIterator end,CompFunc op)

    min_element與max_element 回傳值為 第一個 最小值 或 最小值 的位置
    minmax_element 回傳值為pair
    pair物件 first 是第一個 最小值物件位置 second 是 最後一個 最大值物件位置

    比較函式 默認使用operator<
    CompFunc 形式為 bool op(int v1,int v2){...}

    函數不應該改動傳入的參數值

    複雜度:線性
*/
int main() {
    deque<int> q;
    for (int i = 0; i < 5; i++) {
        q.emplace_back(i);
    }

    for (int i = 0; i < 10; i++) {
        q.emplace_back(i);
    }

    //物件位置要de-reference才是 物件
    int minValue = *(min_element(q.begin(), q.end()));
    int maxValue = *(max_element(q.begin(), q.end()));
    //輸出第一個最小值與第一個最大值
    cout << minValue << endl;
    cout << maxValue << endl;

    //auto會自動推導成 pair<deque<int>::iterator, deque<int>::iterator>
    // auto pair = minmax_element(q.begin(), q.end());
    auto pair = minmax_element(q.begin(), q.end(), [](const int a, const int b) -> bool { return a < b; });
    minValue = *pair.first;
    maxValue = *pair.second;
    //輸出第一個最小值與最後一個最大
    cout << minValue << endl;
    cout << maxValue << endl;

    return 0;
}