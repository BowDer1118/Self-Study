#ifndef DENSEGRAPH_H
#define DENSEGRAPH_H
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/*
    Adjacency Matrix中的 addEdge(v,w)
    對於從v往w的邊 有做 是否存在的檢查 
    因此會 自然排除掉 平行邊的狀況(也就是 不會有多個邊)
*/

//使用鄰接矩陣(Adjacency Matrix) 表示 稠密圖(Dense Graph)
class DenseGraph {
private:
    int n;                   //節點(Vertex)
    int m;                   //邊(Edge)
    bool directed;           //是否有向(有向圖or無向圖)
    vector<vector<bool>> g;  //二維陣列(使用vector實作)--->Adjacency Matrix

public:
    //傳入節點數n,是否有向 directed
    DenseGraph(int n, bool directed) {
        this->n = n;                //設立節點數
        this->m = 0;                //設立邊數--->預設為0
        this->directed = directed;  //是否有向
        //初始化Adjacency Matrix
        for (int i = 0; i < n; i++) {
            //在g加入vector 泛型為bool型 有n個元素 每個元素都初始化為false
            g.push_back(vector<bool>(n, false));
        }
    }
    ~DenseGraph() {
    }
    //獲取節點數量
    int V() {
        return n;
    }
    //獲取邊的數量
    int E() {
        return m;
    }
    //在節點v與w之間 加入邊(有向:v--->w 無向:v<--->w)
    void addEdge(int v, int w) {
        //檢查邊界問題--->v和w是否存在
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        //檢查 從v往w節點之間 是否有邊
        if (hasEdge(v, w)) {
            //有邊--->不進行addEdge--->不可能出現平行邊(v與w之間有多條邊)
            return;
        }

        //有向圖的狀態--->加入邊--->從v出發連接到w
        g[v][w] = true;      //對於v來說 將g[v][w]設為true--->代表從v有邊連接到w
        if (!directed) {     //無向圖的狀態
            g[w][v] = true;  //對於w來說 g[v][w]=true--->g[w][v]也要是true (因為無向邊可以看做雙向)
        }
        m++;  //更新邊的數量
    }

    //檢查從w往w節點之間 是否有邊--->因為是直接索引到資料--->時間複雜度O(1)
    bool hasEdge(int v, int w) {
        //檢查邊界問題--->v和w是否存在
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        return g[v][w];
    }

    // 显示图的信息
    void show() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << g[i][j] << "\t";
            cout << endl;
        }
    }

    //宣告一個內部類用來製作節點的iterator--->保證資料的安全 但又可以避免複製vector的overhead
    class adjIterator {
    private:
        DenseGraph &G;  //圖
        int v;          //節點
        int index;      //掃描到Row:v中的第index Column
    public:
        //傳入 圖與 要製作iterator的節點
        adjIterator(DenseGraph &graph, int v) : G(graph) {
            this->v = v;
            this->index = -1;  //初始化為 尚未開始掃描
        }

        int begin() {
            index = -1;  //代表尚未找到第一個元素(節點)
            //將找到的第一個節點索引值 當作起點回傳
            return next();
        }

        int next() {
            //開始掃描Row為v的 陣列(vector) 元素共有V個 從上次掃描到的元素的下一個人開始--->index++
            for (index += 1; index < G.V(); index++) {
                if (G.g[v][index]) {  //如果找到節點v的第index個元素為true
                    return index;     //回傳 元素索引值(節點)
                }
            }
            //找不到--->回傳索引值為-1
            return -1;
        }

        bool end() {
            //檢查是否越界
            return index >= G.V();
        }
    };
};

#endif