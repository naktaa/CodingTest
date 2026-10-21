#include <deque>
#include <vector>
using namespace std;

vector<int> arr, ans;
int k;

void windowMaximum() {
    ans.clear();
    if (k <= 0 || k > static_cast<int>(arr.size())) return;
    deque<int> dq;
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        while (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();
        while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(arr[dq.front()]);
    }
}
