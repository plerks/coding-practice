/*
url: https://leetcode.cn/problems/3sum/
相关: LeetCode18. 四数之和, LeetCode923. 三数之和的多种可能, LeetCode611. 有效三角形的个数
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution15 {
public:
    // 我的写法。第一个数枚举，第2，3个数用滑窗从n^2优化到n。总时间复杂度O(n^2)
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_set<long long> st;
        const long long N = 1e6 + 1;
        vector<vector<int>> ans;
        for (int l = 0; l < n - 1; l++) {
            int m = l + 1;
            int r = n - 1;
            while (m < r) {
                int sum = nums[l] + nums[m] + nums[r];
                if (sum == 0) {
                    long long hash = nums[l] * N * N + nums[m] * N + nums[r];
                    if (!st.count(hash)) ans.push_back({nums[l], nums[m], nums[r]});
                    st.insert(hash);
                    m++;
                }
                else if (sum < 0) m++;
                else r--;
            }
        }
        return ans;
    }

    // 参考灵茶题解，去重只需要让前后两次指针位置指向的值不同即可
    vector<vector<int>> threeSum_implementation2(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        for (int l = 0; l < n - 1; l++) {
            if (l > 0 && nums[l] == nums[l - 1]) continue; // 跳过重复数字
            int m = l + 1;
            int r = n - 1;
            while (m < r) {
                int sum = nums[l] + nums[m] + nums[r];
                if (sum == 0) {
                    ans.push_back({nums[l], nums[m], nums[r]});
                    m++;
                    while (m < r && nums[m] == nums[m - 1]) m++;
                    // 这里也可以写成：
                    for (m++; m < r && nums[m] == nums[m - 1]; m++);
                    for (r--; r > m && nums[r] == nums[r + 1]; r--);
                }
                else if (sum < 0) m++;
                else r--;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution15 solu;
    auto a = solu.threeSum(*new vector<int>{-1,0,1,2,-1,-4});
    auto b = solu.threeSum(*new vector<int>{-1,0,1,2,-1,-4});
    return 0;
}