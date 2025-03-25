/*
url: https://leetcode.cn/problems/find-the-power-of-k-size-subarrays-ii/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3255 {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n - k + 1);
        for (int i = 0; i <= n - k;) {
            int start = i;
            for (i++; i < n && nums[i] == 1 + nums[i - 1]; i++);
            // [start, i)
            for (int j = start; j <= n - k && j <= i - 1; j++) {
                if (j + k - 1 <= i - 1) {
                    ans[j] = nums[j] + k - 1;
                }
                else ans[j] = -1;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3255 solu;
    // auto a = solu.resultsArray(*new vector<int>{1,2,3,4,3,2,5}, 3);
    auto b = solu.resultsArray(*new vector<int>{2,3}, 2);
    return 0;
}