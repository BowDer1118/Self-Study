#include <algorithm>
#include <iostream>
using namespace std;

void bubbleSort(int* array, int n) {
    while (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
            }
        }
        n--;
    }
}

void selectionSort(int* array, int n) {
    for (int i = 0; i < n; i++) {
        int min = array[i];
        int index;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < min) {
                min = array[j];
                index = j;
            }
        }
        swap(array[i], array[index]);
    }
}

void insertionSort(int* array, int n) {
    for (int i = 0; i < n; i++) {
        int current = array[i];
        int j;
        for (j = i; j > 0; j--) {
            if (array[j - 1] > current) {
                array[j] = array[j - 1];
            } else {
                break;
            }
        }
        array[j] = current;
    }
}

int main() {
    int arr[] = {1, 3, 2, 5, 4};
    insertionSort(arr, 5);
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}