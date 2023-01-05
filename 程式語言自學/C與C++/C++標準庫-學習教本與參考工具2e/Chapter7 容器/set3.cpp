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

int main() {
    //升序lambda表達式
    auto compare = [](const Student &s1, const Student &s2) -> bool { return s1.age < s2.age; };
    //使用lambda表達式 當作排序規則
    set<Student, decltype(compare)> s(compare);  //使用decltype讓編譯器推倒lambda的型別 並以lambda當作constructor參數

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