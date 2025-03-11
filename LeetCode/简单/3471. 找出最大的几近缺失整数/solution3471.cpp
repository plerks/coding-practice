/*
url: https://leetcode.cn/problems/find-the-largest-almost-missing-integer/
标签: LeetCode第439场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3471 {
public:
    // 周赛时写的暴力，通过
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> cnt; // 被包含次数
        for (int i = 0; i <= n - k; i++) {
            unordered_map<int, int> seen;
            for (int j = i; j < i + k; j++) {
                seen[nums[j]]++;
            }
            for (auto &[x, c] : seen) {
                cnt[x]++;
            }
        }
        int ans = -1;
        for (int num : nums) {
            if (cnt[num] == 1) ans = max(ans, num);
        }
        return ans;
    }

    // 优化下，当k==n时，整个窗口元素都合法，当k==1时，只出现一次的元素合法，当1 < k < n时，只有两端元素可能合法，只要还在其它地方出现，两端元素就不合法。这样就是线性的
    int largestInteger_implementation2(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = -1;
        // 1 <= k <= n
        if (k == n) {
            return *max_element(nums.begin(), nums.end());
        }
        if (k == 1) {
            unordered_map<int, int> seen;
            for (int x : nums) seen[x]++;
            for (auto &[x, freq] : seen) {
                if (freq == 1) ans = max(ans, x);
            }
            return ans;
        }
        // 1 < k < n，只有两端的两个数可能成为解，再检验一下，只要还在其它地方出现就不行
        int first = nums.front();
        int last = nums.back();
        int cnt1 = 0;
        int cnt2 = 0;
        for (int x : nums) {
            cnt1 += (x == first);
            cnt2 += (x == last);
        }
        if (cnt1 == 1) ans = max(ans, first);
        if (cnt2 == 1) ans = max(ans, last);
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3471 solu;
    cout << solu.largestInteger_implementation2(*new vector<int>{3,9,2,1,7}, 3) << endl;
    cout << solu.largestInteger_implementation2(*new vector<int>{3,9,7,2,1,7}, 4) << endl;
    return 0;
}