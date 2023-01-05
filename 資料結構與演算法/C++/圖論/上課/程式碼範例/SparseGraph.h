#ifndef SPARSEGRAPH
#define SPARSEGRAPH
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

/*
    Adjacency list中的 addEdge(v,w)
    在無向圖的模式下 有檢查v與w是否為同節點
    如果v與w是同節點 則無向圖 不會產生 自環邊(節點連結自己)
    但是有向圖會產生自環邊 因為沒有檢查

    還有Adjacency list 沒有檢查 平行邊(也就是檢查hasEdge)
    因為檢查所產生的Overhead是O(n)級別的
    因此Adjaceny list是允許平行邊的
    如果要去除平行邊 通常是 處理完整個圖之後 才做整理
*/

//使用Adjacency list 表示 稀疏圖(Sparse Graph)
class SparseGraph {
private:
    int n;                  //節點數
    int m;                  //邊數
    bool directed;          //是否有向(有向圖or無向圖)
    vector<vector<int>> g;  //Adjacency list--->使用vector實作
public:
    //傳入節點數量，有向圖或無向圖
    SparseGraph(int n, bool directed) {
        this->n = n;  //初始化節點
        this->m = 0;  //初始化邊
        this->directed = directed;
        for (int i = 0; i < n; i++) {
            //每個節點 都預設是空(沒有與其他節點相連)
            g.push_back(vector<int>());
        }
    }
    ~SparseGraph() {
    }
    //獲取節點數量
    int V() {
        return n;
    }
    //獲取邊的數量
    int E() {
        return m;
    }
    void addEdge(int v, int w) {
        //檢查v與w是否合法(沒有越界)
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);
        //有向圖--->從v出發往w之間 有一條邊
        g[v].push_back(w);

        //無向圖--->v往w有邊--->w往v也有邊(前提w與v不是同一個節點)
        if (v != w && !directed) {  //當v!=w才 讓w往v也有邊--->排除掉無向圖產生自環邊(自己連接自己)
            g[w].push_back(v);
        }

        m++;  //更新節點數量
    }

    //檢查v往w是否有邊--->因為要查找節點v紀錄的vector--->時間複雜度O(n)
    bool hasEdge(int v, int w) {
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);

        //檢查節點v中的vector 是否有紀錄與w相連
        for (int i = 0; i < g[v].size(); i++) {  //遍歷節點v的vector
            if (g[v][i] == w) {                  //如果有紀錄與w相連
                return true;
            }
        }
        //查無結果--->沒有與w相連
        return false;
    }

    // 显示图的信息
    void show() {
        for (int i = 0; i < n; i++) {
            cout << "vertex " << i << ":\t";
            for (int j = 0; j < g[i].size(); j++)
                cout << g[i][j] << "\t";
            cout << endl;
        }
    }

    //宣告一個內部類用來製作節點的iterator--->保證資料的安全 但又可以避免複製vector的overhead
    class adjIterator {
    public:
        SparseGraph &G;  //儲存要製作的圖(使用引用 避免資料的複製)
        int v;           //要製作的節點
        int index;       //紀錄當前遍歷到節點v中vector的索引位置
    public:
        //傳入 要製作迭代器的圖 與 該節點
        adjIterator(SparseGraph &graph, int v) : G(graph) {
            this->v = v;
            this->index = 0;  //初始化節點v中vector的索引位置
        }
        //迭代器的起點(節點v中vector的第一個元素 也就是第一個紀錄的節點)
        int begin() {
            if (G.g[v].size()) {   //檢查圖的節點v是否有元素--->有元素才返回
                index = 0;         //更新 當前索引位置
                return G.g[v][0];  //回傳該元素(也就是節點)
            }
            //沒有元素可以遍歷--->回傳-1
            return -1;
        }
        //當前vector中的下一個元素索引值
        int next() {
            index++;                      //更新 當前索引位置(到下一個位置)
            if (index < G.g[v].size()) {  //沒有越界--->代表下一個位置 是有元素的
                return G.g[v][index];     //回傳該元素(也就是節點)
            }
            return -1;  //沒有下一個元素--->回傳-1
        }

        bool end() {
            return index >= G.g[v].size();  //查看當前索引值是否在節點v中vector的size範圍內
        }
    };
};
#endif