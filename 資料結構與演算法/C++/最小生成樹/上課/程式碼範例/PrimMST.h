#ifndef PRIMMST
#define PRIMMST
#include <vector>

#include "Edge.h"
#include "IndexMinHeap.h"
using namespace std;

template <class Graph, class Weight>
class PrimMST {
private:
    Graph &G;
    IndexMinHeap<Weight> ipq;       //使用IndexMinHeap模擬 IndexPriorityQueue--->只存 每個橫切邊的"權重"
    vector<Edge<Weight> *> edgeTo;  //存MST 每個橫切邊的 邊
    bool *marked;
    vector<Edge<Weight>> mst;  //用來存 MST 的邊
    Weight mstWeight;          //用來存 MST的總權重
    //從節點v開始向外找橫切邊
    void visit(int v) {
        assert(!marked[v]);
        marked[v] = true;

        class Graph::adjIterator adj(G, v);
        for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()) {
            //獲取此邊的另一個頂點
            int w = e->other(v);
            if (!marked[w]) {      //如果此邊是橫切邊(因為w還未被marked)
                if (!edgeTo[w]) {  //查看是否有找到過(是否為NULL) 此橫切邊
                    //沒找到過
                    edgeTo[w] = e;                       //紀錄往節點w的橫切邊
                    ipq.insert(w, e->wt());              //傳入節點索引值與該邊的權重
                } else if (e->wt() < edgeTo[w]->wt()) {  //如果存在而且 當前的橫切邊 權重更小
                    //更新與節點w的橫切邊權重(等於是用新的取代舊的)
                    edgeTo[w] = e;           //使用當前的橫切邊取代舊的
                    ipq.change(w, e->wt());  //更新ipq中的值
                }
            }
        }
    }

public:
    PrimMST(Graph &graph) : G(graph), ipq(IndexMinHeap<Weight>(graph.V())) {
        marked = new bool[G.V()];
        //只需要初始化V個元素就好(最多就是全部節點)
        for (int i = 0; i < G.V(); i++) {
            marked[i] = false;
            edgeTo.push_back(NULL);
        }
        mst.clear();

        //Prim算法
        visit(0);
        //只要ipq中還有橫切邊要考慮
        while (!ipq.isEmpty()) {
            //取出最小權重的邊的另一端節點
            int v = ipq.extractMinIndex();
            //確保該邊存在
            assert(edgeTo[v]);
            //將此邊加入MST中
            mst.push_back(*edgeTo[v]);
            visit(v);
        }

        //計算總權重
        mstWeight = 0;
        for (int i = 0; i < mst.size(); i++) {
            mstWeight += mst[i].wt();
        }
    }
    ~PrimMST() {
        delete[] marked;
    }

    //取得MST的所有邊
    vector<Edge<Weight>> mstEdges() {
        return mst;
    }

    //取得MST總權重
    Weight result() {
        return mstWeight;
    }
};

#endif