#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

int main() {
    //雙向鏈表
    list<int> listContainer;
    //從前或後加入1234
    listContainer.push_back(3);
    listContainer.push_front(2);
    listContainer.push_back(4);
    listContainer.push_front(1);

    cout << "Use list::iterator(font to back)" << endl;
    list<int>::iterator it;
    //iterator不支持 "<" 的操作
    for (it = listContainer.begin(); it != listContainer.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << endl;

    cout << "Use list::reverse_iterator(back to font)" << endl;
    //反向iterator
    list<int>::reverse_iterator reit;
    //使用rbegin()和rend()代表反向的起點與終點
    for (reit = listContainer.rbegin(); reit != listContainer.rend(); reit++) {
        cout << *reit << " ";
    }
    return 0;
}