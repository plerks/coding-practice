/*
url: https://leetcode.cn/problems/4sum/
相关: LeetCode15. 三数之和
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution18 {
public:
    // 类似LeetCode15，前2个数直接枚举，后俩个数用滑窗，能把n^2优化到n，总时间复杂度O(n^3)。也就是说只有最后两个位置的枚举能用滑窗优化。
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for (int a = 0; a < n; a++) {
            if (a > 0 && nums[a] == nums[a - 1]) continue;
            for (int b = a + 1; b < n - 2; b++) {
                if (b > a + 1 && nums[b] == nums[b - 1]) continue;
                int c = b + 1, d = n - 1;
                while (c < d) {
                    long long sum = (long long)nums[a] + nums[b] + nums[c] + nums[d];
                    if (sum == target) {
                        ans.push_back({nums[a], nums[b], nums[c], nums[d]});
                        for (c++; c < d && nums[c] == nums[c - 1]; c++);
                        for (d--; d > c && nums[d] == nums[d + 1]; d--);
                    }
                    else if (sum < target) c++;
                    else d--;
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution18 solu;
    auto a = solu.fourSum(*new vector<int>{1,0,-1,0,-2,2}, 0);
    return 0;
}