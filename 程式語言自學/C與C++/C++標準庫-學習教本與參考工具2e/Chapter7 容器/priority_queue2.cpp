#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

struct Student {
    friend ostream &operator<<(ostream &os, const Student &s) {
        cout << s.name << " " << s.age;
        return os;
    }
    int age;
    string name;
    Student(string name, int age) {
        this->name = name;
        this->age = age;
    }
};

//實作Functor
struct Compare {
    bool operator()(const Student &s1, const Student &s2) const {
        return s1.age < s2.age;
    }
};

int main() {
    //使用自訂義Functor當作排序準則
    priority_queue<Student, vector<Student>, Compare> pq;
    pq.push({"Peter", 18});
    pq.push({"Mary", 30});
    pq.push({"Tom", 21});

    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
    //Mary 30
    //Tom 21
    //Peter 18
    return 0;
}