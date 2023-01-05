#ifndef DENSEGRAPH_H
#define DENSEGRAPH_H
#include <cassert>
#include <iostream>
#include <vector>

#include "Edge.h"
using namespace std;

/*
    Adjacency Matrix中的 addEdge(v,w)
    對於從v往w的邊 有做 是否存在的檢查 
    如果加入新的重複邊 新的會覆蓋掉舊的權重
*/

//使用鄰接矩陣(Adjacency Matrix) 表示 帶權重的稠密圖(Dense Graph)
template <class Weight>
class DenseGraph {
private:
    int n;          //節點(Vertex)
    int m;          //邊(Edge)
    bool directed;  //是否有向(有向圖or無向圖)
    //存放Edge Class的指標
    vector<vector<Edge<Weight> *> > g;  //二維陣列(使用vector實作)--->Adjacency Matrix

public:
    //傳入節點數n,是否有向 directed
    DenseGraph(int n, bool directed) {
        this->n = n;                //設立節點數
        this->m = 0;                //設立邊數--->預設為0
        this->directed = directed;  //是否有向
        //初始化Adjacency Matrix
        for (int i = 0; i < n; i++) {
            //在g加入vector 泛型為Edge型 有n個元素 每個元素都初始化為NULL--->因為之後要存放Edge Class的指標
            g.push_back(vector<Edge<Weight> *>(n, NULL));
        }
    }
    ~DenseGraph() {
        //釋放掉Adjacency Matrix中所有的Edge類指標
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] != NULL) {
                    delete g[i][j];
                }
            }
        }
    }
    //獲取節點數量
    int V() {
        return n;
    }
    //獲取邊的數量
    int E() {
        return m;
    }
    //在節點v與w之間 加入帶有權重的邊(有向:v--->w 無向:v<--->w)
    void addEdge(int v, int w, Weight weight) {
        //檢查邊界問題--->v和w是否存在
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        //檢查 從v往w節點之間 是否有邊--->有的話--->刪除舊的邊 用新的邊 覆蓋掉舊的
        if (hasEdge(v, w)) {
            //覆蓋權重
            delete g[v][w];
            if (!directed) {  //如果圖是無向圖
                //另一個方向也要覆蓋新的權重
                delete[] g[w][v];
            }
            //更新邊的數量
            m--;
        }

        //有向圖的狀態--->加入邊--->從v出發連接到w
        g[v][w] = new Edge<Weight>(v, w, weight);      //將邊new到存放g[v][w]--->從節點v往節點w產生邊
        if (!directed) {                               //無向圖的狀態
            g[w][v] = new Edge<Weight>(w, v, weight);  //對於w來說 也從節點w往節點v產生邊
        }
        m++;  //更新邊的數量
    }

    //檢查從w往w節點之間 是否有邊--->因為是直接索引到資料--->時間複雜度O(1)
    bool hasEdge(int v, int w) {
        //檢查邊界問題--->v和w是否存在
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        //如果存放在g[v][w]中的指標不為NULL 代表 有邊
        return g[v][w] != NULL;
    }

    // 显示图的信息
    void show() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //如果指標不為空--->邊存在
                if (g[i][j]) {
                    //調用g[i][j]中 Edge類 指標的wt()函數
                    cout << g[i][j]->wt() << "\t";
                } else {
                    cout << "NULL\t";
                }
            }
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

        Edge<Weight> *begin() {
            index = -1;  //代表尚未找到第一個元素(節點)
            //將找到的第一個節點的邊(一個Edge的指標) 當作起點回傳
            return next();
        }

        Edge<Weight> *next() {
            //開始掃描Row為v的 陣列(vector) 元素共有V個 從上次掃描到的元素的下一個人開始--->index++
            for (index += 1; index < G.V(); index++) {
                if (G.g[v][index]) {       //如果找到節點v的第index個元素有值(不是null)
                    return G.g[v][index];  //回傳 該Edge指標
                }
            }
            //找不到--->回空指標
            return NULL;
        }

        bool end() {
            //檢查是否越界
            return index >= G.V();
        }
    };
};

#endif