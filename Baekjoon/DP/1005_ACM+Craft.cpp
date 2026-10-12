// 건물 짓는 순서 주어짐
// 건설시간 필요
// 부모 건물이 다 완성되어야 건설 가능
// 건설 동시 진행 가능
// 최소 건설 시간 출력
// 1번부터 시작해서 pq에 넣고 제일 작은 시간만큼 감소
// flag++ 로 건설 가능 여부 판단해 가능하면 pq에 삽입
// -----------------------------------------------------------------------------
// 위상정렬 문제 + dp

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string.h>
using namespace std;

struct node {
    int num, time; // 건물 번호, 건설 시간
    bool operator<(node right) const {
        return time < right.time;
    }
};
int N, K;                // 건물의 개수 N, 건설 순서 개수 K
vector<int> D;           // 건설시간
vector<vector<int>> seq; // 건설 순서
int W;                   // 건설해야할 번호 W
int flag[1010];          // 건설 가능 여부 확인용
int flag_cmp[1010];      // flag 비교용


void init() {
    D.clear();
    seq.clear();
    memset(flag, 0, sizeof(flag));
    memset(flag_cmp, 0, sizeof(flag_cmp));
}

void input() {
    cin >> N >> K;
    D.resize(N);
    seq.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> D[i];
    }
    for (int i = 0; i < K; i++) {
        int from, to;
        cin >> from >> to;
        seq[from - 1].push_back(to - 1);
        flag[to - 1]++;
    }
    cin >> W;
}

int solution() {
    deque<node> pq;    // pq 대신 sort하면서 사용
    vector<int> start; // 진입차수가 0인 시작지점 모음
    int cnt = 0;       // 총 건설시간
    for (int i = 0; i < N; i++) {
        if (flag[i] == 0) {
            start.push_back(i);
        }
    }
    for (int n : start) {
        pq.push_back({n, D[n]});
    }

    // cout << "\n";

    while (!pq.empty()) {
        node MIN = pq.front();
        pq.pop_front();
        cnt += MIN.time;
        // 건물 W의 건설 조건이 모두 충족되면 ans에 더하고 종료
        if (MIN.num == W - 1) return cnt;
        // cout << cnt << "\n";
        // 최소 건설시간 만큼 큐에 있는 다른 시간들 감소
        if (!pq.empty()) {
            for (node& target : pq) {
                target.time -= MIN.time;
            }
        }

        // 건설 마치면 연결된 다음 건물들 건설 가능한지 확인
        for (int next : seq[MIN.num]) {
            flag_cmp[next]++;
            if (flag_cmp[next] == flag[next]) pq.push_back({next, D[next]});
        }

        // pq 오름차순으로 정렬
        sort(pq.begin(), pq.end());
        // for (node target : pq) {
        //     cout << target.num << " " << target.time << " | ";
        // }
        // cout << "\n";
    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        int ans = solution();
        cout << ans << "\n";
    }
}