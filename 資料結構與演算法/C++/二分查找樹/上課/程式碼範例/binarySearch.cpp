#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/*
    [證明] (l+r)/2=mid 與 l+(r-l)/2=mid 相等
    假設 (l+r)/2=mid--->(l+r)=2*mid--->r=2*mid-l

    l+(r-l)/2=mid--->l+((2*mid-l)-l)/2=mid--->l+(2*mid-2*l)/2=mid
    l+(mid-l)=mid--->mid=mid--->兩者相等
*/

/*
    二分查找法，在排序好的陣列中查找target
    如果找到則返回，target在arr中的索引值(arr[?]=target)
    如果找不到則返回-1

    規則是先找到每次要查找區間arr[l...r]的中間值arr[mid]
    並判斷
    1.target==arr[mid]--->返回mid的索引值
    2.target<arr[mid]--->繼續查找arr[l...mid-1]
    3.target>arr[mid]--->繼續查找arr[mid+1...r]
*/
template <class T>
int binarySearch(T arr[], int n, T target) {
    // 在arr[l...r]之間 嘗試查找target--->arr[0...n-1]之間
    int l = 0, r = n - 1;
    while (l <= r) {  //當arr[l...r]還存在(不是空集合)--->因為l>r代表空集合
        //(l+r)如果都是INT_MAX(int的最大值)則相加會Overflow
        // int mid = (l + r) / 2;
        int mid = l + (r - l) / 2;  //不會Overflow
        if (arr[mid] == target) {   //找到target
            return mid;
        }
        if (target < arr[mid]) {  //target在arr[mid]的左邊
            //查找arr[l...mid-1]
            r = mid - 1;  //右邊界為mid-1
        } else {          //target在arr[mid]右邊
            //查找arr[mid+1...r]
            l = mid + 1;  //左邊界為mid+1
        }
    }
    //所有可能的區間都找完了 都沒有找到
    return -1;
}

int main() {
    int arr[] = {10, 1, 7, 2, 3, 8, 5};
    //對arr[0...6]排序
    sort(arr, arr + 7);  //sort arr[0...7)
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;

    int target = 5;
    int index = binarySearch(arr, 7, target);
    if (0 <= index && index <= 6) {
        cout << "Value: " << to_string(target) << " is in data[" << index << "]." << endl;
    } else {
        cout << "Can't find " << to_string(target) << "in arr." << endl;
    }
    return 0;
}