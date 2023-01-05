#include <algorithm>
#include <ctime>
#include <iostream>

#include "DenseGraph.h"
#include "SparseGraph.h"
using namespace std;

int main() {
    int N = 20;   //節點數量
    int M = 100;  //邊的數量

    srand(time(NULL));

    // Sparse Graph
    SparseGraph g1(N, false);  //無向的稀疏圖
    for (int i = 0; i < M; i++) {
        //隨機找兩個節點
        int a = rand() % N;
        int b = rand() % N;
        //連接兩個節點--->加入邊
        g1.addEdge(a, b);
    }

    // 輸出每個節點和 與之相連的節點--->遍歷該節點的vector中所有被記錄的邊--->時間複雜度O(E)
    for (int v = 0; v < N; v++) {
        cout << v << " : ";
        SparseGraph::adjIterator adj(g1, v);
        for (int w = adj.begin(); !adj.end(); w = adj.next())
            cout << w << " ";
        cout << endl;
    }

    cout << endl;

    // Dense Graph
    DenseGraph g2(N, false);
    for (int i = 0; i < M; i++) {
        int a = rand() % N;
        int b = rand() % N;
        g2.addEdge(a, b);
    }

    //對每個節點 掃描V個元素--->時間複雜度--->O(V^2)
    for (int v = 0; v < N; v++) {
        cout << v << " : ";
        DenseGraph::adjIterator adj(g2, v);
        for (int w = adj.begin(); !adj.end(); w = adj.next())
            cout << w << " ";
        cout << endl;
    }

    return 0;
}