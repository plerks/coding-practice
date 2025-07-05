/*
url: https://leetcode.cn/problems/apply-operations-on-array-to-maximize-sum-of-squares/
相关: LeetCode2939. 最大异或乘积
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2897 {
public:
    /*
    00 -> 00
    01 -> 01
    10 -> 01
    11 -> 11
    所以，1的总数不变，分析方式和LeetCode2939很像
    */
    int maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        constexpr long long MOD = 1e9 + 7;
        int cnt[32]{};
        for (int x : nums) {
            for (int i = 0; i < 32; i++) {
                if ((x >> i) & 1) cnt[i]++;
            }
        }
        vector<int> t(k);
        for (int& x : t) {
            for (int i = 0; i < 32; i++) {
                if (cnt[i]) {
                    x |= 1 << i;
                    cnt[i]--;
                }
            }
        }
        long long ans = 0;
        for (long long x : t) {
            ans = (ans + x * x % MOD) % MOD;
        }
        return ans;
    }

    /* 参考灵茶题解，只想着把1都给到k个数里面了，但是没分析这种情况，不过代码是对的：
    现在1不够，101 和 001，是变成 111, 001 还是 101, 011 ？哪种平方和大？
    (x + d)^2 + y^2 = x^2 + y^2 + 2dx + d^2
    x^2 + (y + d)^2 = x^2 + y^2 + 2dy + d^2
    所以，把 d 给 x，y 中的较大者
    */
};

int main(int argc, char const *argv[]) {
    Solution2897 solu;
    cout << solu.maxSum(*new vector<int>{2,6,5,8}, 2) << endl;
    cout << solu.maxSum(*new vector<int>{4,5,4,7}, 3) << endl;
    return 0;
}