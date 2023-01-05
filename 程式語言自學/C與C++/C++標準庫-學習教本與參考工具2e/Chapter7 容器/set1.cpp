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
    //實作operator< 讓set調用
    bool operator<(const Student &s) const {  //如果將operator<寫在struct中 函式要以const修飾
        return this->age < s.age;
    };
};

int main() {
    //使用set默認調用的operator< 來排序
    set<Student> s;

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