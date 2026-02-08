/*
url: https://leetcode.cn/problems/longest-strictly-increasing-subsequence-with-non-zero-bitwise-and/
相关: LeetCode300. 最长递增子序列
标签: LeetCode第175场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3825 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> d; // (长度，最小结尾值)
        // 看 < x 的最后那个点 d[j - 1]，考虑 d[j - 1] + x 是否能更新 d[j]
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = lower_bound(d.begin(), d.end(), x);
            if (it != d.end()) *it = x;
            else d.push_back(x);
        }
        return d.size();
    }

    // 相对于LeetCode300只多了一个OR不能为0的要求，枚举考虑位，对于某一位，需要数的这一位都不为0才能出现在序列中
    // 周赛时直接写成了这样，能过，不过没必要创建新数组
    int longestSubsequence(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            vector<int> t;
            for (int& x : nums) {
                if ((x >> i) & 1) {
                    t.push_back(x);
                }
            }
            ans = max(ans, lengthOfLIS(t));
        }
        return ans;
    }

    // 在枚举位时检查一下就行了，不用把nums的数摘出来
    int longestSubsequence_impl2(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        vector<int> d;
        d.reserve(n); // std::vector不会自动缩容，reserve后只要不调相关函数不会缩回去，这样能缩减一下扩容的时间，时间复杂度不变
        for (int i = 0; i < 32; i++) {
            d.clear();
            for (int& x : nums) {
                if ((x >> i) & 1) {
                    auto it = lower_bound(d.begin(), d.end(), x);
                    if (it != d.end()) *it = x;
                    else d.push_back(x);
                }
            }
            ans = max(ans, (int)d.size());
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}