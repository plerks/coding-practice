// https://leetcode.cn/problems/count-commas-in-range-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution3871 {
public:
    // 周赛时的解法
    long long countCommas(long long n) {
        using i64 = long long;
        string s = to_string(n);
        i64 len = s.size();
        i64 ans = 0;
        for (i64 l = 1; l < len; l++) {
            ans += (l - 1) / 3 * 9 * pow(10LL, l - 1);
        }
        ans += (len - 1) / 3 * (n - pow(10LL, len - 1) + 1);
        return ans;
    }

    // 灵茶题解解法一，贡献法的思路，最右边的逗号出现在 [1e3, n] 中
    // 倒数第二个逗号出现在 [1e6, n] 中
    // 时间复杂度 O(logn)
    long long countCommas_impl2(long long n) {
        long long ans = 0;
        for (long long low = 1000; low <= n; low *= 1000) {
            ans += n - low + 1;
        }
        return ans;
    }

    // 灵茶题解解法二，直接用公式
    // 设 k 是满足 10^{3k} <= n 的最大整数，则答案为
    // (n - 10^3 + 1) + (n - 10^6 + 1) + ... + (n - 10^3k + 1)
    // = k(n + 1) - (10^{3k+3} - 1000) / 999
    // 时间复杂度 O(1)
    long long countCommas_impl3(long long n) {
        string s = to_string(n);
        long long k = (s.size() - 1) / 3;
        return k * (n + 1) - (pow(10, 3 * k + 3) - 1000) / 999;
    }
};

int main(int argc, char const *argv[]) {
    Solution3871 solu;
    cout << solu.countCommas(1002) << endl;
    cout << solu.countCommas_impl3(998) << endl;
    return 0;
}