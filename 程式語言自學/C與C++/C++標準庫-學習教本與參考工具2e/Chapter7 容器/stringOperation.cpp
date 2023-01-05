#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    string inputString("Hello C++ Language");
    string str("C++");
    //find(string str):返回第一個找到的字串 第一個字元索引值
    //注意:返回值為string::size_type 所以auto會自動推導成string::size_type
    auto pos = inputString.find("C++");
    //檢查是否存在
    if (pos != inputString.npos) {
        //erase(int pos,int num):刪除 從str.at(pos)開始算num個字元
        inputString.erase(pos, 3);
    }
    cout << inputString << endl;  //Hello  Language
    return 0;
}