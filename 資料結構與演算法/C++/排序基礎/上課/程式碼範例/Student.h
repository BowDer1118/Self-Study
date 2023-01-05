#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;  //偷懶--->在header中使用namespace

class Student {  //自訂義類別--->測試generic template
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Student: " << student.name << " " << student.score << endl;
        return os;
    }

private:
    string name;
    int score;

public:
    Student(string str, int sc) : name(str), score(sc) {}

    bool operator<(const Student& otherStudent) {
        return score < otherStudent.score;
    }
};

#endif