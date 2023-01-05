#ifndef QUICKSORTTHREEWAY
#define QUICKSORTTHREEWAY
#include "DoubleQuickSort.h"
using namespace std;

/*
    處理三路快速排序arr[l...r]
    將arr[l...r]分成 小於v 等於v 大於v 的三部分
    之後對 小於v 與 大於 v 繼續三路快排
*/
template <class T>
void __quickSortThreeWay(T arr[], int l, int r) {
    if ((r - l + 1) <= 16) {  //優化:陣列夠小--->使用InsertionSort較快
        insertionSort(arr, l, r);
        return;
    }

    /*
        建立參考點lt,gt
        lt代表小於v的最後一個元素--->設定lt從l開始--->預設是空集合
        gt代表大於v的第一個元素--->設定gt從(r+1)開始--->預設是空集合

        使得arr陣列呈現
        arr[l...lt-1]都是 小於v
        arr[lt...gt-1]都是 等於v
        arr[gt...r]都是大於v

        設定要開始遍歷的位置
        i=(l+1)從第二個元素(arr[l+1])開始向後訪問--->arr[l]是參考點不用訪問
        當i與gt相遇代表整個陣列都訪問過了

        規則是
        arr[i]代表當前要被分類得元素
            1.如果arr[i]<v則與arr[lt+1]的位置交換，並更新lt與i(因為此時的arr[i]是等於v的，或者說分類過了)
            2.如果arr[i]==v則不用做任何處理(因為等於v的元素被夾在arr[lt+1]~arr[i]之間)
            3.如果arr[i]>v則與arr[gt-1]的位置交換，並更新gt的位置，不用更新i(因為交換後的arr[i]是arr[gt-1]是還沒被分類的元素)
        直到i與gt相遇代表所有元素都被訪問過--->分類完成
    */
    swap(arr[l], arr[rand() % (r - l + 1) + l]);  //優化:隨機化快排
    T v = arr[l];                                 //標定參考元素(第一個元素)
    int lt = l;                                   //小於v的最後一個元素位置
    int gt = r + 1;                               //大於v的第一個元素

    int i = l + 1;  //開始遍歷的起點

    while (i < gt) {  //當i還未碰上gt--->開始對arr[i]做分類
        if (arr[i] < v) {
            swap(arr[i], arr[lt + 1]);  //與arr[lt+1]交換位置
            lt++;                       //更新lt--->維持lt代表小於v的最後一個元素位置
            i++;                        //往下一個元素訪問
        } else if (arr[i] > v) {
            swap(arr[i], arr[gt - 1]);  //與arr[gt-1]交換位置
            gt--;                       //更新gt--->維持gt代表大於v的第一個元素位置
            //不需要i++因為交換後的arr[i]是arr[gt-1]是還未被處理的元素
        } else {  //與v相等--->不須做任何處理 因為等於v的元素被夾在arr[lt+1]~arr[i]當中
            i++;  //繼續往下訪問
        }
    }

    /*
        分類完畢--->將參考點arr[l]放到正確的位置
        此時lt代表最後一個小於v的位置
        將參考點與arr[lt]交換
        使得
        arr[l...lt-1]都是小於v
        arr[lt...gt-1]都是等於v
        arr[gt...r]都是大於v

        思考勘誤:當分類完畢以下三者的關係
        arr[lt-1] 小於v的倒數第二個元素 
        arr[lt]   小於v的最後一個元素
        arr[lt+1] 等於v的第一個元素
        此時應該將arr[l](參考點)與誰做swap能使得上面的條件成立呢?
        ----應該與arr[lt]交換!----
        使得
        arr[lt-1] 成為小於v的最後一個元素
        arr[lt]  成為等於v的第一個元素
        arr[lt+1] 成為等於v的第二個元素
    */
    swap(arr[l], arr[lt]);
    __quickSortThreeWay(arr, l, lt - 1);  //排序小於v的部分(arr[l...lt-1])
    __quickSortThreeWay(arr, gt, r);      //排序大於v的部分(arr[gt...r])
}

template <class T>
void quickSortThreeWay(T arr[], int n) {
    srand(time(NULL));  //用來給隨機化選取元素優化用的隨機種子碼
    __quickSortThreeWay(arr, 0, n - 1);
}
#endif