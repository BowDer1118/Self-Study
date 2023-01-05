#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

/*
    以parent來記錄每個元素的跟節點是誰(也就是 跟哪些人是同一群)

    如果arr[index]==parent[index]就代表 自己就是根節點
    反之arr[index]!=parent[index]就代表 與別人Union在一起了
*/

//以QuickUnion方法 實作UnionFind
class UnionFind {
private:
    int *parent;  //用來記錄每個元素的根結點是誰
    int count;

public:
    UnionFind(int count) {
        parent = new int[count];
        this->count = count;
        //每個元素的根節點都是自己(自己一群)
        for (int i = 0; i < count; i++) {
            parent[i] = i;
        }
    }
    ~UnionFind() {
        delete[] parent;
    }
    //查arr[p]的(群組)--->一直往p的根結點檢查p的parent等於自己--->找到根
    int find(int p) {
        assert(p >= 0 && p < count);
        while (p != parent[p]) {  //不是根結點--->往下個節點檢查
            p = parent[p];
        }
        //返回p的群組(根節點)
        return p;
    }
    //檢查兩者是否相連(同一群)
    bool isConnected(int p, int q) {
        //檢查兩者根 是否為同一個
        return find(p) == find(q);
    }
    //將p與q合併成同一群
    void unionElements(int p, int q) {
        //先找p與q的根
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot) {  //同一個根--->已經合併完
            return;
        } else {
            //兩者任一選一個，將根元素綁訂到另外一個的根元素
            parent[pRoot] = qRoot;
        }
    }
};

int main() {
    return 0;
}