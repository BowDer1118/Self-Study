#include <algorithm>
#include <iostream>

#include "MergeSort2.h"
#include "QuickSort2.h"
using namespace std;

/*
    使用雙路partition解決等於v的元素分布問題
    改善左右半邊的陣列大小差距大的問題
*/

//對arr[l,r]做partition
template <class T>
int __dPartition(T arr[], int l, int r) {
    //隨機化選取元素
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];  //以陣列起始的元素當參考

    /*
        標記出雙路排序的兩端起點
        左半陣列從arr[l+1]開始向後分類(因為arr[l]是參考點--->不考慮)
        又半邊陣列從arr[r]開始向前分類

        左半邊陣列碰到大於等於v的元素停下來--->與右半邊做交換--->使得當前元素被放到大於等於v的右半邊
        右半邊陣列碰到小於等於v的元素停下來--->與左半邊做交換--->使得當前元素被放到小於等於v的左半邊

        此過程一直到i與j互相錯過(碰見且經過)則代表整個陣列都被訪問過一次(arr[l+1]~arr[r]都被訪問過)
        並交換arr[l]與arr[j]
        使得整個陣列呈現:
        arr[l]~arr[i-1]都是小於等於v
        arr[j+1]~arr[l]都是大於等於v
    */
    int i = l + 1, j = r;  //左邊陣列從l+1開始(arr[l]是參考值) 右邊陣列從最後一個元素開始(arr[r])

    while (true) {
        while (i <= r && arr[i] < v) {  //由前往後找--->遇到大於等於的元素停止
            i++;
        }
        while (j >= l + 1 && arr[j] > v) {  //由後往前找--->遇到小於等於的元素停止
            j--;
        }

        if (i > j) {  //如果兩者錯過(碰見且經過)對方代表整個陣列都訪問過了
            break;
        }

        //交換左右兩邊停止的值
        swap(arr[i], arr[j]);
        //各自朝自己要訪問的方向行走
        i++;
        j--;
    }
    /*
        此時
        i會停在第一個大於等於v的位置
        j會停在最後一個小於等於v的位置(重要!)
        應該把arr[i]與arr[j]交換
        而整個陣列的參考點就是j
        使得陣列
        arr[l,j-1]都是小於等於v
        arr[j+1,r]都是大於等於v
        
    */
    swap(arr[l], arr[j]);
    return j;  //回傳參考點
}

//對arr[l,r]做DoubleQuickSort
template <class T>
void __dQuickSort(T arr[], int l, int r) {
    if (r - l + 1 <= 15) {  //陣列較小--->使用InsertionSort
        insertionSort(arr, l, r);
        return;
    }
    //邏輯與QuickSort一樣
    int p = __dPartition(arr, l, r);
    __dQuickSort(arr, l, p - 1);
    __dQuickSort(arr, p + 1, r);
}

template <class T>
void doubleQuickSort(T arr[], int n) {
    srand(time(NULL));
    __dQuickSort(arr, 0, n - 1);
}

int main() {
    int n = 50000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);
    int *arr5 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test Random Array" << endl;
    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("MergeSortBU", mergeSortBU, arr2, n);
    SortTestHelper::testSort("QuickSort", quickSort, arr3, n);
    SortTestHelper::testSort("QuickSort2", quickSort2, arr4, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr5, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    int swapTimes = 100;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);

    cout << endl;
    cout << "Test Nearly Ordered Array" << endl;
    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("MergeSortBU", mergeSortBU, arr2, n);
    SortTestHelper::testSort("QuickSort", quickSort, arr3, n);
    SortTestHelper::testSort("QuickSort2", quickSort2, arr4, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr5, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    return 0;
}