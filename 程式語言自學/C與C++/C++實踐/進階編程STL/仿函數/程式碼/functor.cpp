#include <algorithm>
#include <iostream>
using namespace std;

//C++ inline function template 內連函數模板
template <class T>
inline bool mySort(T a, T b) {
    return a > b;  //降序
}

//C++ inline function template 內連函數模板
template <class T>
inline void display(T value) {
    cout << value << " ";
}

//C++ functor template仿函數模板
template <class T>
struct sortFunctor {
    inline bool operator()(T a, T b) {
        return a > b;  //降序
    }
};

template <class T>
struct displayFunctor {
    inline void operator()(T value) {
        cout << value << " ";
    }
};

int main() {
    /*
        使用sort排序陣列
        傳入前閉後開的記憶體區段 默認是升序(小到大)
        可額外傳入一個function或functor來指定排序過程 
        如果是泛型 則要標記出泛型的資料種類
    */
    cout << "Use function template design" << endl;
    int arr[] = {4, 3, 2, 1, 7};

    for_each(arr, arr + 5, display<int>);
    cout << endl;

    sort(arr, arr + 5, mySort<int>);

    for_each(arr, arr + 5, display<int>);
    cout << endl;
    cout << endl;

    cout << "Use functor template design" << endl;
    int arr2[] = {4, 3, 2, 1, 7};
    for_each(arr2, arr2 + 5, displayFunctor<int>());
    cout << endl;

    sort(arr2, arr2 + 5, sortFunctor<int>());

    for_each(arr2, arr2 + 5, displayFunctor<int>());
    cout << endl;

    return 0;
}