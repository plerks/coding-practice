/*
url: https://leetcode.cn/problems/longest-subarray-with-maximum-bitwise-and/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2419 {
public:
    // & 之后一定会变小，最大值一定是max(nums)，然后看能多长就行，一出现别的数，&就会变小，所以，看连续的mx最长多长就行
    int longestSubarray(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        int ans = 0;
        // 分组循环
        for (int i = 0; i < nums.size();) {
            int start = i;
            for (i++; i < nums.size() && nums[i] == nums[i - 1]; i++);
            if (nums[start] == mx) ans = max(ans, i - start);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2419 solu;
    cout << solu.longestSubarray(*new vector<int>{1,2,3,3,2,2}) << endl;
    return 0;
}