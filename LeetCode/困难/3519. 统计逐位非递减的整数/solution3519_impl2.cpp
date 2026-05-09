/*
url: https://leetcode.cn/problems/count-numbers-with-non-decreasing-digits/
参考: https://leetcode.cn/problems/count-numbers-with-non-decreasing-digits/solutions/3649556/mo-ban-shang-xia-jie-shu-wei-dp-by-endle-rhuw/
相关: LeetCode3251. 单调数组对的数目 II, LeetCode3906. 统计网格路径中好整数的数目
标签: 数位dp, 组合数学
*/
#include <bits/stdc++.h>

using namespace std;

constexpr int MX = 400; // 可以取等到的最大范围
long long comb[400][10];
auto init = [] {
    // 用 C_{n}^{m} = C_{n - 1}^{m - 1} + C_{n - 1}^{m} 递推预处理组合数
    for (int i = 0; i < 400; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= min(i, 9); j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    return 0;
}();

class Solution3519 {
public:
    vector<int> convert(string s, int b) {
        // s.length <= 100，改成 b 进制，不能直接转 long long。s 仅由数字（0-9）组成
        for (char& c : s) c -= '0';
        vector<int> digits;
        while (!s.empty()) {
            string next_s; // 商
            int rem = 0; // 余数
            for (char c : s) {
                rem = rem * 10 + c;
                int x = rem / b;
                rem = rem % b;
                if (x || !next_s.empty()) next_s.push_back(x); // x || !next_s.empty() 的判断是为了去掉前导零
            }
            digits.push_back(rem);
            s = next_s;
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }

    /* 灵茶题解解法二，组合数学的解法，
    把 l 和 r 转成 b 进制后，把问题先转化为 [0, r + 1) - [0, l)。
    考虑这个问题，假设之前的位置都是紧贴着边界 s 的，那么如果当前位置的取值为 pre, pre + 1, ... , s[i]，
    如果当前位置的取值 < s[i]，那么此时已经可以确认 <= s 了。那么假设后面的位数为 m ，长为 m 的序列，每位的范围为 [j, b - 1]，
    能有多少种方案？这是 LeetCode3251 灵茶题解解法二，结果为 C_{m + b - 1 - j}^{m}。
    j 为 i 位填的数字，j 从 pre 取到 s[i] - 1 ，记 hi = s[i] ，组合数加起来的结果是:
        ∑_{j = b-hi}^{b-1-pre} C_{m + j}^{m}
    再结合恒等式 C_{m}^{m} + C_{m + 1}^{m} + ... + C_{m + k}^{m} = C_{m + k + 1}^{m + 1} (把 C_{m + k}^{m} = C_{m + k + 1}^{m + 1} - C_{m + k}^{m + 1}，然后裂项相消)，
    于是：∑_{j = b-hi}^{b-1-pre} C_{m + j}^{m}
        = ∑_{j = 0}^{b-1-pre} C_{m + j}^{m} - ∑_{j = 0}^{b-hi-1} C_{m + j}^{m}
        = C_{m + b - pre}^{m + 1} - C_{m + b - hi}^{m + 1}
        = C_{m + b - pre}^{b - 1 - pre} - C_{m + b - hi}^{b - 1 - hi}
    这里 b - 1 很小，组合数会很小，不用求逆元
    */
    long long calc(string& s, int b) { // 计算 < s 的合法方案数
        auto digits = convert(s, b);
        long long res = 0;
        int pre = 0;
        for (int i = 0; i < digits.size() && digits[i] >= pre; i++) { // 不加 && hi >= pre 运行不会越界，有点特殊，hi >= pre 的要求没体现在 comb 的下标中
            int hi = digits[i];
            int m = digits.size() - i - 1;
            // 计数当前位置取值为 pre, pre + 1, ... , hi - 1 时的方案总数
            res += comb[m + b - pre][b - 1 - pre] - comb[m + b - hi][b - 1 - hi];
            // 还没计数的部分是紧贴 s 上界的
            pre = hi;
        }
        return res;
    }

    int countNumbers(string l, string r, int b) {
        const long long mod = 1e9 + 7;
        // 2 <= b <= 10
        long long t = calc(r, b) - calc(l, b); // 本来是 return calc(r + 1, b) - calc(l, b); string 不好 +1，单独判断 r + 1
        auto check_r = [&]() -> int { // 检查 r 的 b 进制是否单增
            auto rr = convert(r, b);
            for (int i = 1; i < rr.size(); i++) {
                if (rr[i - 1] > rr[i]) return false;
            }
            return true;
        };
        return (t + check_r()) % mod;
    }
};

int main(int argc, char const *argv[]) {
    Solution3519 solu;
    // cout << solu.countNumbers("23", "28", 8) << endl;
    // cout << solu.countNumbers("2", "7", 2) << endl;
    cout << solu.countNumbers("1", "5", 2) << endl;
    return 0;
}