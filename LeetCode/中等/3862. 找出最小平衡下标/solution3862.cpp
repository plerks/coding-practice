/*
url: https://leetcode.cn/problems/find-the-smallest-balanced-index/
标签: LeetCode第492场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3862 {
public:
    // 周赛时的解法，这题 n 是 1e5 ，nums[i] 是 1e9，后缀是乘，需要开 i128 ，且乘完后若 > inf ，变成 inf
    int smallestBalancedIndex(vector<int>& nums) {
        int n = nums.size();
        using i128 = __int128_t;
        vector<i128> pre(n + 1);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + nums[i];
        const i128 inf = 1e14 + 1;
        vector<i128> suf(n + 1, 1);
        for (int i = n - 1; i >= 0; i--) {
            if (suf[i + 1] == inf) suf[i] = inf;
            else {
                suf[i] = suf[i + 1] * nums[i];
                if (suf[i] >= inf) suf[i] = inf;
            }
            // suf[i + 1] * nums[i] 不会爆 i128，也可以写成：suf[i] = min(inf, suf[i + 1] * nums[i]);
        }
        for (int i = 0; i < n; i++) {
            if (pre[i - 1 + 1] == suf[i + 1]) return i;
        }
        return -1;
    }

    // 参考灵茶题解，可以不开 i128，但是有步 乘 要转化成 除
    int smallestBalancedIndex_impl2(vector<int>& nums) {
        int n = nums.size();
        vector<long long> pre(n + 1);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + nums[i];
        long long mul = 1;
        // 倒着来，一但 mul 更大，就可以跳出循环，这样也可以避免一直乘溢出
        // 且由于相等最多只会有一处，倒着循环不会影响返回最小的合法位置
        for (int i = n - 1; i >= 1; i--) {
            if (pre[i - 1 + 1] == mul) return i;
            // if (mul * nums[i] > pre[i - 1]) break; // 这样写不行，(mul = 1e14) * (nums[i] = 1e9) 会爆 long long
            if (mul > pre[i - 1] / nums[i]) break; // 但是对于都是整数下的 > ，乘 等价于 除过来(对 >= 不行)
            mul *= nums[i];
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}