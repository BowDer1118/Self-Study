#ifndef COMPONENT
#define COMPONENT
using namespace std;

//求圖的連通分量(Graph Component)
template <class Graph>
class Component {
private:
    Graph &G;       //圖的資訊
    bool *visited;  //用來記錄 所有節點是否被遍歷
    int ccount;     //紀錄連通分量--->也就是紀錄一個圖 有多少個 互不連接的子圖
    int *id;        //用來記錄 所有節點 分布在哪些子圖

    //對節點v做dfs
    void dfs(int v) {
        //代表節點v被訪問了
        visited[v] = true;
        //讓此子圖的所有節點的id值都是ccount(因為每次呼叫dfs時的ccount都是不一樣的 可以直接用ccount當作子圖的id)
        id[v] = ccount;
        //調用圖中節點v的iteraotr(因為還未確定泛型Graph是哪個Class因此無法分辨adjIterator--->使用typename或class宣告--->模板宣告法)
        class Graph::adjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); i = adj.next()) {
            //將 與節點v相連的 其他節點都進行dfs
            if (!visited[i]) {
                dfs(i);
            }
        }
    }

public:
    Component(Graph &graph) : G(graph) {
        //visited陣列大小為 圖的節點總數
        visited = new bool[G.V()];
        //id陣列大小為 圖的節點總數(因為最多就是每個節點 自己一個子圖)
        id = new int[G.V()];

        //初始化--->全部都沒有被遍歷過
        for (int i = 0; i < G.V(); i++) {
            visited[i] = false;  //全部節點都還未被走訪
            id[i] = -1;          //初始化所有節點 都屬於id=-1的子圖
        }

        ccount = 0;  //初始化連通分量值--->未開始檢查

        //開始檢查每個節點
        for (int i = 0; i < G.V(); i++) {
            //如果當前節點尚未被走訪過
            if (!visited[i]) {
                //對節點i做dfs深度優先遍歷
                dfs(i);
                //經過一次dfs代表 某一塊子圖 被遍歷完 代表找到一塊子圖
                ccount++;  //更新連通分量
            }
        }
    }

    ~Component() {
        delete[] visited;
        delete[] id;
    }

    //回傳 連通分量--->有多少個子圖
    int count() {
        return ccount;
    }

    //查看節點v與w是否連接在一起--->判斷是否在同子圖
    bool isConnected(int v, int w) {
        //檢查v與w是否合法
        assert(v >= 0 && v < G.V());
        assert(w >= 0 && w < G.V());

        return id[v] == id[w];
    }
};
#endif