#ifndef KRUSKAMST
#define KRUSKAMST
#include <vector>

#include "Edge.h"
#include "MinHeap.h"
#include "UF.h"
using namespace std;
template <class Graph, class Weight>
class KruskalMST {
private:
    vector<Edge<Weight>> mst;  //MST的邊
    Weight mstWeight;          //MST總權重
public:
    KruskalMST(Graph &graph) {
        //MinHeap中 要存放graph中的所有邊
        MinHeap<Edge<Weight>> pq(graph.E());

        //遍歷圖中的所有節點--->獲取graph所有的邊
        for (int i = 0; i < graph.V(); i++) {
            class Graph::adjIterator adj(graph, i);
            //每個節點 與 其他節點的所有邊
            for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()) {
                /*
                    注意:無向圖的邊是沒有方向性的
                    因此要避免重複加入

                    假設節點v與w 
                    會加入兩次 v-->w 和 w--->v

                    透過節點的大小來限制 只加入一條邊
                    這邊使用 v<w 才加入
                */
                if (e->v() < e->w()) {
                    pq.insert(*e);
                }
            }
        }

        //使用UnionFind來檢查是否形成環
        UnionFind uf(graph.V());  //要存放的個數:圖的節點數量

        //Kruskal算法
        //開始找MST的邊
        while (!pq.isEmpty() || mst.size() < graph.V() - 1) {  //因為MST的邊數 是圖的節點數量-1 所以可以提前停止
            Edge<Weight> e = pq.extractMin();
            //檢查是否形成環(如果左右兩端點都是被標記的頂點 就會形成環)
            if (uf.isConnected(e.v(), e.w())) {  //形成環
                continue;
            } else {
                mst.push_back(e);  //找到MST的邊
                uf.unionElements(e.v(), e.w());
            }
        }

        mstWeight = 0;
        for (int i = 0; i < mst.size(); i++) {
            mstWeight += mst[i].wt();
        }
    }

    ~KruskalMST() {
    }

    vector<Edge<Weight>> mstEdges() {
        return mst;
    }

    Weight result() {
        return mstWeight;
    }
};
#endif