#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
#include <cassert>
#include <queue>
#include <stack>
using namespace std;
//從節點s到每一個節點的最短距離
template <class Graph>
class ShortestPath {
private:
    Graph &G;
    int s;  //Source節點--->從此節點向外BFS
    bool *visited;
    int *from;
    int *ord;  //用來記錄從節點s到每個節點的最短路徑(長度)
public:
    ShortestPath(Graph &graph, int s) : G(graph) {
        assert(s >= 0 && s < graph.V());
        //配置動態記憶體
        visited = new bool[graph.V()];
        from = new int[graph.V()];
        ord = new int[graph.V()];

        //初始化visited from ord
        for (int i = 0; i < graph.V(); i++) {
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }
        this->s = s;

        //輔助BFS的Queue
        queue<int> q;

        //無向圖最短路徑算法
        q.push(s);          //先推入source 節點s
        visited[s] = true;  //更新成訪問過
        ord[s] = 0;         //紀錄節點s與節點s的距離

        //開始處理queue
        while (!q.empty()) {
            //獲取queue的第一個節點 並移出
            int v = q.front();
            q.pop();
            //開始遍歷 與節點v相連的節點
            typename Graph::adjIterator adj(G, v);
            for (int i = adj.begin(); !adj.end(); i = adj.next()) {
                if (!visited[i]) {        //如果節點i沒有被訪問過
                    q.push(i);            //將節點i推入queue
                    visited[i] = true;    //訪問過節點i
                    from[i] = v;          //記錄是從節點v過來節點i的
                    ord[i] = ord[v] + 1;  //節點i與節點s的距離是 (過來的節點v與節點s的距離+1)
                }
            }
        }
    }
    ~ShortestPath() {
        delete[] visited;
        delete[] from;
        delete[] ord;
    }

    //查看節點s到節點w是否有路徑
    bool hasPath(int w) {
        assert(w >= 0 && w < G.V());
        //查看有沒有訪問到w就知道 有沒有路徑存在s與w之間了
        return visited[w] == true;
    }
    //從節點s到節點w中間所經過的節點(也就是路徑)
    void path(int w, vector<int> &vec) {
        //因為當初在dfs是反正紀錄的 因此放入stack再拿出來 剛好就是正的紀錄
        stack<int> s;

        //從w往回走到s
        int p = w;         //從節點p往回走
        while (p != -1) {  //如果還沒回到s
            s.push(p);     //將此節點推入stack
            p = from[p];   //將p更新成 前一個節點
        }

        vec.clear();
        //將stack中的資料 push_back到vec中
        while (!s.empty()) {
            vec.push_back(s.top());  //將stack最上面的元素push_back到vec中
            s.pop();                 //移除stack最上面的元素
        }
    }

    //輸出 從節點s到節點w的路徑
    void showPath(int w) {
        vector<int> vec;
        path(w, vec);
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i == vec.size() - 1) {  //如果i是最後一個元素
                cout << endl;           //換行
            } else {
                cout << " -> ";
            }
        }
    }
    //取得節點s到節點w的最短路徑長度
    int length(int w) {
        assert(w >= 0 & w < G.V());
        return ord[w];
    }
};
#endif