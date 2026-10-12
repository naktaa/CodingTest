// 직렬 연결 --> 더 작은 용량
// 병렬 연결 --> 합한만큼의 용량
// 연결되어 있지 않으면 제거
// A - Z 사이의 최대 유량 계산
// 재귀로 구성해서 병렬이면 모두 더하고 다음 노드와 직렬 계산으로 min 하면서 유량 return
// Z까지 연결 안되는 경우는 제거 해야됨

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    int to, cap; // 연결 노드, 용량
};
vector<vector<node>> pipes(26);                     // A - Z 까지 26개
vector<vector<int>> pipes(26, vector<int>(26, -1)); // 구간 유량
int ans;

int cal() {
}

int main() {
    int N;
    cin >> N;

    while (N--) {
        char from, to;
        int cap;
        pipes[from - 'A'].push_back({to - 'A', cap});
    }

    for (const auto& pipe : pipes) {
        for (const auto& node : pipe) {
            ans += node.cap;
        }
    }
}