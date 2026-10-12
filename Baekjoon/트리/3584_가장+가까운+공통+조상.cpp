// depth 맞추고 한 단계씩 끌어올리면서 맞추기
// LCA 문제 O(N)에서 이분탐색으로 O(logN) 가능

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        vector<int> parent;
        int node1, node2;
        int dep1 = 0, dep2 = 0;

        cin >> N;
        parent.resize(N + 1, -1);
        N--;
        while (N--) {
            int A, B;
            cin >> A >> B;
            parent[B] = A;
        }
        cin >> node1 >> node2;

        for (int next = node1; next != -1; next = parent[next])
            dep1++;
        for (int next = node2; next != -1; next = parent[next])
            dep2++;

        // depth 맞추기
        int dif = abs(dep1 - dep2);
        if (dep1 > dep2) {
            while (dif--) {
                node1 = parent[node1];
            }
        }
        else {
            while (dif--) {
                node2 = parent[node2];
            }
        }

        while (node1 != node2) {
            node1 = parent[node1];
            node2 = parent[node2];
        }

        cout << node1 << "\n";
    }
}