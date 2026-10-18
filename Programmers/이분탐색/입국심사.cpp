// 이분탐색을 결정론적 관점으로 바꿔서 풀기 --> 파라매트릭 서치
// 최소 시간, 최대 시간을 해서 각 심사관별로 나누고 얼마만큼의 사람이 가능한지 구함
// 계속해서 lower_bound 찾아내기

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end()); // 오름차순 정렬

    long long MIN = 1;
    long long MAX = (long long)times[times.size() - 1] * n; // 최대로 걸리는 시간

    while (MIN <= MAX) {
        long long mid = (MIN + MAX) / 2;
        long long cnt = 0;
        for (int time : times) {
            cnt += mid / time; // 시간 안에 각 심사관이 맡을 수 있는 사람 수
        }
        if (cnt >= n)
            MAX = mid - 1;
        else
            MIN = mid + 1;
    }

    return MIN;
}