#include <algorithm>
#include <iostream>
#include <set>
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
    bool operator()(const Student &s1, const Student &s2) {
        return s1.age < s2.age;
    }
};

int main() {
    //使用functor當作排序規則
    set<Student, Compare> s;

    s.emplace("Peter", 18);
    s.emplace("Mary", 30);
    s.emplace("Tom", 21);

    for (auto st : s) {
        cout << st << endl;
    }
    //Peter 18
    //Tom 21
    //Mary 30
    return 0;
}