/*
n까지의 정수를 조합
각 index에 대해 나누어떨어져야함
n <= 15
백트래킹 하면서 세기?
2 6
*/

class Solution {
    int cnt = 0;

    void dfs(int idx, int used, int n) {
        if (idx == n) {
            cnt++;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (used & (1 << i)) continue;
            if ((idx + 1) % (i + 1) != 0 && (i + 1) % (idx + 1) != 0) continue;

            dfs(idx + 1, used | (1 << i), n);
        }
    }

public:
    int countArrangement(int n) {
        dfs(0, 0, n);
        return cnt;
    }
};