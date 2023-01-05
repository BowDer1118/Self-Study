#ifndef QUICKSORT
#define QUICKSORT
using namespace std;

/*
    partition後的陣列會是
    arr[l]~arr[p-1]都小於arr[p]
    arr[p+1]~arr[r]都大於等於arr[p]

    注意:左半部都是"小於"，右半部則是"大於等於"
    代表其實這個版本的QuickSort在partition的時候 左右半邊是不平衡的
    因為等於arr[p]的值並未均勻散佈在左右半邊 而是都放在右半邊
*/

//對arr[l,r]做partition操作
//返回索引值p使得arr[l]~arr[p-1]都小於arr[p]且arr[p+1]~arr[r]都大於等於arr[p]
template <class T>
int __partition(T arr[], int l, int r) {
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
void __quickSort(T arr[], int l, int r) {
    if (l >= r) {  //當剩下一個或空的時候停止遞迴--->代表已排序或不需要再排序
        return;
    }

    //獲取當前陣列中間的元素
    /*
        此位置p就是partition後的結果
        也就是說 陣列會呈現
        arr[l]~arr[p-1]都小於arr[p]
        arr[p+1]~arr[r]都會大於等於arr[p]
    */
    int p = __partition(arr, l, r);
    //繼續快速排序左右半部的元素
    __quickSort(arr, l, p - 1);  //左半部:arr[l]~arr[p-1]
    __quickSort(arr, p + 1, r);  //右半部:arr[p+1]~arr[r]
}

template <class T>
void quickSort(T arr[], int n) {
    __quickSort(arr, 0, n - 1);
}
#endif