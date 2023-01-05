#include <algorithm>
#include <iostream>

#include "InsertionSort2.h"
#include "SortTestHelper.h"
using namespace std;

template <class T>
void __merge(T arr[], int l, int mid, int r) {
    //假設要處理arr[2]~arr[5]--->共有(5-2+1)個元素
    T aux[r - l + 1];  //儲存左右陣列的臨時空間

    for (int i = l; i <= r; i++) {  //儲存arr[l,r]到aux中
        //arr從l開始aux從0開始--->有l個位移量
        aux[i - l] = arr[i];
    }

    /*
        標記前半與後半陣列中的第一個元素
        前半部:arr[l]~arr[mid]--->第一個元素是arr[l]
        後半部:arr[mid+1]~arr[r]--->第一個元素是mid+1
    */
    int i = l, j = mid + 1;
    //循環傳入的陣列索引--->開始決定arr[k]應該放誰
    for (int k = l; k <= r; k++) {
        /*
        如果兩個陣列都還有元素也就是說
        i沒有大於mid且j沒有大於r
        則兩邊陣列中第一個元素比大小(比較arr[i],arr[j])
        取比較小的值存入arr[k]並將該邊的陣列第一個人向後指(索引值++的意思)--->因為被消耗掉拿去填補arr[k]了
        如果有一邊的陣列已經取光了
        則只要一直放另一邊的陣列就好
        */
        if (i > mid) {                         //左邊陣列被取光
            arr[k] = aux[j - l];               //放右邊陣列的元素
            j++;                               //標記右邊陣列下一個元素當作陣列的第一個元素
        } else if (j > r) {                    //右邊陣列被取光
            arr[k] = aux[i - l];               //放右邊陣列
            i++;                               //標記左邊陣列下一個元素當作陣列的第一個元素
        } else if (aux[i - l] < aux[j - l]) {  //左邊比右邊小--->放左邊陣列的元素
            arr[k] = aux[i - l];
            i++;
        } else {  //左邊比右邊大--->放右邊陣列的元素
            arr[k] = aux[j - l];
            j++;
        }
    }
}

template <class T>
void __mergeSort(T arr[], int l, int r) {  //對arr[l,r]做排序也就是arr[l]~arr[r]都包含
    if (l >= r) {                          //只剩一個元素或空(就不用繼續切分了)--->一個元素代表已經有序，空代表遞迴到最底
        return;
    }

    /*
        前半段排序的陣列是arr[l]~arr[mid]
        後半段排序的陣列是arr[mid+1]~arr[r]
        都是前閉後閉區間也就是
        [l,mid]與[mid+1,r]

        假設對arr[0]~arr[1]做__mergeSort
        mid=(0+1)/2=0
        前半部為arr[0]~arr[0]--->1個元素
        後半部為arr[1],arr[1]--->1個元素
        對arr[0]~arr[0]與arr[1]~arr[1]做__merge

        假設對arr[0]~arr[2]做__mergeSort
        mid=(0+2)/2=1
        前半部為arr[0]~arr[1]--->2個元素--->繼續mergeSort
        後半部為arr[2],arr[2]--->1個元素--->l=r--->return
        對arr[0]~arr[1]與arr[2]~arr[2]做__merge
    */
    int mid = (l + r) / 2;         //最中間的元素
    __mergeSort(arr, l, mid);      //對前半部繼續切割
    __mergeSort(arr, mid + 1, r);  //對後半部繼續切割
    __merge(arr, l, mid, r);       //合併左右半部
}

//MergeSort v1
template <class T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n - 1);  //對arr[0]~arr[n-1](都包含)做排序
}

//InsertionSort for MergeSort v2
template <class T>
void insertionSort(T arr[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        T e = arr[i];
        int j;
        for (j = i; j > l; j--) {
            if (arr[j - 1] > e) {
                arr[j] = arr[j - 1];
            } else {
                break;
            }
        }
        arr[j] = e;
    }
}

//Same as __merge,this version just a practice
template <class T>
void __merge2(T arr[], int l, int mid, int r) {
    T aux[r - l + 1];
    for (int i = l; i <= r; i++) {
        aux[i - l] = arr[i];
    }

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = aux[j - l];
            j++;
        } else if (j > r) {
            arr[k] = aux[i - l];
            i++;
        } else if (aux[i - l] < aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        } else {
            arr[k] = aux[j - l];
            j++;
        }
    }
}

template <class T>
void __mergeSort2(T arr[], int l, int r) {
    if (r - l <= 15) {  //如果陣列已經足夠小--->使用InsertionSort取代MergeSort--->速度更快
        insertionSort(arr, l, r);
        return;
    }

    int mid = (l + r) / 2;
    __mergeSort2(arr, l, mid);
    __mergeSort2(arr, mid + 1, r);
    /*
        如果左半邊最後一個元素(arr[mid])>右半邊第一個元素(arr[mid+1])才需要merge
        因為 如果左半邊最後一個元素<右半邊第一個元素 其實就代表 此陣列已經是排序完了 不需要merge操作
    */
    if (arr[mid] > arr[mid + 1]) {
        __merge2(arr, l, mid, r);
    }
}

//MergeSort v2
template <class T>
void mergeSort2(T arr[], int n) {
    __mergeSort2(arr, 0, n - 1);
}

int main() {
    int n = 100000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, 3);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test Random Array" << endl;
    SortTestHelper::testSort("InsertionSort2", insertionSort2, arr1, n);
    SortTestHelper::testSort("MergeSort", mergeSort, arr2, n);
    SortTestHelper::testSort("MergeSort2", mergeSort2, arr3, n);

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
    SortTestHelper::testSort("InsertionSort2", insertionSort2, arr1, n);
    SortTestHelper::testSort("MergeSort", mergeSort, arr2, n);
    SortTestHelper::testSort("MergeSort2", mergeSort2, arr3, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    return 0;
}