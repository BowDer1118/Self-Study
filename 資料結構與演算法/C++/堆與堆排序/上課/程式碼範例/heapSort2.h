#ifndef HEAPSORT2
#define HEAPSORT2
#include "MaxHeap.h"
using namespace std;

//使用heapify方式進行Sort
template <class T>
void heapSort2(T arr[], int n) {
    //使用第二種構造函數創造maxHeap--->即使用heapify方式建構maxHeap
    MaxHeap<T> maxHeap(arr, n);

    //從後往前，將每輪MaxHeap中的最大值放到陣列中--->完成排序
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = maxHeap.extactMax();
    }
}
#endif