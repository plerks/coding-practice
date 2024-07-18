/*
url: https://leetcode.cn/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-ii/description/
参考: https://www.bilibili.com/video/BV17w4m1e7Nw/
标签: LeetCode第133场双周赛, 贪心
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3192 {
public:
    int minOperations(vector<int>& nums) {
        // 考虑全1变为nums，如果考虑nums变为全1，则后缀部分不整齐，需要一个个去改，则复杂度O(n^2)
        /* 与LeetCode3191. 使二进制数组全部等于 1 的最少操作次数 I相同，操作顺序无关。一开始是全1，考虑
        从左到右操作，如果当前位置不是nums想要的，则需要反转[i, n)，后缀的值和当前处理的位置是相等的，因此
        处理i位置时，用pre记录i - 1位置的值，就是当前nums[i]的值
        */
        int n = nums.size();
        int ans = 0;
        if (nums[0] == 0) ans = 1;
        int pre = nums[0];
        for (int i = 1; i < n; i++) {
            int num = nums[i];
            if (num != pre) {
                ans++;
                pre = num;
            }
        }
        return ans;
    }

    // 灵茶山艾府解法，不用反过来考虑，从左到右考虑，当前位置的值由反转次数决定，因此知道反转次数就可以知道当前位置的值，不用把后缀一个个改
    int minOperations_implementation2(vector<int>& nums) {
        int ans = 0;
        // 若num原本是0，且反转次数为偶数，则ans需要++
        // 若num原本是1，且反转次数为奇数，则ans需要++
        // 于是，总结为num == ans % 2时，ans需要++
        for (int num : nums) {
            if (num == ans % 2) ans++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
