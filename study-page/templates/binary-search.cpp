#include <vector>
using namespace std;

vector<int> arr; // 오름차순 정렬된 입력

int lowerIndex(int x) {
    int left = 0;
    int right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < x) left = mid + 1;
        else right = mid;
    }
    return left;
}
