/*
url: https://leetcode.cn/problems/manhattan-distances-of-all-arrangements-of-pieces/
参考: https://leetcode.cn/problems/manhattan-distances-of-all-arrangements-of-pieces/solutions/3051398/gong-xian-fa-yu-chu-li-hou-o1pythonjavac-2hgt/
标签: LeetCode第148场双周赛, 贡献法
*/

// 这次双周赛2题

#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 - 2 + 1; // 具体题目需要涉及到的最大范围
const int MOD = (int)(1e9 + 7); // 具体题目要mod的素数

long long fac[MX];
long long inv_fac[MX]; // 逆元

long long fastPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if ((b & 1) != 0) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

auto init = []() {
    fac[0] = 1;
    for (int i = 1; i < MX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv_fac[MX - 1] = fastPow(fac[MX - 1], MOD - 2);
    for (int i = MX - 2; i >= 0; i--) {
        inv_fac[i] = inv_fac[i + 1] * (i + 1) % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

class Solution3426 {
public:
    /* 参考灵茶题解，贡献法，
    先从题目给的示例2来分析，1行4列，只有xi的绝对差，
    xi的绝对差为1，有多少种情况？
    (xi, xi + 1)共有3个位置可以放，注意: 不要把这两个位置的内部交换计数，也不要把剩下的1个球与这俩个球构成的绝对差计数，否则都会导致重复计数，
    共C(2,1) * 3 = 6种情况
    xi的绝对差为2，有多少种情况？C(2,1) * 2 = 4
    xi的绝对差为3，有多少种情况？C(2,1) * 1 = 2
    所以结果为 1 * 6 + 2 * 4 + 3 * 2 = 20

    推公式：
    先只考虑|xi - xj|，xi和xj构成绝对差d在x方向上有n-d种情况，在y方向上有m^2种情况，剩下的k-2个球有C(mn-2, k-2)种放法，
    绝对差总共 C(mn-2, k-2) * m^2 * ∑(d=1, n-1) d*(n-d)
    将 d*(n-d) 求和出来，结果为 C(mn-2, k-2) * m^2 * (n-1)n(n+1)/6
    对称地，y方向上为 C(mn-2, k-2) * n^2 * (m-1)m(m+1)/6，
    这里 (n-1)n(n+1)/6 有除法，用6的逆元
    相加即可。
    */
    int distanceSum(int m, int n, int k) {
        int inv_6 = fastPow(6, MOD - 2);
        return (comb(m * n - 2, k - 2) * (long long)m % MOD * m % MOD * (long long)(n - 1) % MOD * n % MOD * (n + 1) % MOD * inv_6 % MOD + 
                comb(m * n - 2, k - 2) * (long long)n % MOD * n % MOD * (long long)(m - 1) % MOD * m % MOD * (m + 1) % MOD * inv_6 % MOD) % MOD;
    }
};

int main(int argc, char const *argv[]) {
    Solution3426 solu;
    cout << solu.distanceSum(2,2,2) << endl;
    return 0;
}