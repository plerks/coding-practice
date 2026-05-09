/*
url: https://leetcode.cn/problems/count-fancy-numbers-in-a-range/
参考: https://leetcode.cn/problems/count-fancy-numbers-in-a-range/solutions/3925643/zhuang-tai-ji-shu-wei-dppythonjavacgo-by-4gpn/
相关: LeetCode2376. 统计特殊整数, LeetCode2999. 统计强大整数的数目
标签: 数位dp
*/

#include <bits/stdc++.h>

using namespace std;

bool is_good(int sum) { // 数位和是否为好数
    if (sum < 100) {
        return sum / 10 != sum % 10;
    }
    else {
        // 百位一定为 1，因此数位和要是好数只能是严格单增的
        return (sum / 10) % 10 > 1 && sum % 10 > (sum / 10) % 10;
    }
};

vector<long long> type2; // 数位和不是好数，但本身是好数

auto init = []() -> int {
    for (int mask = 1; mask < (1 << 10); mask++) {
        long long x = 0;
        int digit_sum = 0;
        // 严格单减的部分
        for (int i = 9; i >= 0; i--) {
            if ((mask >> i) & 1) {
                digit_sum += i;
                x = x * 10 + i;
            }
        }
        if (!is_good(digit_sum)) type2.push_back(x);
        // 严格单增的部分
        if (mask & 1) continue; // 不能有 0
        x = 0;
        digit_sum = 0;
        for (int i = 1; i < 10; i++) {
            if ((mask >> i) & 1) {
                digit_sum += i;
                x = x * 10 + i;
            }
        }
        if (!is_good(digit_sum)) type2.push_back(x);
    }
    sort(type2.begin(), type2.end()); // 排序方便统计 [l, r] 的 type2 的个数
    return 0;
}();

class Solution3869 {
public:
    /* 灵茶题解解法二，
    答案包括两部分：
        1. 数位和是好数的个数。其总数可以用数位dp来求
        2. 数位和不是好数，但本身是好数。本身是好数怎么判断？严格单增的话就是 {1-9} 的真子集，严格单减的话就是 {0-9} 的真子集，
            好数一共有 2^10 - 1 + 2^9 - 1 个。可以通过枚举子集来求出所有好数
    */
    long long countFancy(long long l, long long r) {
        // 数位dp 求 [l, r] 范围内的 type1 个数
        string low_s = to_string(l);
        string high_s = to_string(r);
        int n = high_s.size();
        int pos = n - low_s.size();

        vector memo(n, vector<long long>(9 * n + 1, -1));

        // 求范围内所有数位和是好数的个数
        auto dfs = [&](auto& dfs, int i, int digit_sum, bool is_tight_low, bool is_tight_high) -> long long {
            if (i == n) {
                return is_good(digit_sum);
            }
            long long &ref = memo[i][digit_sum];
            if (!is_tight_low && !is_tight_high && memo[i][digit_sum] != -1) {
                return ref;
            }
            int lo = is_tight_low && i >= pos ? low_s[i - pos] - '0' : 0;
            int hi = is_tight_high ? high_s[i] - '0' : 9;

            long long res = 0;
            int d = lo;
            // 通过 is_tight_low 和 i 可以判断能否不填数字，无需 is_num 参数。也可以用 digit_sum == 0 && i < pos 判断
            if (is_tight_low && i < pos) {
                res += dfs(dfs, i + 1, 0, true, false); // 无数字的话下界贴着，上界不贴着
                d = 1;
            }
            for (; d <= hi; d++) {
                res += dfs(dfs, i + 1, digit_sum + d, is_tight_low && d == lo, is_tight_high && d == hi);
            }
            
            if (!is_tight_low && !is_tight_high) {
                ref = res;
            }

            return res;
        };

        long long part1 = upper_bound(type2.begin(), type2.end(), r) - lower_bound(type2.begin(), type2.end(), l);
        long long part2 = dfs(dfs, 0, 0, true, true);
        return part1 + part2;
    }
};

int main(int argc, char const *argv[]) {
    Solution3869 solu;
    // cout << solu.countFancy(8, 10) << endl;
    cout << solu.countFancy(13, 135) << endl;
    return 0;
}