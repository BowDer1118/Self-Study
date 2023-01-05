#include <algorithm>
#include <iostream>
#include <sstream>  //stringstream
#include <string>
#include <vector>
using namespace std;

int main() {
    string str, token;
    getline(cin, str);  //Hello World
    stringstream st(str);
    vector<string> v;
    while (getline(st, token, ' ')) {
        v.emplace_back(token);
    }
    for (auto s : v) {
        cout << s << endl;
    }
    //Hello
    //World
    return 0;
}