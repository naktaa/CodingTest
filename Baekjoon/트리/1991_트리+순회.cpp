#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
vector<vector<int>> tree;

void preorder(int now) {
    if (now == -1) return;
    cout << (char)(now + 'A');
    preorder(tree[now][0]);
    preorder(tree[now][1]);
}

void inorder(int now) {
    if (now == -1) return;
    inorder(tree[now][0]);
    cout << (char)(now + 'A');
    inorder(tree[now][1]);
}

void post(int now) {
    if (now == -1) return;
    post(tree[now][0]);
    post(tree[now][1]);
    cout << (char)(now + 'A');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    tree.resize(N);

    for (int i = 0; i < N; i++) {
        char from, n1, n2;
        cin >> from >> n1 >> n2;
        if (n1 == '.')
            tree[from - 'A'].push_back(-1);
        else
            tree[from - 'A'].push_back(n1 - 'A');
        if (n2 == '.')
            tree[from - 'A'].push_back(-1);
        else
            tree[from - 'A'].push_back(n2 - 'A');
    }

    // 전위 순회
    preorder(0);
    cout << "\n";

    // 중위 순회
    inorder(0);
    cout << "\n";

    // 후위 순회
    post(0);
}