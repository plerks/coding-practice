/*
url: https://leetcode.cn/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/
标签: 【算法题单】位运算, LogTrick
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2654 {
public:
    /* 如果gcd(nums)不为1的话，就操作不出来，返回-1，否则可以。
    先操作出1，即用LogTrick找最短的gcd为1的子数组。
    */
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int t = 0;
        for (int x : nums) t = __gcd(t, x);
        if (t != 1) return -1;

        int cnt_one = 0;
        for (int x : nums) if (x == 1) cnt_one++;
        if (cnt_one) return n - cnt_one; // 如果原本就有1，不管有多少个1，分布如何，一定是 n - cnt_one

        int min = INT_MAX;
        for (int i = 0; i < n; i++) { // 枚举右端点
            if (nums[i] == 1) {
                min = 1;
                break;
            }
            for (int j = i - 1; j >= 0; j--) {
                if (__gcd(nums[i], nums[j]) == nums[j]) break;
                nums[j] = __gcd(nums[i], nums[j]);
                if (nums[j] == 1) min = std::min(min, i - j + 1);
                // 前面可能还有1，但是一定不是最短的子数组
            }
        }
        
        return 2 * (min - 1) + n - min;
    }
};

int main(int argc, char const *argv[]) {
    Solution2654 solu;
    // cout << solu.minOperations(*new vector<int>{2,6,3,4}) << endl;
    cout << solu.minOperations(*new vector<int>{6,10,15}) << endl;
    cout << solu.minOperations(*new vector<int>{1,1}) << endl;
    return 0;
}