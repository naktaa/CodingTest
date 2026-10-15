
/*
n <= 15, 방향성 있는 그래프
한 학기에 k개 까지만 선택 가능 -> 최소 학기 구하기
비트마스킹 DP + 재귀
permutation으로 조합 생성
*/

#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

class Solution {
    const int INF = 1e8;

    vector<vector<int>> edges;
    vector<int> Initindegree;
    vector<int> dp;
    deque<int> Initseq;

    void func(vector<vector<int>>& edges, int k, int visited, deque<int> seq, vector<int> indegree) {
        int size = seq.size();
        if (size == 0) return;

        int nvisited = visited;
        vector<int> nindegree = indegree;
        deque<int> nseq = seq;

        if (size > k) {
            vector<int> order(size, 0);
            for (int i = 0; i < k; i++) {
                order[i] = 1;
            }

            do {
                nvisited = visited;
                nindegree = indegree;
                nseq.clear();

                for (int i = 0; i < size; i++) {
                    int now = seq[i];

                    if (!order[i]) {
                        nseq.push_back(now);
                        continue;
                    }

                    nvisited |= 1 << now;

                    for (int& next : edges[now]) {
                        if (!--nindegree[next]) nseq.push_back(next);
                    }
                }

                if (dp[nvisited] <= dp[visited] + 1) continue;
                dp[nvisited] = dp[visited] + 1;
                func(edges, k, nvisited, nseq, nindegree);

            } while (prev_permutation(order.begin(), order.end()));
        }

        else {
            while (size--) {
                int now = nseq.front();
                nseq.pop_front();
                nvisited |= 1 << now;

                for (int& next : edges[now]) {
                    if (!--nindegree[next]) nseq.push_back(next);
                }
            }

            if (dp[nvisited] <= dp[visited] + 1) return;
            dp[nvisited] = dp[visited] + 1;
            func(edges, k, nvisited, nseq, nindegree);
        }
    }

public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        edges.resize(n);
        Initindegree.resize(n, 0);
        dp.resize(1 << n, INF);
        dp[0] = 0;

        for (const auto& r : relations) {
            edges[r[0] - 1].push_back(r[1] - 1);
            Initindegree[r[1] - 1]++;
        }
        for (int i = 0; i < n; i++) {
            if (!Initindegree[i]) Initseq.push_back(i);
        }

        func(edges, k, 0, Initseq, Initindegree);

        return dp[(1 << n) - 1];
    }
};

///  바텀업 비트마스킹 dp
/*
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    const int INF = 1e8;

public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> pre(n, 0);

        for (const auto& r : relations) {
            pre[r[1] - 1] |= 1 << (r[0] - 1);
        }

        vector<int> dp(1 << n, INF);
        dp[0] = 0;

        for (int visited = 0; visited < (1 << n); visited++) {
            if (dp[visited] == INF) continue;

            int available = 0;

            // 이번 학기에 수강 가능한 과목
            for (int i = 0; i < n; i++) {
                if (visited & (1 << i)) continue;

                if ((pre[i] & visited) == pre[i]) {
                    available |= 1 << i;
                }
            }

            if (__builtin_popcount((unsigned)available) <= k) {
                int nvisited = visited | available;
                dp[nvisited] = min(dp[nvisited], dp[visited] + 1);
            }
            else {
                // available의 모든 부분집합 탐색
                for (int sub = available; sub; sub = (sub - 1) & available) {
                    if (__builtin_popcount((unsigned)sub) != k) continue;

                    int nvisited = visited | sub;
                    dp[nvisited] = min(dp[nvisited], dp[visited] + 1);
                }
            }
        }

        return dp[(1 << n) - 1];
    }
};
*/