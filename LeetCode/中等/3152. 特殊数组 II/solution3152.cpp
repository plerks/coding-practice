/*
url: https://leetcode.cn/problems/special-array-ii/description/
LeetCode参考: https://leetcode.cn/problems/special-array-ii/solutions/2782830/qian-zhui-he-wei-yun-suan-pythonjavacgo-3pvya/
标签: LeetCode第398场周赛, 前缀和
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3152 {
public:
    /* 周赛时的做法，把所有特殊数组求出来存着，然后对每个query，二分求最后一个左端点 <= query[0]的，
    看query是否在这个区间
    */
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int qLen = queries.size();
        vector<bool> ans(qLen, true);

        for (int &num : nums) num = num % 2;

        vector<pair<int, int>> intervals;
        int left = 0, right = 0;
        while (left < n && right < n) {
            if (left == right) {
                right++;
                continue;
            }
            if (nums[right] == nums[right - 1]) {
                intervals.push_back(make_pair(left, right - 1));
                left = right;
                continue;
            }
            else right++;
        }
        intervals.push_back(make_pair(left, right - 1));


        for (int i = 0; i < qLen; i++) {
            if (queries[i][1] - queries[i][0] + 1 <= 1) {
                ans[i] = true;
                continue;
            }
            ans[i] = false;
            int lo = queries[i][0], hi = queries[i][1];
            // 找最后一个左边界<=lo的
            int left = 0, right = intervals.size() - 1;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (intervals[mid].first <= lo) left = mid + 1;
                else right = mid - 1;
            }
            if (left - 1 == -1) continue;
            else if (intervals[left - 1].first <= lo && hi <= intervals[left - 1].second) {
                ans[i] = true;
            }
        }
        return ans;
    }

    // 改进一下，dp求每个位置最左能到哪里即可
    vector<bool> isArraySpecial_implementation2(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> dp(n);
        iota(dp.begin(), dp.end(), 0); // 填充为0 - (n - 1)
        for (int i = 1; i < n; i++) {
            if ((nums[i] & 1) != (nums[i - 1] & 1)) {
                dp[i] = dp[i - 1];
            }
        }
        vector<bool> ans;
        for (auto &query : queries) {
            ans.push_back(dp[query[1]] <= query[0]);
        }
        return ans;
    }

    /* 灵茶山艾府题解解法，对每个nums[i]，如果其与nums[i - 1]奇偶性不同则为0，相同则为1，
    于是对一个query，只需检测query[0] - query[1]是否含有1即可，于是转化为前缀和是否大于0。 */
    vector<bool> isArraySpecial_implementation3(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> prefixSum(n, 0);
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + ((nums[i] & 1) == (nums[i - 1] & 1));
        }
        vector<bool> ans;
        for (auto &query : queries) {
            // 检测(query[0], query[1]]间有无1即可
            ans.push_back(prefixSum[query[1]] - prefixSum[query[0]] == 0);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3152 solu;
    vector<int> nums = {4, 3, 1, 6};
    vector<vector<int>> queries = {{0,2},{2,3}};
    auto a = solu.isArraySpecial_implementation3(nums, queries);
    return 0;
}
