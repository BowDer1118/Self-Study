#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    /*
        transform用來處理容器
        1.對容器中的每個元素做處理
            transform(容器起始,容器終點,處理函數)
        2對兩個容器做處理 並放到另外一個容器中
            transform(第一個容器起始,第一個容器結束,第二個容器起始,最後存放容器的起始,處理函數)
            會將第一個第二個 前(第一個容器的容量) 透過處理函數 處理
    
    */
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {10, 20, 30, 40, 50};
    int results[5];
    //std::plus<int>()是STL中的 仿函數 將傳入的兩個值做相加
    // transform(array1, array1 + 5, array2, results, plus<int>());
    transform(array1, array1 + 5, array2, results, [](int v1, int v2) -> int { return v1 + v2; });

    /*
        lambda expression
        本質上是一個inline的匿名函式
        語法:
            [全域變數](傳入的參數)-> 函式返回類型 {函式內容}
    */
    cout << "Ouput results array" << endl;
    for_each(results, results + 5, [](int sum) -> void { cout << sum << " "; });
    cout << endl;
    cout << endl;

    cout << "Do  search" << endl;
    //binary search
    int arr[] = {0, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7, 7, 8};
    /*
        count()可以記數
        傳入 容器起點 容器終點 要統計的元素 數量
        
        count_if()可以找吻合if條件的元素 數量
        傳入 容器起點 容器終點 要統計的元素 數量 if條件
            if條件---> bool function(T value){T 條件}
            1.使用bind2nd(less<>或greater<T>,數值) 用來表達 小於或大於 某個數值
            2.或使用函數 或 lambda expression

    */
    int num = count(arr, arr + sizeof(arr) / sizeof(int), 7);
    cout << "Find " << num << " element is 7" << endl;

    // num = count_if(arr, arr + sizeof(arr) / sizeof(int), bind2nd(less<int>(), 7));
    num = count_if(arr, arr + sizeof(arr) / sizeof(int), [](int value) -> bool { return value < 7; });
    cout << "Find " << num << " element is less than 7" << endl;

    cout << endl;
    cout << "Do binary search" << endl;

    /*
        二分查找法(要求必須排序完成了)
        binary_search(容器起點,容器中點,查找元素)
        回傳值是1 代表查找到 0代表沒有查找到
    */
    int len = sizeof(arr) / sizeof(arr[1]);
    bool findResult = binary_search(arr, arr + len, 8);
    if (findResult) {
        cout << "Find 8 in array" << endl;
    } else {
        cout << "Not found 8 in array" << endl;
    }

    /*
        從容器中 找子序列
        使用search(容器起點,容器中點,子序列起點,子序列終點)
        返回 第一次再容器中 找到子序列的第一個位置
    */
    vector<int> v(arr + 2, arr + 5);  //使用arr[2]~arr[4]當作子序列
    vector<int>::iterator pos;
    int *pos = search(arr, arr + len, v.begin(), v.end());
    cout << *pos << endl;
}