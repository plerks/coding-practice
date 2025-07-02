/*
url: https://leetcode.cn/problems/split-array-into-maximum-number-of-subarrays/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2871 {
public:
    // & 得越多，结果越小，所以把nums &全部得到的最小，这个基础上要让子数组尽量多划分
    // 1. and(nums) > 0，不可划分
    // 2. and(nums) == 0，必须保证每段为0
    int maxSubarrays(vector<int>& nums) {
        int n = nums.size();
        int total = -1;
        for (int x : nums) total &= x;
        if (total > 0) return 1;
        // 分组循环
        int cnt = 0;
        for (int i = 0; i < n;) {
            int start = i;
            int t = nums[start];
            for (i++; i < n && t != 0; t &= nums[i], i++);
            cnt++;
            if (i == n && t != 0) cnt--; // 最后一段&不是0，得和前面的一段合并
        }
        return cnt;
    }

    // 灵茶题解写法
    int maxSubarrays_implementation2(vector<int>& nums) {
        int ans = 0;
        int t = -1;
        for (int x : nums) {
            t &= x;
            if (t == 0) {
                ans++;
                t = -1;
            }
        }
        return max(ans, 1); // 如果ans为0说明nums整段& > 0，返回1
    }
};

int main(int argc, char const *argv[]) {
    Solution2871 solu;
    cout << solu.maxSubarrays(*new vector<int>{1,0,2,0,1,2}) << endl;
    return 0;
}