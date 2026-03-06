/*
url: https://leetcode.cn/problems/minimum-cost-to-split-into-ones/
标签: LeetCode第491场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3857 {
public:
    int minCost(int n) {
        vector<int> f(n + 1, INT_MAX);
        f[1] = 0;
        for (int i = 2; i <= n; i++) {
            for (int a = 1; a < i; a++) {
                int b = i - a;
                f[i] = min(f[i], f[a] + f[b] + a * b);
            }
        }
        return f[n];
    }

    /* 参考灵茶题解，数学，
    这题用 O(n^2) 的 dp 可以做，但是有直接的公式含义，
    对于 f(n) ，考虑 n 个点的完全图，f(n) = f(a) + f(b) + a * b，a * b 这个代价恰好是左边分 a 个点，右边分 b 个点
    的边数，所以答案为 C_{n}^{2}，且无论怎么划分 a, b ，结果都是一样的。
    */
    int minCost_impl2(int n) {
        return n * (n - 1) / 2;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}