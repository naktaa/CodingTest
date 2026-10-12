#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    set<string> people;
    set<string> ans;

    cin >> N >> M;
    while (N--) {
        string person;
        cin >> person;
        people.insert(person);
    }

    while (M--) {
        string person;
        cin >> person;
        if (people.find(person) != people.end()) ans.insert(person);
    }

    cout << ans.size() << "\n";
    for (auto name : ans) {
        cout << name << "\n";
    }
}