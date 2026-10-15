/*
n <= 15,  방향성 있는 그래프
한 학기에 k개 까지만 선택 가능 -> 최소 학기 구하기
k개 이상으로 선택 가능할 때 비트마스킹 dp로 구하기?
permutation 써보기
*/

#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

class Solution {
    vector<vector<int>> edges;
    vector<int> indegree;
    vector<int> dp;
    deque<int> seq;

    void func(vector<vector<int>>& edges, int k, int visited, deque<int> seq) {
        int size = seq.size();
        int nvisited = visited;
        deque<int> nseq = seq;

        if (size > k) {
            vector<int> order(size, 0);
            for (int i = 0; i < k; i++) {
                order[i] = 1;
            }

            do {
                for (auto idx : order) {
                    if (!idx) continue;
                    //
                }
            } while (next_permutation(order.begin(), order.end()));
        }

        else {
            while (size--) {
                int now = seq.front();
                seq.pop_front();
                nvisited |= 1 << now;

                for (int& next : edges[now]) {
                    if (!--indegree[next]) nseq.push_back(next);
                }
            }

            if (dp[nvisited] <= dp[visited] + 1) return;
            func(edges, k, nvisited, nseq);
        }
    }

public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        edges.resize(n);
        indegree.resize(n, 0);
        dp.resize(1 << n, 0);

        for (const auto& r : relations) {
            edges[r[0]].push_back(r[1]);
            indegree[r[1]]++;
        }
        for (int idx : indegree) {
            if (!indegree[idx]) seq.push_back(idx);
        }

        func(edges, k, 0, seq);

        return dp[(1 << n) - 1];
    }
};