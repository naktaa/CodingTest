#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    string name;
    int d;
    int m;
    int y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<Student> students;
    students.reserve(n);

    for (int i = 0; i < n; i++) {
        Student student{};
        cin >> student.name >> student.d >> student.m >> student.y;
        students.push_back(student);
    }

    stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.y != b.y) return a.y < b.y;
        if (a.m != b.m) return a.m < b.m;
        return a.d < b.d;
    });

    cout << students.back().name << '\n';
    cout << students.front().name << '\n';
}