#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    檢驗區間是否完全相等(順序、數值完全相同)
    1.bool equal(Iterator beg,Iterator end,Iterator cmpBeg)
    2.bool equal(Iterator beg,Iterator end,Iterator cmpBeg,BinaryPredicate op)

    版本1:判斷[beg,end)中的元素是否都和comBeg開頭的區間 都相同
    版本2:判斷[beg,end)中的元素和comBeg開頭的區間 都會讓BinaryPredicate產生true

    BinaryPredicate形式為 bool op(int elem,int comElem){...}
    elem:[beg,end)中的元素
    cmpElem:cmpBeg指向的元素
    必須確保cmpBeg中的元素足夠(數量>=區間數量) 否則結果不保證正確

    複雜度:線性
*/

/*
    檢驗區間的不定序相等性(順序不同、元素相同)
    1.bool is_permutation(Iterator beg1,Iterator end1,Iterator beg2)
    2.bool is_permutation(Iterator beg1,Iterator end1,Iterator beg2,CompFunc op)

    版本1:調用默認的opeator==比對 區間元素是否相同 只是排列方式不同
    版本2:調用自訂義CompFunc op比對 區間元素是否相同 只是排列方式不同
    CompFunc op 形式為 bool op(elem1,elem2) 
    此function應該再elem1等於elem2時 回傳true

    複雜度:兩次線性呼叫
*/

int main() {
    vector<int> v1 = {1, 2, 3, 4, 5, 6};
    vector<int> v2 = {1, 2, 3, 4, 5, 6};

    bool isEqual = equal(v1.begin(), v1.begin(), v2.begin());
    if (isEqual) {
        cout << "Equal" << endl;  //Equal
    } else {
        cout << "Not Equal" << endl;
    }

    v1.assign({3, 1, 2, 5, 6, 4});  //亂序 但元素都是1-6

    bool isPermutation = is_permutation(v1.begin(), v1.end(), v2.begin());
    if (isPermutation) {
        cout << "Equal but permutation" << endl;  //Equal but permutation
    } else {
        cout << "Not equal" << endl;
    }

    return 0;
}