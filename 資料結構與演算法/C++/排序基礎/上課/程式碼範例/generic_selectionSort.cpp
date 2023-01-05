#include <algorithm>
#include <iostream>

#include "Student.h"
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

int main() {
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    selectionSort(a, 10);
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;

    float b[4] = {4.4, 3.3, 2.2, 1.1};
    selectionSort(b, 4);
    for (auto i : b) {
        cout << i << " ";
    }
    cout << endl;

    string c[4] = {"D", "C", "B", "A"};
    selectionSort(c, 4);
    for (auto i : c) {
        cout << i << " ";
    }
    cout << endl;

    Student s1("D", 90);
    Student s2("C", 100);
    Student s3("B", 95);
    Student s4("A", 95);
    Student d[4] = {s1, s2, s3, s4};

    selectionSort(d, 4);
    for (auto i : d) {
        cout << i;
    }

    return 0;
}