// 순서대로 도착
// heap으로 빼기
// =================================================================
// union-find 문제
// 이 문제에서 Union 함수는 필요 없음
// parent[MAX] = find(MAX - 1) 로 갱신

#include <iostream>
#include <vector>
using namespace std;

int G, P; // 게이트, 비행기
vector<int> parent;
int ans = 0;

int find(int now) {
    if (now == parent[now]) return now;
    return parent[now] = find(parent[now]);
}

void Union(int a, int b) {
    int roota = find(a);
    int rootb = find(b);
    if (roota == rootb) return;
    parent[rootb] = roota;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> G >> P;
    parent.resize(G + 1, 0);
    for (int i = 1; i <= G; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < P; i++) {
        int g;
        cin >> g;

        int MAX = find(g);
        if (!MAX) break;

        Union(MAX - 1, MAX);
        ans++;
    }

    cout << ans << "\n";
}