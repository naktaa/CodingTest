#include <algorithm>
#include <vector>
using namespace std;

vector<int> nums;
vector<vector<int>> ans;

void permutations() {
    ans.clear();
    sort(nums.begin(), nums.end());
    do {
        ans.push_back(nums);
    } while (next_permutation(nums.begin(), nums.end()));
}
