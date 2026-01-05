/*
url: https://leetcode.cn/problems/k-similar-strings/
参考: https://leetcode.cn/problems/k-similar-strings/solutions/1836897/xiang-si-du-wei-k-de-zi-fu-chuan-by-leet-8z10/
标签: 【题单】图论算法, 循环节
*/

#include <bits/stdc++.h>

using namespace std;

class Solution854 {
public:
    /* 官方题解解法，常规的想法，即bfs里写个枚举双重交换不行，会超时，因为这样状态数有 n! 种，总时间复杂度 O(n^2 * n!)。
    所以必须剪枝，枚举方式换成：前面已经相同的部分不用管，从第一个不等的位置开始。
    这样时间复杂度还是无法分析，不过能过题，官方题解："该方法时空复杂度分析较为复杂，暂不讨论。"
    */
    int kSimilarity(string s1, string s2) {
        int n = s1.size();
        queue<pair<string, int>> q; // string 为当前状态，int 左侧都是和 s2 相等的部分，计算过程带着 int 避免重新算
        unordered_set<string> vis;
        if (s1 == s2) return 0;
        q.push({s1, 0});
        vis.insert(s1);
        int level = 1;
        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                auto [cur, pos] = q.front(); q.pop();
                for (; cur[pos] == s2[pos]; pos++);

                for (int j = pos + 1; j < n; j++) {
                    if (cur[j] != s2[pos]) continue;
                    string next = cur;
                    swap(next[pos], next[j]);
                    if (vis.count(next)) continue;
                    if (next == s2) return level;
                    q.push({next, pos + 1});
                    vis.insert(next);
                }
            }
            level++;
        }
        return -1;
    }

    // 官方题解解法二，三是用 dfs 和 A* 的，和解法一本质大差不差

    /* 官方题解解法四，用循环节的思路。
    先看一个例子，对于 s1 = "abcdef" , s2 = "ecdbfa"，s1 可以拆成 "_cdb__" 和 "e___fa"，
    也就是说 s1 有两个循环节，这里有相同字母，循环节的定义是：选出同样的位置序列，成分相同，且极小
    对于每个循环节，需要的交换次数为 len(循环节) - 1，是最大化的，也是 base case。

    对于 s1[i] = s2[i] 的位置，不用交换，全部不看。
    因此，问题在于求排除相等位置后（现在每个位置都不相等，最大交换次数为 len - 1，最小为 len / 2），s1 对应着 s2 的循环节数，ans 为 n - 循环节数

    如何求 str1 对应着 str2 的循环节数？
    分治，用 f 表示循环节数，则 f(s) = f(p) + f(q)，其中 p, q 各自为循环节，且二者为 s 的一个划分

    这意味着我们要预先处理出 s1 中的所有可能成为循环节的情况，1 <= s1.length <= 20，所以子集划分可以用位优化。
    此外还有一点，我们难以判断子序列是否极小，只能判断 选出同样的位置序列，成分相同（以下我称之为广义循环节） ，
    所以，要按长度排序一下，前面的才是极小的。

    我们要判断 s1 的循环节数，要枚举 p 的所有选择情况，然后求 f(p) + f(q)，用递归的话是记忆化搜索，用 dp 的话计算顺序该如何？
    题目字符串只会有 abcdef 6种字母，所以长度超过 6 的子序列，就算是广义循环节，也一定不是循环节（一定会有位置相同，可以再拆）。
    此外，长度 <= 6 的子序列也可能是可以再分的。
    所以，要先计算 smallGeneralizedCycles 的 f 值，再计算 largeGeneralizedCycles 的 f 值。官方题解是这么做的，
    看起来不需要根据长度是否 <= 6 划分为 small 和 large，统一计算就行，但是以下代码会超时，63 / 66 个通过的测试用例

    问题在于枚举 x 和 y 的那个双重循环，|gCycles| 最坏可能为 2^n，于是 x 和 y 的双重循环耗时 2^{2n}
    */
    int kSimilarity_tle(string s1, string s2) {
        string str1, str2;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) str1.push_back(s1[i]), str2.push_back(s2[i]);
        }
        int n = str1.size();
        if (n == 0) return 0;
        vector<int> gCycles; // s1能成为广义循环节的所有子序列
        // 算所有子序列，是否能成为广义循环节
        for (int i = 0; i < (1 << n); i++) {
            int diff[6]{}; // 记录成分差值
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) { // 子序列中有 j 这位
                    diff[str1[j] - 'a']++;
                    diff[str2[j] - 'a']--;
                }
            }
            bool is = true; // 成分是否相同，是不是广义循环节
            for (int i = 0; i < 6; i++) {
                if (diff[i] != 0) {
                    is = false;
                    break;
                }
            }
            if (is) {
                gCycles.push_back(i);
            }
        }

        // 把选的字母少的放前面，这样 dp 过程中 base case 才能保证先算了
        auto cmp = [](int state1, int state2) {
            return __builtin_popcount(state1) < __builtin_popcount(state2);
        };
        sort(gCycles.begin(), gCycles.end(), cmp);
        vector<int> f(1 << n, 1); // 先默认每个子序列情况自成一个循环节
        f[0] = 0;
        // 拆分所有广义循环节，算循环节数
        for (int x : gCycles) {
            for (int y : gCycles) {
                if ((x & y) == y) { // y 是 x 的子集
                    f[x] = max(f[x], f[y] + f[x ^ y]);
                }
            }
        }

        return n - f[(1 << n) - 1]; // (1 << n) - 1 的选择情况即为 s1
    }

    /* 还是得划分 small 和 large，这样一来，先把 f(smallGCycles) 算了，对于 smallGCycles 的计算只需枚举 smallGCycles，不需枚举 largeGCycles，
    然后再算 f(largeGCycles) ，也只需用到 smallGCycles。
    这样，计算 f 表的时间就只有 |small| * |small| + |large| * |small| ，而 small 最长 6 位，这样就把枚举的时间降低下来了。

    本题字符串长度 <= 20，字符种类个数 <= 6，时间复杂度 O(20 * 2^20 + 2^6 * 2^20)

    这个循环节的解法虽然很有意思，不过实际运行时间不如 bfs 的解法。
    */
    int kSimilarity_implementation2(string s1, string s2) {
        string str1, str2;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) str1.push_back(s1[i]), str2.push_back(s2[i]);
        }
        int n = str1.size();
        if (n == 0) return 0;
        vector<int> smallGCycles; // 长度 <= 6 的
        vector<int> largeGCycles; // 长度 > 6 的
        // 算所有子序列，是否能成为广义循环节
        for (int i = 0; i < (1 << n); i++) {
            int diff[6]{}; // 记录成分差值
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) { // 子序列中有 j 这位
                    diff[str1[j] - 'a']++;
                    diff[str2[j] - 'a']--;
                }
            }
            bool is = true; // 成分是否相同，是不是广义循环节
            for (int i = 0; i < 6; i++) {
                if (diff[i] != 0) {
                    is = false;
                    break;
                }
            }
            if (is) {
                int popcount = __builtin_popcount(i);
                if (popcount <= 6) smallGCycles.push_back(i);
                else largeGCycles.push_back(i);
            }
        }

        // 把选的字母少的放前面，这样 dp 过程中 base case 才能保证先算了
        auto cmp = [](int state1, int state2) {
            return __builtin_popcount(state1) < __builtin_popcount(state2);
        };
        sort(smallGCycles.begin(), smallGCycles.end(), cmp);
        sort(largeGCycles.begin(), largeGCycles.end(), cmp);
        vector<int> f(1 << n, 1); // 先默认每个子序列情况自成一个循环节
        f[0] = 0;
        // 拆分所有广义循环节，算循环节数
        for (int x : smallGCycles) {
            for (int y : smallGCycles) {
                if ((x & y) == y) { // y 是 x 的子集
                    f[x] = max(f[x], f[y] + f[x ^ y]);
                }
            }
        }
        for (int x : largeGCycles) {
            for (int y : smallGCycles) {
                if ((x & y) == y) { // y 是 x 的子集
                    f[x] = max(f[x], f[y] + f[x ^ y]);
                }
            }
        }

        return n - f[(1 << n) - 1]; // (1 << n) - 1 的选择情况即为 s1
    }
};

int main(int argc, char const *argv[]) {
    Solution854 solu;
    cout << solu.kSimilarity("abc", "bca") << endl;
    cout << solu.kSimilarity_implementation2("abc", "bca") << endl;
    return 0;
}