#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct info {
    int no, age;
    string name;
};

bool cmp(info a, info b) {
    if (a.age != b.age) return a.age < b.age;
    return a.no < b.no;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<info> member;

    cin >> N;
    for (int i = 0; i < N; i++) {
        int age;
        string name;
        cin >> age >> name;
        member.push_back({i, age, name});
    }

    sort(member.begin(), member.end(), cmp);

    for (const auto& m : member) {
        cout << m.age << " " << m.name << "\n";
    }
}