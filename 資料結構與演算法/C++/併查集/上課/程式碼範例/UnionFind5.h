#ifndef UNIONFIND5
#define UNIONFIND5
#include <cassert>
using namespace std;
namespace UF5 {
/*
    以parent來記錄每個元素的跟節點是誰(也就是 跟哪些人是同一群)

    如果arr[index]==parent[index]就代表 自己就是根節點
    反之arr[index]!=parent[index]就代表 與別人Union在一起了

    使用rank來紀錄每個根節點的樹高
    rank[i]=5 代表以i為根的群集 樹高是5
    
    讓 層數少的群體 往 層數多的群體 合併 
    會讓樹高較低
*/

//使用遞迴的方式Path Compression優化QuickUnion的實作
class UnionFind {
private:
    int *parent;  //用來記錄每個元素的根結點是誰
    int *rank;    //用來記錄rank[i]以i為根的群集 樹的高度是多少
    int count;

public:
    UnionFind(int count) {
        parent = new int[count];
        rank = new int[count];
        this->count = count;
        //每個元素的根節點都是自己(自己一群)
        for (int i = 0; i < count; i++) {
            parent[i] = i;
            rank[i] = 1;  //所有元素都以自己為根(樹高只有一層)
        }
    }
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
    //查arr[p]的(群組)--->Path Compression
    int find(int p) {
        assert(p >= 0 && p < count);
        /*
            使用遞迴的方式做Path Compression
        */
        if (p != parent[p]) {  //不是根結點
            //遞迴往上找 直到找到根
            parent[p] = find(parent[p]);  //就去找上層的parent[p]直到
        }
        //回傳p的根節點--->直到根節點
        return parent[p];
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
                層數少的往層數多的合併
            */
            if (rank[pRoot] < rank[qRoot]) {  //q的群集樹高較高
                parent[pRoot] = qRoot;        //將pRoot連接到qRoot上
                /*
                    合併後 樹的高度 最多也就是rank[qRoot]
                    也就是說 樹高 最多 等於rank[qRoot]
                    不會超過rank[qRoot] 因此不用維護rank[qRoot]
                */
            } else if (rank[qRoot] < rank[pRoot]) {  //p的樹高較高
                parent[qRoot] = pRoot;
            } else {                    //當樹高相等時--->誰向誰合併都沒差
                parent[pRoot] = qRoot;  //在這裡是讓pRoot連接到qRoot中
                rank[qRoot] += 1;       //因為p往q合併 因此q的層數會多一層(可以自己模擬看看 就知道為什麼會多一層)
            }
        }
    }
};
};  // namespace UF5
#endif