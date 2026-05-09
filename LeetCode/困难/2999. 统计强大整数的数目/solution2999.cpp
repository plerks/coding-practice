/*
url: https://leetcode.cn/problems/count-the-number-of-powerful-integers/
参考: https://www.bilibili.com/video/BV1Fg4y1Q7wv/
      https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/2595149/shu-wei-dp-shang-xia-jie-mo-ban-fu-ti-da-h6ci/
标签: 数位dp
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2999 {
public:
    /* 数字范围过大，但是比方说对于：第 1 位填 1...5，后面的后缀对于第一位填的 1...5 都是一样的，所以可以用记忆化搜索优化。
    可以转成 [0, hi] - [0, lo - 1] ，但是也可以不用算两次，直接算。

    时间复杂度 O(位数)，虽然上下限范围为 1e15，但是时间复杂度只有 O(15)
    */
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string low = to_string(start);
        string high = to_string(finish);
        low = string(high.size() - low.size(), '0') + low; // 补前导 0 对齐
        int n = high.size();
        int pos = n - s.size(); // >= pos 的部分必须填成 s 的内容
        vector<long long> memo(n, -1);
        
        // 填到第 i 位，is_limit_low 和 is_limit_high 表示之前填的数字是否是贴着上下限填的
        auto dfs = [&](auto& dfs, int i, bool is_limit_low, bool is_limit_high) -> long long {
            if (i == n) {
                return 1;
            }
            if (!is_limit_low && !is_limit_high && memo[i] != -1) {
                return memo[i];
            }
            // 为了保持数值的大小在 [low, high] ，这一位的范围
            int lo = is_limit_low ? low[i] - '0' : 0;
            int hi = is_limit_high ? high[i] - '0' : 9;
            long long res = 0;
            if (i < pos) {
                for (int d = lo; d <= min(hi, limit); d++) {
                    res += dfs(dfs, i + 1, is_limit_low && d == lo, is_limit_high && d == hi);
                }
            }
            else {
                int d = s[i - pos] - '0';
                if (lo <= d && d <= hi) { // 题目保证 x <= limit，无需判断
                    res += dfs(dfs, i + 1, is_limit_low && d == lo, is_limit_high && d == hi);
                }
            }

            // 只记忆 false, false 的 i ，贴着上下限的不会被重复访问，无需记忆，(i, 贴着上/下限的状态) 变了之后，不会重新进入
            if (!is_limit_low && !is_limit_high) {
                memo[i] = res;
            }
            return res;
        };

        return dfs(dfs, 0, true, true); // 最开始是 true, true ，因为例如第一位填上下限数字之后，前缀该被认定为贴紧上下限
    }
};

int main(int argc, char const *argv[]) {
    Solution2999 solu;
    cout << solu.numberOfPowerfulInt(1, 6000, 4, "124") << endl;
    return 0;
}