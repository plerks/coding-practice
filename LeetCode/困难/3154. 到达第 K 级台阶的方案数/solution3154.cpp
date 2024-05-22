/*
url: https://leetcode.cn/problems/find-number-of-ways-to-reach-the-k-th-stair/description/
参考: https://www.bilibili.com/video/BV19D421G7mw/
      https://leetcode.cn/problems/find-number-of-ways-to-reach-the-k-th-stair/solutions/2782792/liang-chong-fang-fa-ji-yi-hua-sou-suo-zu-j227/
相关: LeetCode231. 2 的幂
标签: LeetCode第398场周赛, 记忆化搜索, 数学, 组合数学, 隔板法, dp计算组合数
*/

// 这次周赛做出3题

#include <bits/stdc++.h>

using namespace std;

int c[31][31];

/* 立即调用的lambda表达式（Immediately Invoked Lambda Expression，IIFE）实现全局初始化的效果
这样写，右侧是直接调用了的，所以init不是函数对象，而是调用结果，这里init是int类型。
所以这里lambda里必须有返回值，不然就是把void赋值给init，auto推断为void，而void init是非法的，编译不通过。
直接不写`auto init = `，单纯写右边也通不过编译。全局范围下写`[]() {cout << 1 << endl;}();`不能编译，函数里写可以。
*/
auto init = []() {
    for (int i = 0; i <= 30; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j <= i; j++) {
            // dp计算组合数
            // C(n, m) = C(n - 1, m - 1) + C(n - 1, m)，从n个数里选m个，考虑第一个选有C(n - 1, m - 1)种情况，第一个不选有C(n - 1, m)种情况，加起来
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    return 0; // 必须有返回值
}();


class Solution3154 {
public:
    // 周赛时写的暴力解法，370 / 600 个通过的测试用例，超时
    int waysToReachStair_time_limit_exceeded(int k) {
        int ans = 0;
        // lastIsBack表示上一次是否是用的操作1
        function<void(int, bool, int)> dfs = [&](int i, bool lastIsBack, int jump) {
            if (i == k) ans++;
            if (lastIsBack) {
                if ((i > k + 1) && ((2 << jump) > 1) || (i + (1 << jump) > k + 1)) {
                    return;
                }
                else {
                    dfs(i + (1 << jump), false, jump + 1);
                }
            }
            else {
                dfs(i - 1, true, jump);
                if (!((i > k + 1) && ((2 << jump) > 1) || (i + (1 << jump) > k + 1))) {
                    dfs(i + (1 << jump), false, jump + 1);
                }
            }
        };
        dfs(1, 0, 0);
        return ans;
    }

    /* 灵茶山艾府解法一。
    周赛做的时候把dfs()定义成无返回值的，就想不到记忆化搜索那里去，把dfs()的定义改一下，改成有返回值的，
    改成从(i, lastIsBack, jump)状态下，到达k位置的方案数，就能记忆化了。
    视频讲解里还分析了这个记忆化搜索的时间复杂度
    记忆化搜索的时间复杂度为状态个数 * 单个状态的计算时间
    这里单个状态的计算时间为O(1)，状态个数有多少个？
    i为在楼梯上的位置，初始时在1位置，记m为操作1的次数，j为操作2的次数，
    则目前的位置i = 1 + (1 + 2^1 + ... + 2^j) - m = 2^j - m
    由于操作1不能连续做，于是操作1只能以隔板法的形式插入到j中间，于是0 <= m <= j + 1
    且到了i > k + 1后，搜索就会停止，于是还有2^j - m <= k + 1
    于是2^j约等于k + 1，则j是logk规模的，m <= j + 1，则m也是logk规模的，
    于是状态总个数为O(logk * logk)，时间复杂度为O(logk * logk)
    */
    int waysToReachStair(int k) {
        int ans = 0;
        unordered_map<string, int> memo;
        // dfs()定义为从(i, lastIsBack, jump)状态下，到达k位置的方案数，这样就能记忆化
        function<int(int, bool, int)> dfs = [&](int i, bool lastIsBack, int jump) {
            /* 拼接成string来作为查找状态是否已搜索的key，也可以用tuple<int, bool, int>存i, lastIsBack, jump，
            然后把tuple放std::map里，tuple不用自定义hash函数就可以直接往std::map里放，然后通过std::map查找状态。
            */
            string s = to_string(i) + "_" + to_string(lastIsBack) + "_" + to_string(jump);
            if (memo.find(s) != memo.end()) return memo[s];
            int count = 0;
            if (i == k) {
                memo[s] = 1;
                count++;
            }
            if (!lastIsBack && i - 1 >= 0) {
                count += dfs(i - 1, true, jump);
            }
            if (!((i > k + 1) && ((2 << jump) > 1) || (i + (1 << jump) > k + 1))) {
                count += dfs(i + (1 << jump), false, jump + 1);
            }
            memo[s] = count;
            return count;
        };
        return dfs(1, 0, 0);
    }

    /* 灵茶山艾府解法二
    枚举操作2的次数，然后操作1不能连续做，于是操作1只能以隔板法的形式放到操作2内部以及左右的n + 1个隔板位置
    假设操作2做了j次，则操作1的次数m = 2^j - k。
    j能是多少？
    0 <= m = 2^j - k，所以2^j >= k，如果k只有一个1，则j就在k那个1的位置，否则，j应该在k的最高位1左边一位。题解的做法是
    j从32 - __builtin_clz(k - 1)开始枚举，k减1，若k为2的幂次，j在k最高位1，否则32 - __builtin_clz(k - 1)也是在k的最高位1的位置，j够小不会漏
    m = 2^j - k <= j + 1，当j = 0时等式成立，当j > 0时，一旦有2^j - k > j + 1，对后面的j也会有2^j - k > j + 1，于是可以break
    */
    int waysToReachStair_implementation2(int k) {
        int ans = 0;
        int j = 0;
        // 题目k >= 0
        if (k == 0) j = 0;
        else if (k > 0) { // __builtin_clz()，参数为0时返回结果是ub
            if ((k & (k - 1)) == 0) j = 31 - __builtin_clz(k); // `LeetCode231. 2 的幂`判断k是否是2的幂
            else j = 32 - __builtin_clz(k);
        }
        for (; (1 << j) - k <= j + 1; j++) {
            // C(j + 1, m)
            ans += c[j + 1][(1 << j) - k]; // m此时<= j + 1，隔板法求方案数
            /* 这里要算组合数，上面用立即调用的lambda表达式实现了全局初始化的效果
            2^j - k <= j + 1，即2^j - j - 1 <= k，题目k <= 10^9，而2^29 < 10^9 < 2^30，所以j最多到29，
            上面的全局数组只需要31×31足够
            */
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3154 solu;
    cout << solu.waysToReachStair_implementation2(3) << endl;
    return 0;
}
