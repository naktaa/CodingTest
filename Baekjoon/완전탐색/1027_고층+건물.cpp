#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


int n;
vector<double> building;
int ans;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        building.push_back(temp);
    }

    if (building.size() == 1) {
        std ::cout << "0\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int cnt = 0; // i번째마다 몇 개 보이는지 카운트
        for (int j = 0; j < n; j++) {
            double slope = 0;
            double y = 0;

            if (i == j) continue;
            if (abs(i - j) == 1) {
                cnt++;
                continue;
            }
            if (building[i] == building[j])
                y = building[i];
            else {
                slope = ((building[i] - building[j]) / (i - j)); // i, j 사이 기울기
                y = building[j] - slope * j;                     // y절편
            }
            cnt++; // 다른 빌딩마다 미리 +1하고 선분에 걸리면 -1

            // 선분 그었을 때 사이에 있는 좌표의 빌딩의 높이가 더 높은지 아닌지
            if (i < j) {
                for (int tar = i + 1; tar < j; tar++) {
                    if (building[tar] >= slope * tar + y) {
                        cnt--;
                        break;
                    }
                }
            }
            else if (i > j) {
                for (int tar = i - 1; tar > j; tar--) {
                    if (building[tar] >= slope * tar + y) {
                        cnt--;
                        break;
                    }
                }
            }
        }
        if (cnt > ans) ans = cnt;
    }
    cout << ans;
}