#ifndef PATH
#define PATH
#include <cassert>
#include <stack>
using namespace std;

/*
    從節點0代號s往其他節點走 
    假設經過節點(1,2,3)分別代號為(a,b,c)節點
    
    from[0]=-1
    from[1]=-1 ---> 此路徑是從節點s過來(到k節點)
    from[2]=1 ---> 此路徑是從節點a過來(到b節點)
    from[3]=2 ---> 此路徑是從節點b過來(到c節點)

    推入stack會是 3 2 1
    拿出stack 路徑會是 1 2 3
    就正確了
*/

//用來尋找路徑 從節點s到任意其他點的路徑
template <class Graph>
class Path {
private:
    Graph &G;
    int s;          //從節點s(source)出發 往其他節點訪問(source)
    bool *visited;  //紀錄節點是否被訪問過
    int *from;      //用來記錄節點之間的路徑

    //對節點v做dfs
    void dfs(int v) {
        //代表節點v被訪問了
        visited[v] = true;
        //調用圖中節點v的iteraotr(因為還未確定泛型Graph是哪個Class因此無法分辨adjIterator--->使用typename或class宣告--->模板宣告法)
        class Graph::adjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); i = adj.next()) {
            //將 與節點v相連的 其他節點都進行dfs
            if (!visited[i]) {
                from[i] = v;  //要訪問的當前節點i 是從v節點過來的
                //標記完from後 才繼續dfs
                dfs(i);
            }
        }
    }

public:
    Path(Graph &graph, int s) : G(graph) {
        //檢查節點s的合法性
        assert(s >= 0 & s < G.V());

        visited = new bool[G.V()];
        from = new int[G.V()];
        for (int i = 0; i < G.V(); i++) {
            visited[i] = false;
            from[i] = -1;  //尚未開始訪問--->初始化路徑為-1
        }
        this->s = s;  //設定以s節點為出發點
        //從s開始dfs
        dfs(s);
    }
    ~Path() {
        delete[] visited;
        delete[] from;
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
};

#endif