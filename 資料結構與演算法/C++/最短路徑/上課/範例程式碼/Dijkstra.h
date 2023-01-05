#ifndef DIJKSTRA_A
#define DIJKSTRA_A
#include <stack>

#include "Edge.h"
#include "IndexMinHeap.h"
#include "ReadGraph.h"
#include "SparseGraph.h"
using namespace std;

template <class Graph, class Weight>
class Dijkstra {
private:
    Graph &G;
    int s;                        //單源的源Source(節點的編號)
    Weight *distTo;               //從節點S到每個其他節點的最短路徑權重值
    bool *marked;                 //紀錄是否被走訪
    vector<Edge<Weight> *> from;  //紀錄路徑
public:
    Dijkstra(Graph &graph, int s) : G(graph) {
        //初始化所有參數
        this->s = s;
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];
        for (int i = 0; i < G.V(); i++) {
            distTo[i] = Weight();  //調用權重的資料類型的基本Constructor--->int就是0
            marked[i] = false;
            from.push_back(NULL);
        }
        //用來記錄路徑權重的IndexMinHeap
        IndexMinHeap<Weight> ipq(G.V());

        //Dijkstra
        //從節點s開始
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s, s, Weight());
        marked[s] = true;
        ipq.insert(s, distTo[s]);  //節點編號 與節點權重
        while (!ipq.isEmpty()) {
            //獲取離節點s最近的節點
            int v = ipq.extractMinIndex();

            //distTo[v]就是節點s到節點v的最短距離
            marked[v] = true;

            //訪問節點v的所有臨邊 並做鬆弛操作
            class Graph::adjIterator adj(G, v);
            for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()) {
                int w = e->other(v);  //獲得與節點v相連的另一個節點
                if (!marked[w]) {
                    if (from[w] == NULL || distTo[v] + e->wt() < distTo[w]) {  //判斷此節點是否被訪問過 或 被訪問過的總權重是多少(做判斷)
                        //透過節點v到w權重會更小--->更新from與distTo
                        distTo[w] = distTo[v] + e->wt();
                        from[w] = e;

                        //更新最小索引堆
                        if (ipq.contain(w)) {  //如果存在過--->更新新的權重
                            ipq.change(w, distTo[w]);
                        } else {
                            ipq.insert(w, distTo[w]);  //加入節點w
                        }
                    }
                }
            }
        }
    }
    ~Dijkstra() {
        delete[] distTo;
        delete[] marked;
    }

    //查節點s到節點w的最短路徑權重
    Weight shortestPathTo(int w) {
        return distTo[w];
    }
    //是否能從節點s到達節點w
    bool hasPathTo(int w) {
        return marked[w];
    }

    //將 從節點s到節點w的最短路徑 的邊存進傳入的vector中
    void shortestPath(int w, vector<Edge<Weight>> &vec) {
        stack<Edge<Weight> *> s;
        Edge<Weight> *e = from[w];

        //從w邊往回推
        while (e->v() != e->w()) {
            s.push(e);
            e = from[e->v()];
        }

        //將路徑存到vec中
        while (!s.empty()) {
            e = s.top();
            vec.push_back(*e);
            s.pop();
        }
    }

    //將從節點s到節點w的路徑輸出
    void showPath(int w) {
        vector<Edge<Weight>> vec;
        shortestPath(w, vec);
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].v() << " -> ";
            if (i == vec.size() - 1) {
                cout << vec[i].w() << endl;
            }
        }
    }
};
#endif