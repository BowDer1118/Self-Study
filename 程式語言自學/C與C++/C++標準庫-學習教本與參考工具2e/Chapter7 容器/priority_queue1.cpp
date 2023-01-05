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
    //內部實作operator<()
    bool operator<(const Student &s1) const {  //要使用const修飾
        return this->age < s1.age;
    }
};

int main() {
    priority_queue<Student> pq;
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