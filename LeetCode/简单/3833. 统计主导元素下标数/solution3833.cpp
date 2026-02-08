/*
url: https://leetcode.cn/problems/count-dominant-indices/
标签: LeetCode第488场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3833 {
public:
    // 这题数据范围只有100，周赛时直接写的暴力，可以用后缀和优化求和过程
    int dominantIndices(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            int t = 0;
            for (int j = i + 1; j < n; j++) {
                t += nums[j];
            }
            if (nums[i] * (n - i - 1) > t) ans++;
        }
        return ans;
    }

    // 参考灵茶题解，不用后缀和，倒着遍历就能一次遍历完成
    int dominantIndices_impl2(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int sum = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            // 也可以在这里 sum += nums[i + 1] 再判断 >
            if (nums[i] * (n - i - 1) > sum) ans++;
            sum += nums[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}