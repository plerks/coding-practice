/*
url: https://leetcode.cn/problems/valid-triangle-number/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution611 {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        sort(nums.begin(), nums.end());
        int l = upper_bound(nums.begin(), nums.end(), 0) - nums.begin();
        for (; l < n - 2; l++) {
            int r = l + 2; // 现在m, r的运动方向是右右。把m改成倒着枚举，r和m还是同向双指针，运动方向变成左左
            for (int m = l + 1; m < n - 1; m++) {
                while (r < n && nums[l] + nums[m] > nums[r]) {
                    r++;
                }
                // [m + 1, r)
                ans += r - m - 1;
            }
        }
        return ans;
    }

    // 参考灵茶题解，换成枚举最长边，l和m会是相向双指针，且会自然排除nums[i]为0的情况
    int triangleNumber_implementation2(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        sort(nums.begin(), nums.end());
        for (int r = 2; r < n; r++) {
            int l = 0;
            // m, l运动方向左右
            for (int m = r - 1; m > 0; m--) { // m正序枚举，运动方向变成右左(m右l左)
                while (l < m && nums[l] + nums[m] <= nums[r]) {
                    l++;
                }
                // 最短边 ∈ [l, m)
                ans += max(0, m - l);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution611 solu;
    cout << solu.triangleNumber(*new vector<int>{2,2,3,4}) << endl;
    cout << solu.triangleNumber_implementation2(*new vector<int>{2,2,3,4}) << endl;
    cout << solu.triangleNumber_implementation2(*new vector<int>{7,0,0,0}) << endl;
    return 0;
}