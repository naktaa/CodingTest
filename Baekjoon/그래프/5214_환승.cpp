// 여러 개의 역을 거치는 경로가 하이퍼튜브의 경로면 방문개수 1로 침
// 단순하게 하이퍼튜브 경로마다 다 큐에 넣기?
// set에 넣어서 그래프 만들기
// visited_station 만들어서 관리
// ==============================================================================
// 단순하게 모든 set을 다 돌면 시간 초과
// 각 노드마다 어떤 튜브에 들어가있는지 배열 하나 더 만들기
// 튜브에 대한 visited도 만들기
// ==============================================================================
// set 대신 vector를 써서 오버헤드를 크게 줄인 번외코드 아래에 따로 있음

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct node {
    int num, cnt; // 현재 위치, 방문한 역 개수
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K, M;                // 역의 수, 연결 역 수, 하이퍼튜브 수
    vector<set<int>> Tube;      // 하이퍼튜브
    vector<vector<int>> Belong; // 속해있는 하이퍼튜브 번호 저장
    vector<int> visited_station;
    vector<int> visited_tube;

    cin >> N >> K >> M;
    Belong.resize(N + 1);
    visited_station.resize(N + 1, 0);
    visited_tube.resize(M, 0);
    for (int i = 0; i < M; i++) {
        set<int> s;
        for (int j = 0; j < K; j++) {
            int n;
            cin >> n;
            s.insert(n);
            Belong[n].push_back(i);
        }
        Tube.push_back(s);
    }

    // bfs 시작
    queue<node> q;
    q.push({1, 1});
    visited_station[1] = 1;

    while (!q.empty()) {
        node now = q.front();
        q.pop();
        // 현재 N번 역이면 출력하고 종료
        if (now.num == N) {
            cout << now.cnt << "\n";
            return 0;
        }

        // 현재 역이 속한 하이퍼튜브만 순회
        for (const auto& index : Belong[now.num]) {
            if (visited_tube[index]) continue; // 이미 방문한 하이퍼튜브면 pass
            visited_tube[index] = 1;

            for (const int& next : Tube[index]) {
                if (visited_station[next]) continue; // 이미 방문한 역이면 pass
                visited_station[next] = 1;
                q.push({next, now.cnt + 1});
            }
        }
    }
    cout << -1 << "\n";
}


/*
// 여러 개의 역을 거치는 경로가 하이퍼튜브의 경로면 방문개수 1로 침
// 단순하게 하이퍼튜브 경로마다 다 큐에 넣기?
// vector에 넣어서 그래프 만들기
// visited_station 만들어서 관리
// ==============================================================================
// 단순하게 모든 하이퍼튜브를 다 돌면 시간 초과
// 각 노드마다 어떤 튜브에 들어가있는지 배열 하나 더 만들기
// 튜브에 대한 visited도 만들기

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int num, cnt; // 현재 위치, 방문한 역 개수
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K, M;                   // 역의 수, 연결 역 수, 하이퍼튜브 수
    vector<vector<int>> Tube;      // 하이퍼튜브 (각 튜브에 연결된 역들)
    vector<vector<int>> Belong;    // 각 역이 속해있는 하이퍼튜브 번호들
    vector<int> visited_station;   // 역 방문 여부
    vector<int> visited_tube;      // 튜브 방문 여부

    cin >> N >> K >> M;

    Tube.assign(M, vector<int>());
    Belong.assign(N + 1, vector<int>());
    visited_station.assign(N + 1, 0);
    visited_tube.assign(M, 0);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            int n;
            cin >> n;
            Tube[i].push_back(n);
            Belong[n].push_back(i);
        }
    }

    // bfs 시작
    queue<node> q;
    q.push({1, 1});
    visited_station[1] = 1;

    while (!q.empty()) {
        node now = q.front();
        q.pop();

        // 현재 N번 역이면 출력하고 종료
        if (now.num == N) {
            cout << now.cnt << "\n";
            return 0;
        }

        // 현재 역이 속한 하이퍼튜브만 순회
        for (int index : Belong[now.num]) {
            if (visited_tube[index]) continue; // 이미 방문한 하이퍼튜브면 pass
            visited_tube[index] = 1;

            for (int next : Tube[index]) {
                if (visited_station[next]) continue; // 이미 방문한 역이면 pass
                visited_station[next] = 1;
                q.push({next, now.cnt + 1});
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}
*/