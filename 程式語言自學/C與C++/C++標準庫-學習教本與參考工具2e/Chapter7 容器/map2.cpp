#include <algorithm>
#include <iostream>
#include <map>
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

//實作functor
struct Compare {
    bool operator()(const Student &s1, const Student &s2) {
        return s1.age < s2.age;
    }
};

int main() {
    //使用functor當作key的排序規則
    map<Student, int, Compare> map;
    map.insert({{"Peter", 18}, 1});
    map[{"Mary", 30}] = 2;
    map.emplace(Student("Tom", 21), 3);

    for (auto st : map) {  //auto 會自動推導成pair<Student,int>
        cout << st.first << endl;
    }
    //Peter 18
    //Tom 21
    //Mary 30
    return 0;
}