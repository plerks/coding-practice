/*
url: https://leetcode.cn/problems/count-number-of-nice-subarrays/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1248 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // {>= k} - {>= k + 1} 
        int n = nums.size();
        int l1 = 0;
        int l2 = 0;
        int cnt1 = 0;
        int cnt2 = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            cnt1 += nums[r] % 2;
            cnt2 += nums[r] % 2;
            while (cnt1 >= k) cnt1 -= nums[l1++] % 2;
            while (cnt2 >= k + 1) cnt2 -= nums[l2++] % 2;
            // [0, l1) - [0, l2)
            ans += l1 - l2;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1248 solu;
    cout << solu.numberOfSubarrays(*new vector<int>{1,1,2,1,1}, 3) << endl;
    return 0;
}