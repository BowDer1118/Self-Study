#ifndef LAZYPRIMEMST_H
#define LAZYPRIMEMST_H
#include <cassert>
#include <vector>

#include "Edge.h"
#include "MinHeap.h"
using namespace std;
//泛型Graph:Sparse Dense 泛型:Weight的 資料類型
template <class Graph, class Weight>
class LazyPrimMST {
private:
    Graph &G;                  //要製作Minimum Spanning Tree的圖
    MinHeap<Edge<Weight>> pq;  //Priority Queue用來儲存 可能是MST的邊 用來找 最小邊
    bool *marked;              //紀錄 節點是否被放到切分區
    vector<Edge<Weight>> mst;  // Minimum Spanning Tree的邊
    Weight mstWeight;          // Minimum Spanning Tree的 總權重

    //訪問的function
    void visit(int v) {
        //確保節點v 尚未是被標記的點
        assert(!marked[v]);

        marked[v] = true;
        class Graph::adjIterator adj(G, v);
        for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()) {
            //如果 與節點v相連的另一個節點沒有被marked--->此邊就是橫切邊Crossing Edge
            if (!marked[e->other(v)]) {
                //將此條邊insert進入Minheap
                pq.insert(*e);
            }
        }
    }

public:
    //以graph的邊數 初始化MinHeap的size
    LazyPrimMST(Graph &graph) : G(graph), pq(MinHeap<Edge<Weight>>(graph.E())) {
        marked = new bool[G.V()];

        //初始化所有的屬性(成員)
        for (int i = 0; i < G.V(); i++) {
            marked[i] = false;
        }
        mst.clear();
        mstWeight = 0;  //初始化mstWeight

        //Lazy Prim
        visit(0);  //默認先訪問節點0
        //Priority Queue不為空--->還有事情要做--->時間複雜度
        while (!pq.isEmpty()) {
            //獲取 當前pq中權重最小的值
            Edge<Weight> e = pq.extractMin();
            //判斷是否為橫切邊(因為每次加入的邊都是橫切邊 但是MST的節點越來越多 舊的橫切邊 有些就不是橫切邊了 因為兩邊的節點都是marked)
            if (marked[e.v()] == marked[e.w()]) {  //如果兩邊都是marked--->不是橫切邊--->不做事
                //Lazy Prim Lazy在這裡 沒有處理 那些不是橫切邊的邊
                continue;
            } else {  //將橫切邊push到mst中
                mst.push_back(e);
                //找到此橫切邊 尚未被marked的那個節點 將那個節點 標記為marked
                if (!marked[e.v()]) {  //如果此邊的 節點v 沒有被marked
                    //訪問新的被marked的節點
                    visit(e.v());
                } else {  //節點w沒有被marked
                    visit(e.w());
                }
            }
        }

        //計算總權重(將所有mst中的邊 的權重相加)
        for (int i = 0; i < mst.size(); i++) {
            mstWeight += mst[i].wt();
        }
    }
    ~LazyPrimMST() {
        delete[] marked;
    }

    //獲得MST的邊
    vector<Edge<Weight>> mstEdges() {
        return mst;
    }

    //獲得MST的權重總和
    Weight result() {
        return mstWeight;
    }
};
#endif