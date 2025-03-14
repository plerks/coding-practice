/*
url: https://leetcode.cn/problems/subarray-product-less-than-k/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution713 {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        int product = 1; // 乘积
        int ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            product *= nums[r];
            while (l <= r && product >= k) { // 这题必须写l <= r
                product /= nums[l];
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution713 solu;
    cout << solu.numSubarrayProductLessThanK(*new vector<int>{10,5,2,6}, 100) << endl;
    cout << solu.numSubarrayProductLessThanK(*new vector<int>{1,2,3}, 0) << endl;
    return 0;
}