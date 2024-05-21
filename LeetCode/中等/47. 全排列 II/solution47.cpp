/*
url: https://leetcode.cn/problems/permutations-ii/description/
LeetCode参考: https://leetcode.cn/problems/permutations-ii/solutions/417937/quan-pai-lie-ii-by-leetcode-solution/
相关: LeetCode46. 全排列
标签: 全排列
*/

#include <bits/stdc++.h>

using namespace std;

class Solution47 {
public:
    /* 相比LeetCode46. 全排列，nums数字可重复，要求不重复的排列，也就是相同元素不要全排，
    因此递归时，若还有位置更靠前的x没有被使用，则不走这个递归分支 */
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> perm;
        vector<char> visited(n, 0);
        vector<int> cnt(n, 0); // 每个元素是其同类元素里第几个
        unordered_map<int, int> map; // 每种元素已选了多少个
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (map.find(num) == map.end()) {
                map[num] = 0;
            }
            else map[num]++;
            cnt[i] = map[num];
        }
        map.clear();

        function<void(int)> dfs = [&](int count) {
            if (count == n) {
                ans.push_back(perm);
                return;
            }
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    int num = nums[i];
                    if (map[num] != cnt[i]) continue;
                    perm.push_back(nums[i]);
                    map[num]++;
                    visited[i] = true;
                    dfs(count + 1);
                    perm.pop_back();
                    map[num]--;
                    visited[i] = false;
                }
            }
        };

        dfs(0);

        return ans;
    }

    // 官方题解的做法，把nums排序，然后尝试nums[i]时，若nums[i - 1] == nums[i]且nums[i]还未访问，则不能轮到nums[i]
    vector<vector<int>> permute_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> perm;
        sort(nums.begin(), nums.end());
        vector<char> visited(n, 0);

        function<void(int)> dfs = [&](int count) {
            if (count == n) {
                ans.push_back(perm);
                return;
            }
            for (int i = 0; i < n; i++) {
                if (!visited[i] && !(i > 0 && nums[i - 1] == nums[i] && !visited[i - 1])) {
                    perm.push_back(nums[i]);
                    visited[i] = true;
                    dfs(count + 1);
                    perm.pop_back();
                    visited[i] = false;
                }
            }
        };

        dfs(0);

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution47 solu;
    vector<int> nums = {1,1,2};
    solu.permute(nums);
    solu.permute_implementation2(nums);
    return 0;
}