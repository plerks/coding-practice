/*
url: https://leetcode.cn/problems/ways-to-split-array-into-three-subarrays/
相关: LeetCode3455. 最短匹配子字符串
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1712 {
public:
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        const int mod = 1000000007;
        long long ans = 0;
        int l1 = 0, l2 = 0;
        long long sum1 = 0;
        long long sum2_1 = 0, sum2_2 = 0;
        long long sum3 = accumulate(nums.begin(), nums.end(), 0LL);
        for (int r = 0; r < n - 1; r++) {
            sum2_1 += nums[r];
            sum2_2 += nums[r];
            sum3 -= nums[r];
            // 右 >= 中
            while (sum3 < sum2_1) { // 中段的左边界 ∈ [l1, r]
                sum2_1 -= nums[l1];
                l1++;
            }
            // 左 <= 中
            while (l2 <= r && sum1 <= sum2_2) { // 中段的左边界 ∈ [1, l2)
                sum2_2 -= nums[l2];
                sum1 += nums[l2];
                l2++;
            }
            int ll = max(l1, 1);
            int rr = min(r, l2 - 1);
            // cout << r << endl;
            // cout << max(0, rr - ll + 1) << endl;
            ans = (ans + max(0, rr - ll + 1)) % mod;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1712 solu;
    // cout << solu.waysToSplit(*new vector<int>{1,1,1}) << endl;
    cout << solu.waysToSplit(*new vector<int>{1,2,2,2,5,0}) << endl;
    // cout << solu.waysToSplit(*new vector<int>{3,2,1}) << endl;
    return 0;
}