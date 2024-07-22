/*
url: https://leetcode.cn/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/
相关: LeetCode3229. 使数组等于目标数组所需的最少操作次数
标签: LeetCode第133场双周赛, 贪心
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3191 {
public:
    /* 考虑一个操作序列，最终nums的状态是与操作顺序无关的，原因是，对于特定的操作序列，某个位置的num，其反转次数是确定的，因此
    操作顺序无关，于是，考虑从左到右进行最优操作，如果当前位置是0则需要在这个位置上进行反转，然后继续往右。
    */
    int minOperations(vector<int>& nums) {
        // 考虑全1变为nums
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n;) {
            if (nums[i] == 0) {
                if (i > n - 3) return -1;
                ans++;
                nums[i] ^= 1; // 0-1反转
                if (i + 1 < n) nums[i + 1] ^= 1;
                if (i + 2 < n) nums[i + 2] ^= 1;
                while (i < n && nums[i] == 1) i++;
            }
            else i++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
