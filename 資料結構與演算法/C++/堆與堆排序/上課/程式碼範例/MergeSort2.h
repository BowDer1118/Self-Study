#ifndef MERGESORT_2
#define MERGESORT_2
using namespace std;

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
void __mergeSort2(T arr[], int l, int r) {  //T aux[] 傳遞臨時陣列
    if (r - l <= 15) {                      //如果陣列已經足夠小--->使用InsertionSort取代MergeSort--->速度更快
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
#endif