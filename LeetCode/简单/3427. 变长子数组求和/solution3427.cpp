/*
url: https://leetcode.cn/problems/sum-of-variable-length-subarrays/
标签: LeetCode第433场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3427 {
public:
    int subarraySum(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n);
        pre[0]= nums[0];
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i - 1] + nums[i];
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int start = max(0, i - nums[i]) - 1;
            int s = start >= 0 ? pre[start] : 0;
            ans += pre[i] - s;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}