/*
url: https://leetcode.cn/problems/valid-triangle-number/
相关: LeetCode1577. 数的平方等于两数乘积的方法数
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
        for (int r = 2; r < n; r++) { // r改成从大到小枚举无影响，后两个位置l, m的滑窗枚举是个黑盒
            int l = 0;
            // m, l运动方向左右，相向双指针
            for (int m = r - 1; m > 0; m--) {
                while (l < m && nums[l] + nums[m] <= nums[r]) {
                    l++;
                }
                // 最短边 ∈ [l, m)
                ans += max(0, m - l);
            }
        }
        return ans;
    }

    // 结合LeetCode15. 三数之和，18. 四数之和，涉及到要枚举多个位置时，双指针只能把最后两个位置的枚举从O(n^2)优化到O(n)


    /* 这样想的反向双指针看似是对的，但是是错的：m正序枚举，m增大，则临界l变小，m右l左，反向双指针。
    现在双指针在l, m，如果开始时就有l + m < r，当m增大时，l + 1，m + 1可能是正解，这时l不是单调的。
    */
    int triangleNumber_wa(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        sort(nums.begin(), nums.end());
        for (int r = 2; r < n; r++) {
            int l = 0;
            for (int m = 1; m < r; m++) {
                while (l >= 0 && nums[l] + nums[m] > nums[r]) {
                    l--;
                }
                // 最短边 ∈ (l, m)
                ans += max(0, m - l - 1);
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