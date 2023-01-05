#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
    stack<int> s;
    queue<int> q;
    /*
        優先對列
        默認:最大值優先(less<T>)

        也可以自訂義優先概念
        使用最小值優先--->調用greater<int>
        因為greater的Generic function為 bool function(int x,int y){ return x>y}
        代表從小到大(升序)

        使用push加入資料
    */
    priority_queue<int> pq;
    priority_queue<int, vector<int>, greater<int>> pq2;

    pq.push(2);
    pq.push(1);
    pq.push(3);
    pq.push(0);

    cout << "Output priority_queue" << endl;
    while (!pq.empty()) {
        //獲得優先度最大
        int top = pq.top();
        pq.pop();

        cout << top << " ";
    }
    cout << endl;
    return 0;
}