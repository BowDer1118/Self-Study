#ifndef MERGESORTBT2
#define MERGESORTBT2
using namespace std;
#include "MergeSort.h"

//優化mergeSortBU
template <class T>
void mergeSortBU2(T arr[], int n) {
    //控制每次選中的元素個數做處理--->1,2,4,8,16....
    for (int sz = 1; sz <= n; sz += sz) {
        //每輪要merge的陣列起始索引值--->假如今天一次看2個元素--->每輪的陣列起始值為arr[0],arr[4],arr[8]...
        for (int i = 0; i < n; i += sz + sz) {
            /*
                處理arr[i]~arr[i+2*sz-1]--->假如今天看2個元素--->處理arr[0]~arr[3]
                mid是arr[i+sz-1]
                左半邊陣列為arr[i]~arr[i+sz-1]--->arr[0]~arr[1]
                右半邊鎮列為arr[(i+sz-1)+1]~arr[i+sz+sz-1]--->arr[2]~arr[3]
            */
            if (sz <= 16) {  //陣列長度較小--->使用InsertionSort效率較好
                insertionSort(arr, i, min(i + sz + sz - 1, n - 1));
            } else {
                //但是i+2*sz-1可能會超過陣列的總長度--->看陣列總長度或者每輪抓取元素 誰比較小
                __merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
            }
        }
    }
}
#endif