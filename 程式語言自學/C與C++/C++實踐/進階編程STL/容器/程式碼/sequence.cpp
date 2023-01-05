#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

//使用自訂義struct 製造仿函數 用來處理 容器中的每個元素
struct Display {
    //Overload () 運算符 ---> 仿函數
    void operator()(int element) {
        cout << element << " ";
    }
};

int main() {
    //宣告一個陣列
    int intArr[] = {1, 2, 3, 4, 5};
    /*
        宣告一個泛型為int的vector 
        並將 陣列的 首尾記憶體位置傳入 當作參數 初始化vector
        vector 以記憶體位置初始化時 區間是:左閉右開 [Start~End)

        list 和 deque 都有 上面說的 Constructor
    */
    vector<int> intVector(intArr, intArr + 5);
    list<int> intList(intArr, intArr + 5);
    deque<int> intDeque(intArr, intArr + 5);

    /*
        遍歷容器
        使用for_each(容器的記憶體起始位置,容器的記憶體結束位置,要調用的函數)
    
        要調用的函數 會傳入每個元素

        vector.begin() 獲取記憶體起始位置
        vector.end() 獲取記憶體結束位置    
    */
    cout << "for_each vector:" << endl;
    for_each(intVector.begin(), intVector.end(), Display());
    cout << endl;

    cout << "for_each list:" << endl;
    for_each(intList.begin(), intList.end(), Display());
    cout << endl;

    cout << "for_each deque:" << endl;
    for_each(intDeque.begin(), intDeque.end(), Display());
    cout << endl;

    cout << endl;

    /*
        queue 和 stack 是輔助資料結構
        可以使用deque容器 當作參數 來初始化
    
        priority_queue 則要向vector list deque 一樣
        使用陣列記憶體頭尾 當作參數 來初始化
    */
    queue<int> intQueue(intDeque);                      //先進先出 FIFO
    stack<int> intStack(intDeque);                      //先進後出  FILO
    priority_queue<int> intPQueue(intArr, intArr + 5);  //根據priority 出

    /*
        遍歷 queue stack priority_queue
        運用 每個資料結構的特性
    */

    //遍歷Queue
    cout << "Output queue:" << endl;
    while (!intQueue.empty()) {           //判斷stack中是否還有元素
        cout << intQueue.front() << " ";  //取得最前端的元素
        intQueue.pop();                   //推出最前端的元素(捨棄最前端的元素)
    }
    cout << endl;
    //遍歷Stack
    cout << "Output stack:" << endl;
    while (!intStack.empty()) {         //判斷stack中是否還有元素
        cout << intStack.top() << " ";  //取得最頂端的元素
        intStack.pop();                 //推出最頂端的元素(捨棄最頂端的元素)
    }
    cout << endl;
    //遍歷Priority Queue ---> 按照優先度(默認是 數值大的優先度大)
    cout << "Output priority Queue:" << endl;
    while (!intPQueue.empty()) {         //判斷stack中是否還有元素
        cout << intPQueue.top() << " ";  //取得優先度最大的元素
        intPQueue.pop();                 //推出優先度最大的元素(捨棄優先度最大的元素)
    }
    cout << endl;

    return 0;
}