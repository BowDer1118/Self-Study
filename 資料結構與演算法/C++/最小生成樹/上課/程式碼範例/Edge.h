#ifndef EDGE_H
#define EDGE_H
#include <cassert>
#include <iostream>
using namespace std;

//邊
template <class Weight>
class Edge {
    //輸出此edge
    friend ostream& operator<<(ostream& os, const Edge& e) {
        os << e.a << "-" << e.b << ": " << e.weight;
        return os;
    }

private:
    //代表從a指向b的一個邊
    int a;
    int b;
    Weight weight;

public:
    Edge() {
    }
    Edge(int a, int b, Weight weight) {
        this->a = a;
        this->b = b;
        this->weight = weight;
    }
    ~Edge() {}
    int v() {
        return a;
    }
    int w() {
        return b;
    }
    Weight wt() {
        return weight;
    }
    //查詢x是節點a還是節點b--->如果x是a則回傳b
    int other(int x) {
        assert(x == a || x == b);
        if (x == a) {
            return b;
        } else {
            return a;
        }
    }
    //重載比較運算--->比較權重
    bool operator<(Edge<Weight>& e) {
        return weight < e.wt();
    }
    bool operator<=(Edge<Weight>& e) {
        return weight <= e.wt();
    }
    bool operator>(Edge<Weight>& e) {
        return weight > e.wt();
    }
    bool operator>=(Edge<Weight>& e) {
        return weight >= e.wt();
    }
    bool operator==(Edge<Weight>& e) {
        return weight == e.wt();
    }
};
#endif