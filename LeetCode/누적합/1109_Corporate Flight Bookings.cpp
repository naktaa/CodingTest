/*
N <= 2e4, booking <= 2e4
구간안에 있는거 다 더하기 -> 시간 초과 발생할수있는지 최대 4e8?
최적화 방법 필요
================================================================
브루탈포스로 하면 오래 걸림
차분배열 + 누적합 방식 으로 최적화
구간 양 끝의 변화량만 기록 -> 누적합 계산
*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> seats(n, 0);

        for (const auto& book : bookings) {
            for (int i = book[0] - 1; i < book[1]; i++) {
                seats[i] += book[2];
            }
        }

        return seats;
    }
};

/*
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> seats(n, 0);

        for (const auto& book : bookings) {
            int start = book[0] - 1;
            int end = book[1];
            int seat = book[2];

            seats[start] += seat;

            if (end < n) {
                seats[end] -= seat;
            }
        }

        for (int i = 1; i < n; i++) {
            seats[i] += seats[i - 1];
        }

        return seats;
    }
};
*/