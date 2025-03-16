/*
url: https://leetcode.cn/problems/binary-subarrays-with-sum/
标签: 【题单】滑动窗口与双指针, 恰好型滑动窗口
*/
#include <bits/stdc++.h>

using namespace std;

class Solution930 {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // 此题nums[i]不是0就是1，对每个右边界，找第一个和为goal的左边界，和第一个和为goal - 1的左边界
        // 若改成nums[i]不一定0，1，而是为非负整数，那么变成找第一个和为 goal 的左边界，和第一个和 < goal (<= goal - 1)的左边界
        // 但是 == goal 无法作为滑窗的控制条件，如果没有恰好等于goal的会一直滑，所以改成 { <= goal } - { <= goal - 1 } = { == goal }
        // 或者 { >= goal } - { >= goal - 1 }
        int n = nums.size();
        int l1 = 0;
        int l2 = 0; // 两个l一起滑
        int sum1 = 0;
        int sum2 = 0;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            sum1 += nums[r];
            sum2 += nums[r];
            while (sum1 > goal) sum1 -= nums[l1++];
            while (l2 <= r && sum2 > goal - 1) sum2 -= nums[l2++]; // 0 <= goal <= nums.length，空窗口不会自动退出
            // [l1, r] - [l2, r] 
            ans += (r - l1 + 1) - (r - l2 + 1);
        }

        // 另外一种写法，{ >= goal } - { >= goal + 1 }
        /* for (int r = 0; r < n; r++) {
            sum1 += nums[r];
            sum2 += nums[r];
            while (l1 <= r && sum1 >= goal) sum1 -= nums[l1++]; // goal为0时，空窗口sum1 >= 0，这种写法这里也要加上 l <= r
            while (l2 <= r && sum2 >= goal + 1) sum2 -= nums[l2++]; // 0 <= goal <= nums.length，空窗口不会自动退出
            // [0, l1) - [0, l2)
            ans += l1 - l2;
        } */
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution930 solu;
    cout << solu.numSubarraysWithSum(*new vector<int>{1,0,1,0,1}, 2) << endl;
    return 0;
}