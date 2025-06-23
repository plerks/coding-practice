/*
url: https://leetcode.cn/problems/maximum-subarray-min-product/
相关: LeetCode2281. 巫师的总力量和
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

// 这题求 最小乘积的最大值，看着有点像最大化最小值，像二分，实际不是
class Solution1856 {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n); // 左侧第一个 <
        vector<int> right(n, n); // 右侧第一个 <=，这里求最大值，不需要不重不漏地枚举子数组，也可以求 右侧第一个 <
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        vector<long long> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + nums[i];
        }
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int l = left[i];
            int r = right[i];
            // (l, r)
            ans = max(ans, nums[i] * 1LL * (pre[r - 1 + 1] - pre[l + 1]));
        }
        return ans % (int)(1e9 + 7);
    }
};

int main(int argc, char const *argv[]) {
    Solution1856 solu;
    cout << solu.maxSumMinProduct(*new vector<int>{1,2,3,2}) << endl;
    return 0;
}