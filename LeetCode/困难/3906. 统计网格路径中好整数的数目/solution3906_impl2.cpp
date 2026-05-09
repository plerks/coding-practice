/*
url: https://leetcode.cn/problems/count-good-integers-on-a-grid-path/
参考: https://leetcode.cn/problems/count-good-integers-on-a-grid-path/solutions/3954671/shang-xia-jie-shu-wei-dppythonjavacgo-by-feyc/
相关: LeetCode3251. 单调数组对的数目 II, LeetCode3519. 统计逐位非递减的整数
标签: 数位dp, 组合数学
*/
#include <bits/stdc++.h>

using namespace std;

constexpr int MX = 7; // 可以取等到的最大范围
long long comb[7 + 10][10];
auto init = [] {
    // 用 C_{n}^{m} = C_{n - 1}^{m - 1} + C_{n - 1}^{m} 递推预处理组合数
    for (int i = 0; i < 17; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= min(i, 9); j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    return 0;
}();

// 也可以预处理递推求 10 的幂次
long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

class Solution3906 {
public:
    /* 灵茶题解解法二，组合数学的解法，
    用 {< r + 1} - {< l}，
    如何求 < s 的合法方案数，
    假设前面的位置都是紧贴上界 s 的（没贴紧的方案数已经被计数，下一轮循环接着求前缀贴紧 s 的方案数。此外由于是求 {< s} 的方案数，s 本身不用考虑），
    1. 若 s[i] 不在路径上，设 hi = s[i] ，则对于当前位置填 0, 1, ... , hi - 1 的部分，
        后面还有 n - 1 - i 个位置，假设这些位置中有 m 个是路径上的位置，则由 LeetCode3519，这些
        位置的总方案数为 hi * C_{m + 10 - 1 - pre}^{m} * 10^{n - 1 - i - m}
    2. 若 s[i] 在路径上，则对于当前位置填 0, 1, ... , hi - 1 的部分，由 LeetCode3519，总方案数为
        ( C_{m + 10 - pre}^{10 - 1 - pre} - C_{m + 10 - hi}^{10 - 1 - hi} ) * 10^{n - 1 - i - m}
    */
    long long countGoodIntegersOnPath(long long l, long long r, string directions) {
        string high = to_string(r + 1); // 这里 +1 了
        int n = high.size();
        string low = to_string(l);
        low = string(n - low.size(), '0') + low; // 补齐

        vector<int> in_path(n); // r 长度的 n 个位置，哪些地方在路径上
        int pos = n - 16; // 左上角的位置，可能为负
        for (char c : directions) {
            if (pos >= 0) {
                in_path[pos] = true;
            }
            if (c == 'D') pos += 4;
            else pos += 1;
        }
        in_path[n - 1] = true; // 终点一定在路径中

        vector<int> suf(n + 1); // 后缀路径点位数
        for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] + in_path[i];

        auto calc = [&](string& s) -> long long {
            long long res = 0;
            int pre = 0;
            for (int i = 0; i < n; i++) {
                int hi = s[i] - '0';
                int m = suf[i + 1];
                if (!in_path[i]) {
                    res += hi * comb[m + 10 - 1 - pre][m] * fastPow(10, n - 1 - i - m);
                }
                else {
                    if (hi < pre) break;
                    res += (comb[m + 10 - pre][10 - 1 - pre] - comb[m + 10 - hi][10 - 1 - hi]) * fastPow(10, n - 1 - i - m);
                    pre = hi;
                }
            }
            return res;
        };

        return calc(high) - calc(low);
    }
};

int main(int argc, char const *argv[]) {
    Solution3906 solu;
    // cout << solu.countGoodIntegersOnPath(8, 10, "DDDRRR") << endl;
    cout << solu.countGoodIntegersOnPath(123456789, 123456790, "DDRRDR") << endl;
    return 0;
}