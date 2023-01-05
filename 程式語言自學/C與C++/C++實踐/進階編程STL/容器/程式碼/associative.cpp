#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

//仿函數
struct Display {
    //會傳入map中的pair元素
    void operator()(pair<string, double> p) {
        //first就是key second就是value
        cout << p.first << " " << p.second << endl;
    }
};

int main() {
    /*
        map要傳入key-value的泛型

        存放元素的方式
        1.map[key]=value
        2.map.insert(pair物件)
            pair<key泛型,value泛型>(key,value)
        3.map.insert(map::value_type)
            map<key泛型,value泛型>::value_type(key,value)
    
        如果存入 相同key值 則會插入失敗(也就是沒有作用)
    */
    map<string, double> studentScores;
    studentScores["Peter"] = 95.0;
    studentScores["Tom"] = 98.5;

    studentScores.insert(pair<string, double>("Mary", 100.0));
    studentScores.insert(pair<string, double>("Jim", 98.6));
    studentScores.insert(pair<string, double>("Zoe", 94.5));
    //修改元素值
    studentScores["Zoe"] = 88.5;
    studentScores.insert(map<string, double>::value_type("Kevin", 95.5));

    /*
        遍歷map
        使用for_each配合仿函數 處理map中的每個元素 也就是pair<string,double>
    
        順序是依照內部預設的順序(關聯性容器是樹狀的)
        如果想要自定義順序 那就使用序列性容器
    */
    for_each(studentScores.begin(), studentScores.end(), Display());
    cout << endl;

    /*
        查詢map中的資料
        map.find(key) 會return 迭代器指標 
        如果查詢到 會return 元素的位置
            使用iter->first iter->second 訪問pair物件(指標的方式)
        如果查詢不到 會返回map的最後位置(map.end())
    */
    map<string, double>::iterator iter;  //map的iterator
    cout << "Found the score of Tom " << endl;
    iter = studentScores.find("Tom");
    if (iter != studentScores.end()) {
        cout << "Found the score is " << iter->second << endl;
    } else {
        cout << "Not found the key" << endl;
    }
    cout << endl;

    /*
        iterator遍歷查找並刪除的過程
        使用map.erase(iterator)並返回刪除後的 新的記憶體位置
        也就是新的元素
    */
    iter = studentScores.begin();  //先設指標起始位置
    while (iter != studentScores.end()) {
        //刪除元素
        if (iter->second <= 95.0) {
            //刪除當前元素 並取得新的iterator位置(也就是下一個元素)
            iter = studentScores.erase(iter);
        } else {
            //往下一個元素
            iter++;
        }
    }
    //重新輸出
    cout << "After delete score <= 95.0 student" << endl;
    for_each(studentScores.begin(), studentScores.end(), Display());
    cout << endl;

    /*
        使用for循環配合iterator遍歷容器
    */

    for (iter = studentScores.begin(); iter != studentScores.end();) {
        if (iter->second <= 98.5) {
            iter = studentScores.erase(iter);
        } else {
            iter++;
        }
    }
    cout << "After delete score <= 98.5 student" << endl;
    for_each(studentScores.begin(), studentScores.end(), Display());
    cout << endl;

    /*
        使用map.find(key)方法刪除元素
        如果查找到map::iterator就不會是map.end()    
    */
    iter = studentScores.find("Jim");
    if (iter != studentScores.end()) {
        studentScores.erase(iter);
        cout << "delte successed" << endl;
    } else {
        cout << "Not fount cancel delte" << endl;
    }

    cout << "After delete student name Jim" << endl;
    for_each(studentScores.begin(), studentScores.end(), Display());
    cout << endl;

    /*
        直接刪除元素
        map.erase("key")
        返回值 如果為0 代表 沒有找到 沒有刪除
        不為0 則代表找到並刪除
    */
    studentScores["Test"] = 60.0;
    studentScores.erase("Test");

    cout << "After delete Test element" << endl;
    for_each(studentScores.begin(), studentScores.end(), Display());
    cout << endl;

    /*
        使用map.erase(起始點,終點)刪除範圍
    */
    studentScores.erase(studentScores.begin(), studentScores.end());
    if (studentScores.empty()) {
        cout << "container is empty" << endl;
    } else {
        cout << "container is not empty" << endl;
    }

    return 0;
}