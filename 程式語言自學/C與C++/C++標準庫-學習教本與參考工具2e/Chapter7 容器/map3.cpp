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

int main() {
    //升序lambda表達式
    auto compare = [](const Student &s1, const Student &s2) -> bool { return s1.age < s2.age; };
    //使用lambda表達式 當作key的排序規則
    map<Student, int, decltype(compare)> map(compare);
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