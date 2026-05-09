/*
url: https://leetcode.cn/problems/count-fancy-numbers-in-a-range/
参考: https://leetcode.cn/problems/count-fancy-numbers-in-a-range/solutions/3925643/zhuang-tai-ji-shu-wei-dppythonjavacgo-by-4gpn/
相关: LeetCode2376. 统计特殊整数, LeetCode2999. 统计强大整数的数目
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3869 {
public:
    /* 参考灵茶题解。
    奇妙数可以是本身是好数（类型1），也可以是数位和是好数（类型2）。
    数字范围很大，1 <= l <= r <= 10^15，但是类型1由于数位要严格单调，所以只会有一小部分是好数。
    但是对于类型2，数位和是好数就行，这样来看像 88 (8 + 8 = 16) 也行，是否需要枚举范围内的所有数(指数级)？
    不用，我们只关心数位和，而数位和的范围并不大，对于枚举到第 i 位时，只需关心前缀的数位和是多少，并不需要
    考虑所有情况，例如 123xxx 和 321xxx ，只需在状态上记录 digit_sum 是 6 就行了(把"123""321"等等的状态都压成了6)。
    原本调用关系里这一层有很多个节点(3个数位的总和为6，有组合数种方案)，但现在被压缩成了单个状态，只关心被压缩后的状态，而状态数不多，
    因此，只需通过 digit_sum 这个状态搜索类型2就行了。

    类型1 和 类型2 可以写在一个记忆化搜索里，关键要记录的状态分别是 prev 和 digit_sum

    时间复杂度 O(10 * 最大位数 * (最大位数 * 10) * 10) = O(D^3 * log^2{r})，D = 10，r 为数据范围，logr 为位数
    */
    long long countFancy(long long l, long long r) {
        string low_s = to_string(l);
        string high_s = to_string(r);
        int n = high_s.size();
        int pos = n - low_s.size();

        enum State {INIT, INC, DEC, ILLEGAL}; // INIT 表示至多填了一个数

        // 最多 15 位，sum最大为 15 * 9
        auto is_good = [&](int sum) -> bool {
            if (sum < 100) {
                return sum / 10 != sum % 10;
            }
            else {
                // 百位一定为 1，因此数位和要是好数只能是严格单增的
                return (sum / 10) % 10 > 1 && sum % 10 > (sum / 10) % 10;
            }
        };

        // 只用记忆非贴紧上下限的，即 (false, false) 的。用 0 来当初值避免初始化，后续返回时再 -1 (也就是记忆化整体都偏移 +1 了)
        vector memo(n, vector<array<array<long long, 4>, 10>>(n * 9 + 1));

        /* i 表示填了几位，prev 表示上一位的数字，digit_sum 位前缀数位和，state 为当前状态，
        is_tight 表示是否当前填成的紧贴上下限的状态
        */
        auto dfs = [&](auto& dfs, int i, int digit_sum, int prev, int state, bool is_tight_low, bool is_tight_high) -> long long {
            if (i == n) {
                // 填完了，要么本身是好数，要么数位和是好数
                return state != State::ILLEGAL || is_good(digit_sum);
            }

            auto& ref = memo[i][digit_sum][prev][state];
            if (!is_tight_low && !is_tight_high && ref != 0) {
                return ref - 1;
            }

            int lo = is_tight_low && i >= pos ? low_s[i - pos] - '0' : 0;
            int hi = is_tight_high ? high_s[i] - '0' : 9;

            long long res = 0;
            int d = lo;
            // 现在为没填过数的状态，保持为不填数
            // 无需用 is_num 判断现在是否已经填了数字进去了，用 is_tight_low / digit_sum 就行
            if (digit_sum == 0 && i < pos) {
                res += dfs(dfs, i + 1, digit_sum, 0, INIT, true, false);
                d = 1; // 后面尝试填入第一个有效的数字，必须至少是 1
            }
            // 现在是 没填过数的状态 / 已经填了数的状态，要填数
            for (; d <= hi; d++) {
                int new_state = state;
                // 转移状态
                switch(state) {
                    case INIT:
                        if (prev > 0) { // prev == 0 ，填第一个数之后还是 INIT 状态，不用管
                            // INIT 状态且 prev > 0 表示填过一个数了
                            if (d > prev) new_state = INC;
                            else if (d < prev) new_state = DEC;
                            else new_state = ILLEGAL;
                        }
                        break;
                    case INC:
                        if (d <= prev) new_state = ILLEGAL;
                        break;
                    case DEC:
                        if (d >= prev) new_state = ILLEGAL;
                        break;
                }
                res += dfs(dfs, i + 1, digit_sum + d, d, new_state, is_tight_low && d == lo, is_tight_high && d == hi);
            }

            if (!is_tight_low && !is_tight_high) {
                ref = res + 1;
            }
            return res;
        };

        return dfs(dfs, 0, 0, 0, INIT, true, true);
    }
};

int main(int argc, char const *argv[]) {
    Solution3869 solu;
    cout << solu.countFancy(8, 10) << endl;
    cout << solu.countFancy(0, 0) << endl;
    return 0;
}