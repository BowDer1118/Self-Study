#include <algorithm>
#include <iostream>

#include "DoubleQuickSort.h"
#include "MaxHeap.h"
#include "MergeSort2.h"
#include "QuickSortThreeWay.h"
#include "SortTestHelper.h"
#include "heapSort.h"
#include "heapSort2.h"
using namespace std;

/*
    從0開始編號節點的MaxHeap

    已知一個節點為k
    則此節點的父節點為 (k-1)/2
    此節點的左節點為 2*k+1
    此節點的右節點為 2*k+2
    
    最後一個非葉子節點的編號為 (最後一個節點索引值-1)/2

    [注意] 最後一個節點的索引值為 (元素總數-1)

    因此 最後一個非葉子節點的編號為 (最後一個節點索引值-1)/2--->((元素總數-1)-1)/2
*/

//對arr[0...n-1]中的arr[k]做shiftDown
template <class T>
void __shiftDown(T arr[], int n, int k) {
    //注意此時陣列的範圍在arr[0...n-1]--->最後一個元素索引值為(n-1)
    while ((2 * k + 1) <= (n - 1)) {                    //如果左節點存在
        int j = 2 * k + 1;                              //要交換的節點
        if (j + 1 <= (n - 1) && arr[j] < arr[j + 1]) {  //如果存在右節點且右節點>左節點
            j += 1;                                     //將j設定為右節點
        }

        if (arr[k] >= arr[j]) {  //如果父節點已經大於等於子節點
            break;               //不需要交換--->arr[k]已經到達適當位置
        } else {
            swap(arr[k], arr[j]);  //子父節點交換
            k = j;                 //繼續往下層檢查
        }
    }
}

/*
    對arr[0...n-1]使用heapify概念進行heapSort

    在原本的陣列中，直接進行heapSort
    不停的構建MaxHeap的結構
    然後不停地交換最大值與MaxHeap中最後一個元素
    即 交換arr[0]與arr[最後一個元素]
    然後再對新的arr[0]做shiftDown 則又產生MaxHeap結構
    以此類推到最前面 則完成小到大排序

    [注意]此MaxHeap是從索引值0 開始編號節點
    
    將陣列的arr[0...n-1]看成是一個從0開始編號的MaxHeap
    Step1.對arr[0...n-1]做一次Heapify--->arr[0...n-1]變成MaxHeap
      swap(arr[0],arr[n-1])--->此時最大值已經放到arr[n-1]
    Step2.對arr[0...n-2]做Step1則又將最大值放到arr[n-2]
    以此類推...一直做到 對arr[0...1]做MaxHeap--->則將最大值放到arr[1]
    就不用再對arr[0...0]做MaxHeap了 因為本身就已經在適當的位置
*/
template <class T>
void heapSort3(T arr[], int n) {
    //先將最一開始的陣列做一次Heapify--->使陣列變成MaxHeap
    for (int i = ((n - 1) - 1) / 2; i >= 0; i--) {  //第一個非葉節點是(最後一個節點索引值-1)/2
        __shiftDown(arr, n, i);                     //對arr[0...n-1]中的arr[i]做shiftDown
    }

    //從arr[0...n-1]一直操作到arr[0...1]就好--->因為arr[0...0]不需要再做shiftDown--->因為只剩一個元素則代表排序
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);    //將最大值(arr[0])放到arr[i]中
        __shiftDown(arr, i, 0);  //對arr[0...i-1]的arr[0]做shiftDown
    }
}

int main() {
    int n = 300000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);
    int *arr5 = SortTestHelper::copyIntArray(arr, n);
    int *arr6 = SortTestHelper::copyIntArray(arr, n);
    int *arr7 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test Random Array" << endl;
    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("QuickSort2", quickSort2, arr2, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr3, n);
    SortTestHelper::testSort("QuickSortThreeWay", quickSortThreeWay, arr4, n);
    SortTestHelper::testSort("HeapSort", heapSort, arr5, n);
    SortTestHelper::testSort("HeapSort2", heapSort2, arr6, n);
    SortTestHelper::testSort("HeapSort3", heapSort3, arr7, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    int swapTimes = 100;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);
    arr7 = SortTestHelper::copyIntArray(arr, n);

    cout << endl;
    cout << "Test Nearly Ordered Array" << endl;
    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("QuickSort2", quickSort2, arr2, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr3, n);
    SortTestHelper::testSort("QuickSortThreeWay", quickSortThreeWay, arr4, n);
    SortTestHelper::testSort("HeapSort", heapSort, arr5, n);
    SortTestHelper::testSort("HeapSort2", heapSort2, arr6, n);
    SortTestHelper::testSort("HeapSort3", heapSort3, arr7, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    arr = SortTestHelper::generateRandomArray(n, 0, 10);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);
    arr7 = SortTestHelper::copyIntArray(arr, n);

    cout << endl;
    cout << "Test for random array with [0,10]" << endl;
    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("QuickSort2", quickSort2, arr2, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr3, n);
    SortTestHelper::testSort("QuickSortThreeWay", quickSortThreeWay, arr4, n);
    SortTestHelper::testSort("HeapSort", heapSort, arr5, n);
    SortTestHelper::testSort("HeapSort2", heapSort2, arr6, n);
    SortTestHelper::testSort("HeapSort3", heapSort3, arr7, n);

    return 0;
}