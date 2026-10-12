#include <iostream>
#include <vector>
using namespace std;

// 도넛 모양 2겹
// 1구역 or 인접 포함 2구역
// W명으로 구역 합친만큼 커버 가능
// dp문제?
// --------------------------------------------------------------------
// 인접하기 때문에 0 ~ i 구역까지 순차적으로 dp 설정해서 구해가는게 가능

int N, W;                   // 구역개수의 반, 소대원 수
vector<int> enemy1, enemy2; // 적 수
int visited[20000];         // 구역 방문 여부
vector<int> dp, dp1, dp2;   // 모두 채움, 1번째 줄만 채움, 2번째 줄만 채움

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> W;
        enemy1.resize(N);
        enemy2.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> enemy1[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> enemy2[i];
        }
    }
}