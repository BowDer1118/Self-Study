
#include <algorithm>
#include <iostream>

#include "DoubleQuickSort.h"
#include "MaxHeap.h"
#include "MergeSort2.h"
#include "QuickSortThreeWay.h"
#include "SortTestHelper.h"
using namespace std;

//使用MaxHeap結構進行Sort
template <class T>
void heapSort(T arr[], int n) {
    MaxHeap<T> maxHeap(n);
    //將arr陣列中的元素 一次一個的insert進入MaxHeap
    for (int i = 0; i < n; i++) {
        maxHeap.insert(arr[i]);
    }

    //從後往前，將每輪MaxHeap中的最大值放到陣列中--->完成排序
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = maxHeap.extactMax();
    }
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
    SortTestHelper::testSort("QuickSort2", quickSort2, arr2, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr3, n);
    SortTestHelper::testSort("QuickSortThreeWay", quickSortThreeWay, arr4, n);
    SortTestHelper::testSort("HeapSort", heapSort, arr5, n);

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
    SortTestHelper::testSort("QuickSort2", quickSort2, arr2, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr3, n);
    SortTestHelper::testSort("QuickSortThreeWay", quickSortThreeWay, arr4, n);
    SortTestHelper::testSort("HeapSort", heapSort, arr5, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    arr = SortTestHelper::generateRandomArray(n, 0, 10);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);

    cout << endl;
    cout << "Test for random array with [0,10]" << endl;
    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("QuickSort2", quickSort2, arr2, n);
    SortTestHelper::testSort("DoubleQuickSort", doubleQuickSort, arr3, n);
    SortTestHelper::testSort("QuickSortThreeWay", quickSortThreeWay, arr4, n);
    SortTestHelper::testSort("HeapSort", heapSort, arr5, n);

    return 0;
}