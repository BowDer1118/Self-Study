#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

/*
    count有兩個版本
    1.difference_type count(InputIterator beg,InputIterator end,const T& value)
    2.difference_type count_if(InputIterator beg,InputIterator end,UnaryPredicate op)

    統計範圍:[begin,end)

    版本1:返回 元素值等於value的數量
    版本2:統計 傳入的一元Predicate函式物件 產生true結果的 元素數量
    
    (可以傳入lambda functor function pointer)
    Predicate形式為 bool function(T value){...}
    效能:lambda==functor>function pointer

    函數不應該改動傳入的參數值

    複雜度:線性

    [補充] 關聯式(Associative)與未序式(Unordered)容器有提供成員函式find() 用法相同
        ex:
            container.count()
*/

int main() {
    vector<int> v;
    for (int i = 0; i < 10; i++) {
        //使用emplace_back 之接在要插入地方創建物件 避免創建臨時物件 與銷毀臨時物件的Overhead
        v.emplace_back(i);
    }

    //統計元素值等於5的物件數量
    int num = count(v.begin(), v.end(), 5);
    cout << num << endl;  //1

    //統計元素屬於偶數的物件數量
    num = count_if(v.begin(), v.end(), [](int elem) -> bool { return elem % 2 == 0; });
    cout << num << endl;  //5
    return 0;
}