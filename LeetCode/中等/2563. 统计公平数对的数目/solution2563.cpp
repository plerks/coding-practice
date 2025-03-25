/*
url: https://leetcode.cn/problems/count-the-number-of-fair-pairs/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2563 {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int r1 = n - 1, r2 = n - 1;
        long long ans = 0;
        for (int l = 0; l < n; l++) {
            while (r1 > l && nums[r1] + nums[l] >= lower) r1--;
            while (r2 > l && nums[r2] + nums[l] > upper) r2--;
            // 右端点取值为(r1, n - 1] 并 (l, r2]
            int ll = max(r1, l);
            int rr = min(n - 1, r2);
            ans += max(0, rr - ll);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2563 solu;
    cout << solu.countFairPairs(*new vector<int>{0,1,7,4,4,5}, 3, 6) << endl;
    return 0;
}