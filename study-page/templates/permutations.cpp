#include <algorithm>
#include <vector>
using namespace std;

vector<int> arr;
vector<vector<int>> ans;

void permutations() {
    ans.clear();
    sort(arr.begin(), arr.end());
    do {
        ans.push_back(arr);
    } while (next_permutation(arr.begin(), arr.end()));
}
