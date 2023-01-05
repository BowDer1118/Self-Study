#include <algorithm>
#include <iostream>
using namespace std;
/*
    輸入一個不存在重複字元的字串 輸出全部的排列組合
    example:
        輸入 "123" 有3!=3*2*1=6種組合
        輸出    123
                132
                213
                231
                312
                321
    思考:
    f(123)=1+f(23),f(23)=2+f(3)=3 ... 
    遞迴思考
*/

//交換字元的函數
void swap(char &a, char &b) {
    char temp = b;
    b = a;
    a = temp;
}

//輸入陣列與當前位置
void permutation(char *pStr, char *pPosition) {
    //退出條件
    if (*pPosition == '\0') {
        cout << pStr << endl;
    } else {
        for (char *pChar = pPosition; *pChar != '\0'; pChar++) {
            //開始交換 產生排列組合 (與後面的字元做交換)
            swap(*pChar, *pPosition);
            //遞迴
            permutation(pStr, pPosition + 1);
            //換回來
            swap(*pChar, *pPosition);
        }
    }
}

int main() {
    char test[] = "123";
    //手動 排列組合
    cout << "Manual permutation" << endl;
    permutation(test, test);

    cout << endl;

    //使用STL排列組合(必須保證 順序是排序完成的--->預設從小到大的順序)
    cout << "Use STL permutation" << endl;
    do {
        cout << test[0] << test[1] << test[2] << endl;
    } while (next_permutation(test, test + 3));
    return 0;
}