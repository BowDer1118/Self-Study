#ifndef HEAPSORT
#define HEAPSORT
#include "MaxHeap.h"
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
#endif