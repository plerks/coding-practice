/*
url: https://leetcode.cn/problems/count-numbers-with-non-decreasing-digits/
参考: https://leetcode.cn/problems/count-numbers-with-non-decreasing-digits/solutions/3649556/mo-ban-shang-xia-jie-shu-wei-dp-by-endle-rhuw/
相关: LeetCode3906. 统计网格路径中好整数的数目
标签: 数位dp, 组合数学
*/
#include <bits/stdc++.h>

using namespace std;

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

    // 灵茶题解解法一，数位dp的解法
    int countNumbers(string l, string r, int b) {
        const long long mod = 1e9 + 7;
        // 2 <= b <= 10
        auto low_s = convert(l, b);
        auto high_s = convert(r, b);
        int n = high_s.size();
        int diff_lh = n - low_s.size();

        vector<vector<long long>> memo(n, vector<long long>(b)); // memo 存的值都 +1 ，以 0 为初值，这样可以避免初始化为 -1
        auto dfs = [&](auto& dfs, int i, int pre, bool is_tight_low, bool is_tight_high) -> long long {
            if (i == n) return 1;
            if (!is_tight_low && !is_tight_high && memo[i][pre] > 0) {
                return memo[i][pre] - 1;
            }

            int lo = is_tight_low && i >= diff_lh ? low_s[i - diff_lh]: 0;
            int hi = is_tight_high ? high_s[i]: b - 1;

            long long res = 0;
            int start = max(lo, pre);
            for (int d = start; d <= hi; d++) {
                res += dfs(dfs, i + 1, d, is_tight_low && d == lo, is_tight_high && d == hi);
                res %= mod;
            }

            if (!is_tight_low && !is_tight_high) {
                memo[i][pre] = res + 1; // memo 存的值都 +1 ，以 0 为初值，这样可以避免初始化为 -1
            }
            return res;
        };

        return dfs(dfs, 0, 0, true, true);
    }
};

int main(int argc, char const *argv[]) {
    Solution3519 solu;
    cout << solu.countNumbers("23", "28", 8) << endl;
    return 0;
}