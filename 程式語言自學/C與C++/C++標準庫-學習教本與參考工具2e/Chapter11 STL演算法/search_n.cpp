#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    搜尋n個連續匹配值(First n Matching Element)
    1.search_n(Iterator beg,Iterator end,Size count,const T& value)
    2.search_n(Iterator beg,Iterator end,Size count,const T& value,BinaryPredicate op)

    搜尋範圍:[begin,end)
    
    第一種:返回第一個符合 連續count個 元素值都是value的區段 第一個元素位置
    第二種:返回第一個符合 連續count個 讓Predicate都為true的區段 第一個元素位置

    沒找到則會返回 container.end()

    BinaryPredicate 形式為 bool op(T elem,T value){....} 
    第一個參數elem是區間中的元素
    第二個參數是傳入search_n中的第4個參數

    op不該改變傳入的數值

    複雜度:線性
*/

int main() {
    vector<int> v = {1, 2, 7, 7, 6, 3, 9, 5, 7, 7, 7, 3, 6};

    //找連續3個元素都是7的區段
    auto pos = search_n(v.begin(), v.end(), 3, 7);
    if (pos != v.end()) {
        cout << *pos << endl;                      //7
        cout << distance(v.begin(), pos) << endl;  //8--->v[8]
    }

    //找連續3個都是奇數的區段
    //lambda expression (elem為區間內的元素 value為search_n中的第4個參數)
    auto comp = [](int elem, int value) -> bool { return elem % value == 1; };
    pos = search_n(v.begin(), v.end(), 3, 2, comp);

    if (pos != v.end()) {
        cout << *pos << endl;  //3
    }
    return 0;
}