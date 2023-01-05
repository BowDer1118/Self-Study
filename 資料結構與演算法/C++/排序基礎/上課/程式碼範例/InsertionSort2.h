#ifndef INSERTION_SORT_2
#define INSERTION_SORT_2
using namespace std;
//insertionSort_v2
//改善一直swap的overhead
//swap一次是3次賦值運算--->改成2次賦值運算--->效能好一點
template <class T>
void insertionSort2(T arr[], int n) {
    for (int i = 1; i < n; i++) {  //從arr[1]開始排序(因為arr[0]其實相當於插入完畢了--->只有一個位置可以插--->已經排序完成了)
        //開始尋找arr[i]合適的插入位置--->在arr[0]~arr[i]的位置中選一個位置放入
        T e = arr[i];                 //儲存當前arr[i]的值
        int j;                        //保存e應該插入的位置(從arr[0]~arr[i]這些位置中查找)
        for (j = i; j > 0; j--) {     //j最後一個值應該為1--->最後一組比較為e與arr[0]的比較
            if (arr[j - 1] > e) {     //arr[j-1]大於e--->代表arr[j]不是e應該插入的位置
                arr[j] = arr[j - 1];  //將arr[j-1]的值移動到arr[j](前者向後移)
            } else {                  //arr[j-1]<e--->代表e應該放在arr[j]了--->不用再檢查直接break
                break;
            }
        }
        //此時arr[j]就是e應該放的位置
        arr[j] = e;
    }
}
#endif