#ifndef QUICKSORT2
#define QUICKSORT2
#include "MergeSort.h"
#include "MergeSort2.h"
#include "MergeSortBU.h"
#include "QuickSort.h"
#include "SortTestHelper.h"
using namespace std;

/*
    改進QuickSort
    1.透過隨機化選取partition的元素 盡量避免左右半邊陣列不平衡
    2.陣列較小時 使用InsertionSort處理--->性能更好一些
*/

template <class T>
int __partition2(T arr[], int l, int r) {
    //從arr[l]~arr[r]之間選一個跟陣列第一個人交換
    swap(arr[l], arr[rand() % (r - l + 1) + l]);

    T v = arr[l];  //把陣列中第一個元素當作參考標準--->也就是arr[p]的值
    int j = l;     //返回的索引值初始值--->就是arr[p]的索引值--->p(陣列的最起點)

    /*
        開始從arr[l+1]開始往arr[r]掃描--->開始對每個元素做分類(分到左或右邊)
        規則是
            1.如果當前元素arr[i]是小於v則將當前元素放到arr[j+1]的位置，然後更新j
              使得j永遠指向小於v的最後一個元素
            2.如果當前元素arr[i]大於等於v則不需要更動位置(因為本來就該放在arr[j]的右側)
    */
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < v) {
            swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    /*
        遍歷結束後，陣列就會呈現
        arr[l]~arr[j]都小於v
        arr[j+1]~arr[r]都大於等於v
        此時再將第一個元素(arr[p])與arr[j]交換
        就可以返回此位置j了
    */
    swap(arr[l], arr[j]);
    return j;
}

//對arr[l,r]做快速排序
template <class T>
void __quickSort2(T arr[], int l, int r) {
    if (r - l <= 15) {  //當陣列夠小--->採用InsertionSort更快
        insertionSort(arr, l, r);
        return;
    }

    //獲取當前陣列中間的元素
    /*
        此位置p就是partition後的結果
        也就是說 陣列會呈現
        arr[l]~arr[p-1]都小於arr[p]
        arr[p+1]~arr[r]都會大於等於arr[p]
    */
    int p = __partition2(arr, l, r);
    //繼續快速排序左右半部的元素
    __quickSort2(arr, l, p - 1);  //左半部:arr[l]~arr[p-1]
    __quickSort2(arr, p + 1, r);  //右半部:arr[p+1]~arr[r]
}
//QuickSort v2 改進QuickSort
template <class T>
void quickSort2(T arr[], int n) {
    //隨機化選重的元素值--->防止近乎有序的狀況下退化成O(N^2)
    srand(time(NULL));
    __quickSort2(arr, 0, n - 1);
}
#endif