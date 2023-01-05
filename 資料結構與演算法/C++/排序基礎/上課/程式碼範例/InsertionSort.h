#ifndef INSERTION_SORT
#define INSERTION_SORT
using namespace std;
//insertionSort_v1
template <class T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {  //從arr[1]開始排序(因為arr[0]其實相當於插入完畢了--->只有一個位置可以插--->已經排序完成了)
        //開始尋找arr[i]合適的插入位置--->在arr[0]~arr[i]的位置中選一個位置放入
        for (int j = i; j > 0; j--) {      //j>0的原因是因為將arr[j]與arr[j-1]做比較，所以最後一次比較j=1是比較arr[0]與arr[1]
            if (arr[j] < arr[j - 1]) {     //如果前面大後面小
                swap(arr[j], arr[j - 1]);  //交換成 前面小後面大
            } else {                       //如果前面都是排序完成(小到大)--->可以不必再比較了--->前面都已經是小到大了
                break;
            }
        }
    }
}
#endif