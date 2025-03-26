/*
url: https://leetcode.cn/problems/minimum-absolute-sum-difference/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1818 {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        long long ans = 0;
        const int mod = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            ans += abs(nums1[i] - nums2[i]);
        }
        vector<int> nums = nums1;
        sort(nums.begin(), nums.end());
        long long t = ans;
        for (int i = 0; i < n; i++) { // 枚举替换位置
            int x = nums2[i];
            // 寻找nums1中最后一个<=x的，和第一个>x的
            int index = upper_bound(nums.begin(), nums.end(), x) - nums.begin() - 1;
            if (index != -1) ans = min(ans, t - abs(nums1[i] - x) + abs(nums[index] - x));
            index++;
            if (index != n) ans = min(ans, t - abs(nums1[i] - x) + abs(nums[index] - x));
        }
        return ans % mod;
    }
};

int main(int argc, char const *argv[]) {
    Solution1818 solu;
    cout << solu.minAbsoluteSumDiff(*new vector<int>{1,7,5}, *new vector<int>{2,3,5}) << endl;
    return 0;
}