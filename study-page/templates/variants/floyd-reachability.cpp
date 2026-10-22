#include <vector>
using namespace std;

vector<vector<int>> reach;

void initReachability(int N) {
    reach.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) reach[i][i] = 1;
}

void addConnection(int from, int to) {
    reach[from][to] = 1;
}

void transitiveClosure() {
    int len = reach.size();
    for (int k = 0; k < len; k++) {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (reach[i][k] && reach[k][j]) reach[i][j] = 1;
            }
        }
    }
}
