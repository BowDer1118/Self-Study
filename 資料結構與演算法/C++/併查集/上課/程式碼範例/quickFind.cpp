#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

/*
    QuickFind方法

    資料陣列arr 0 1 2 3 
    資料的id    0 1 0 1 (UnionFind Class紀錄的內容)

    透過索引值 來查找 對應的id(集合)
*/

//使用QuickFind方法實作 UnionFind
class UnionFind {
private:
    int *id;    //用來表示資料
    int count;  //此結構有多少元素

public:
    UnionFind(int n) {  //傳入要表示多少個元素
        count = n;
        id = new int[n];
        //讓每個元素的id都不同(沒有任何元素有連結)
        for (int i = 0; i < n; i++) {
            //也就是arr[i]的id是i
            id[i] = i;
        }
    }

    ~UnionFind() {
        delete[] id;
    }

    //查找arr[p]的id
    int find(int p) {
        //id是從0...count-1
        assert(p >= 0 && p < count);
        return id[p];
    }

    //查找元素arr[p]與元素arr[q]是否有關連
    bool isConnected(int p, int q) {
        //如果有關聯則id值會相同
        return find(p) == find(q);
    }

    //合併arr[p]與arr[q]兩類
    void unionElements(int p, int q) {
        int pID = find(p);
        int qID = find(q);

        if (pID == qID) {  //兩個元素id相等--->已經Union再一起
            return;
        }
        //掃描所有元素
        for (int i = 0; i < count; i++) {
            //將id為p的元素都改成id為q
            if (id[i] == pID) {
                id[i] = qID;
            }
        }
    }
};

int main() {
    return 0;
}