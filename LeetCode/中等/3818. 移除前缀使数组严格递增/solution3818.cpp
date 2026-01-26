/*
url: https://leetcode.cn/problems/minimum-prefix-removal-to-make-array-strictly-increasing/
标签: LeetCode第486场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3818 {
public:
    // 周赛时的做法，先把递增子数组长度求出来的
    int minimumPrefixLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n, 1);
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) f[i] = f[i - 1] + 1;
        }
        return n - f[n - 1];
    }

    // 实际只用到 f[n - 1] ，所以直接从 nums[n - 1] 倒着找末尾的最长递增子数组就行了
    int minimumPrefixLength_implementation2(vector<int>& nums) {
        int n = nums.size();
        int i = n - 1;
        while (i > 0 && nums[i] > nums[i - 1]) i--;
        return i;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}