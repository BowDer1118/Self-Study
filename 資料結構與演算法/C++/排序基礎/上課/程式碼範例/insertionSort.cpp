#include <algorithm>
#include <iostream>

#include "SelectionSort.h"
#include "SortTestHelper.h"
using namespace std;

//insertionSort_v1
template <class T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {  //從arr[1]開始排序(因為arr[0]其實相當於插入完畢了--->只有一個位置可以插--->已經排序完成了)
        //開始尋找arr[i]合適的插入位置--->在arr[0]~arr[i]的位置中選一個位置放入
        for (int j = i; j > 0; j--) {      //j>0的原因是因為將arr[j]與arr[j-1]做比較，所以最後一次比較j=1是比較arr[0]與arr[1]
            if (arr[j] < arr[j - 1]) {     //如果前面大後面小
                swap(arr[j], arr[j - 1]);  //交換成 前面小後面大
            } else {                       //如果前面都是排序完成(小到大)--->可以不必再比較了--->前面都已經是小到大了
                break;
            }
        }
    }
}

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

int main() {
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, 3);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test Random Array" << endl;
    SortTestHelper::testSort("SelectionSort", selectionSort, arr1, n);
    SortTestHelper::testSort("InsertionSort", insertionSort, arr2, n);
    SortTestHelper::testSort("InsertionSort2", insertionSort2, arr3, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    int swapTimes = 100;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test Nearly Ordered Array" << endl;
    SortTestHelper::testSort("SelectionSort", selectionSort, arr1, n);
    SortTestHelper::testSort("InsertionSort", insertionSort, arr2, n);
    SortTestHelper::testSort("InsertionSort2", insertionSort2, arr3, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    return 0;
}