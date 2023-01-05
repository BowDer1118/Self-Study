#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

/*
    以parent來記錄每個元素的跟節點是誰(也就是 跟哪些人是同一群)

    如果arr[index]==parent[index]就代表 自己就是根節點
    反之arr[index]!=parent[index]就代表 與別人Union在一起了

    使用sz來紀錄每個根節點擁有的元素個數

    如果sz[index]=5 則代表 以index為根的群組 總共有5個元素

    讓 元素少的群體 往 元素多的群體 合併 產生的樹高 能夠較低
*/

//優化QuickUnion的實作
class UnionFind {
private:
    int *parent;  //用來記錄每個元素的根結點是誰
    int *sz;      //用來記錄sz[i]以i為根的個數(可以理解為 群組中包含的個數)
    int count;

public:
    UnionFind(int count) {
        parent = new int[count];
        sz = new int[count];
        this->count = count;
        //每個元素的根節點都是自己(自己一群)
        for (int i = 0; i < count; i++) {
            parent[i] = i;
            sz[i] = 1;  //所有元素都以自己為根(只有一個元素)
        }
    }
    ~UnionFind() {
        delete[] parent;
        delete[] sz;
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
            /*
                盡量保持樹的高度--->不要太高
                數量少的群組往數量多的群組合併
            */
            if (sz[pRoot] < sz[qRoot]) {  //q的群組元素較多
                parent[pRoot] = qRoot;    //將pRoot連接到qRoot上
                sz[qRoot] += sz[pRoot];   //更新qRoot的群組個數--->因為p往q上接 因此要更新q群組中的元素個數(要加上p群組的元素個數)
            } else {                      //p的群組元素較多
                parent[qRoot] = pRoot;
                sz[pRoot] += sz[qRoot];
            }
        }
    }
};

int main() {
    return 0;
}