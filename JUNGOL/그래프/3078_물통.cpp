/*
채우기, 비우기, 빈만큼 옮기기
원하는 상태로 만들기 위한 최소 작업 수
불가능하면 -1 출력
dp?
동작을 전부 정의한 뒤 각 상태별로 횟수 저장, 비교하면서 더 많은 횟수로 진행한다면 가지치기
1: A 채우기, 2: B 채우기, 3: A 비우기, 4: B 비우기, 5: A -> B, 6: A <- B
A B 최대 10만
===================================================
10만개 그대로 2차원 하면 터짐
동작을 보면 항상 하나가 0이 되니 테두리 배열만 관리 가능
배열 4개로 하면 해쉬보다 시간복잡도 측면에서 더 유리
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
using pr = pair<int, int>;

struct node {
    int a, b, cnt;
};

int A, B, C, D;
set<pr> s;
queue<node> q;

void task(int a, int b, int cnt) {
    if (s.count({a, b})) return;
    s.insert({a, b});
    q.push({a, b, cnt});
}

int main() {
    cin >> A >> B >> C >> D;
    q.push({0, 0, 0});
    s.insert({0, 0});

    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (now.a == C && now.b == D) {
            cout << now.cnt << "\n";
            return 0;
        }

        int difa = A - now.a, difb = B - now.b;

        task(A, now.b, now.cnt + 1);
        task(now.a, B, now.cnt + 1);
        task(0, now.b, now.cnt + 1);
        task(now.a, 0, now.cnt + 1);
        (now.a > difb) ? task(now.a - difb, B, now.cnt + 1) : task(0, now.b + now.a, now.cnt + 1);
        (now.b > difa) ? task(A, now.b - difa, now.cnt + 1) : task(now.a + now.b, 0, now.cnt + 1);
    }

    cout << -1 << "\n";
}