#ifndef SELECTION_SORT
#define SELECTION_SORT
using namespace std;

//Generic template
template <class T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n; i++) {  //循環陣列--->代表arr[i]的index
        //尋找[i,n)區間的最小值-->arr[i]~arr[n-1]
        int minIndex = i;                  //最小值的index
        for (int j = i + 1; j < n; j++) {  //j從當前位置的下一個位置開始找--->當前在arr[i]就從arr[i+1]位置開始找最小值
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        //將最小值的元素與當前位置交換
        swap(arr[i], arr[minIndex]);
    }
}
#endif