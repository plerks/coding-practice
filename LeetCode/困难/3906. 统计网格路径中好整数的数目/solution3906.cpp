/*
url: https://leetcode.cn/problems/count-good-integers-on-a-grid-path/
参考: https://leetcode.cn/problems/count-good-integers-on-a-grid-path/solutions/3954671/shang-xia-jie-shu-wei-dppythonjavacgo-by-feyc/
相关: LeetCode3519. 统计逐位非递减的整数
标签: 数位dp, 组合数学
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3906 {
public:
    long long countGoodIntegersOnPath(long long l, long long r, string directions) {
        string low_s = to_string(l);
        string high_s = to_string(r);
        int n = high_s.size();
        int diff_lh = n - low_s.size();

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
        vector<vector<long long>> memo(n, vector<long long>(10)); // memo 存的值都 +1 ，以 0 为初值，这样可以避免初始化为 -1

        auto dfs = [&](auto& dfs, int i, int pre, bool is_tight_low, bool is_tight_high) -> long long {
            if (i == n) return 1;
            if (!is_tight_low && !is_tight_high && memo[i][pre] > 0) {
                return memo[i][pre] - 1;
            }

            int lo = is_tight_low && i >= diff_lh ? low_s[i - diff_lh] - '0' : 0;
            int hi = is_tight_high ? high_s[i] - '0' : 9;

            long long res = 0;
            int start = lo;
            if (in_path[i]) start = max(lo, pre);
            for (int d = start; d <= hi; d++) {
                res += dfs(dfs, i + 1, in_path[i] ? d : pre, is_tight_low && d == lo, is_tight_high && d == hi);
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
    Solution3906 solu;
    cout << solu.countGoodIntegersOnPath(8, 10, "DDDRRR") << endl;
    cout << solu.countGoodIntegersOnPath(123456789, 123456790, "DDRRDR") << endl;
    return 0;
}