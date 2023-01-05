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
    //如果將operator<寫在struct中 函式要以const修飾
    bool operator<(const Student &s) const {
        return this->age < s.age;
    }
};

int main() {
    //使用map默認調用的operator< 來排序key
    map<Student, int> map;
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