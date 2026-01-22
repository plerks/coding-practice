/*
url: https://leetcode.cn/problems/number-of-alternating-xor-partitions/
参考: https://leetcode.cn/problems/number-of-alternating-xor-partitions/solutions/3883194/he-fa-zi-xu-lie-dppythonjavacgo-by-endle-ivxh/
      https://leetcode.cn/problems/number-of-alternating-xor-partitions/solutions/3883090/di-tui-by-tsreaper-moug/
相关: LeetCode560. 和为 K 的子数组
标签: LeetCode第174场双周赛, 状态机dp
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3811 {
public:
    // 周赛时的写法，由于每个状态需要一个循环，所以时间复杂度是 O(n^2) ，会超时，然后不知道怎么优化
    int alternatingXOR_tle(vector<int>& nums, int target1, int target2) {
        int n = nums.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i - 1 + 1] ^ nums[i];
        }
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[pre[i + 1]].push_back(i);
        }
        const long long MOD = 1e9 + 7;

        unordered_map<long long, long long> memo;

        auto dfs = [&](auto& dfs, int i, int j) -> long long { // dfs(i, j) 表示对 nums[i, n - 1]，当前开头段要为targetj
            long long state = ((long long)i << 1) | (long long)(j - 1);
            if (memo.count(state)) return memo[state];
            if (i >= n) return 1;
            int target = (j == 1) ? target1 : target2;
            long long ans = 0;
            
            // 找 [i, m] 的结果为 target，等价于找 [0, m] 的结果为 [0, i - 1] ^ target
            int t = pre[i - 1 + 1] ^ target;
            if (mp.count(t)) {
                for (int pos : mp[t]) {
                    if (pos < i) continue;
                    long long ret = dfs(dfs, pos + 1, ((j - 1) ^ 1) + 1);
                    if (ret > 0) {
                        ans = (ans + ret) % MOD;
                    }
                }
            }
            memo[state] = ans;
            return ans;
        };

        return dfs(dfs, 0, 1);
    }

    // 参考灵茶题解，要用LeetCode560的思想，在遍历过程中记录前面得到的值并记录在哈希表中
    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        /* 当遍历到 i 位置时，能不能形成以 i 为结尾，且尾段值为 target1 / target2 的交替？
        以尾段的异或值要为 target1 为例，则需要前面有个前缀段异或值为 target2，且其也是满足题意的交替，
        如何知道尾段能不能为 target1 ? 当前总异或值为 s，则前缀的异或和要为 s ^ target1。
        因此要两个哈希表，
        mp1[t] 表示 nums[0, i - 1] 的前缀中，异或和为 t，且尾段结果为 target1，且符合交替的方案数；
        mp2[t] 表示异或和为 t，且尾段结果为 target2，且符合交替的方案数；
        */
        int n = nums.size();
        const int MOD = 1e9 + 7;
        unordered_map<int, int> f1, f2;
        f2[0] = 1; // 初始时刻，选前缀为空是一种方案，比如 nums = [target1] ，尾段为 target1，前缀为 0 是有 1 种方案的
        int s = 0;
        for (int i = 0; i < n; i++) {
            s ^= nums[i];
            int cnt1 = f1.count(s ^ target2) ? f1[s ^ target2] : 0; // 以 target1 结尾，值为 s^target2 的前缀方案数，由于哈希表里还是上一轮的结果，可以保证最后一段非空
            int cnt2 = f2.count(s ^ target1) ? f2[s ^ target1] : 0;
            if (i == n - 1) return (cnt1 + cnt2) % MOD; // 要在最后一次循环时统计结果，这时候还能根据前缀的值设定最后一段的值，循环结束后只有整段的值了
            f1[s] = (f1[s] + cnt2) % MOD;
            f2[s] = (f2[s] + cnt1) % MOD;
        }
        return -1; // 不会执行
    }

    /* TsReaper 的解法，状态机dp。t1, t2, t1, t2 这样循环，前缀异或和会呈现 t1, t1 ^ t2, t2, 0 这样周期性变化，
    从而进行状态机 dp 。
    但是这个方法需要本题的运算是异或，如果改成加，则会失去周期性，而上一种用哈希表的方法仍然可行。采用这种解法可以用滚动数组把空间优化到 O(1)
    */
    int alternatingXOR_implementation2(vector<int>& nums, int target1, int target2) {
        int n = nums.size();
        const int MOD = 1e9 + 7;
        int goal[4] = {target1, target1 ^ target2, target2, 0};
        vector<vector<int>> f(n + 1, vector<int>(4)); // f[i][j] 表示以 nums[0, i) 为范围，且末段状态为 j 的方案数
        f[0][3] = 1;
        int s = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            s ^= nums[i];
            for (int j = 0; j < 4; j++) {
                if (s == goal[j]) f[i + 1][j] = f[i][(j - 1 + 4) % 4]; // 计算 f[i]
            }
            // 现在 f[i] 存的是当前位置的值，而 f[i - 1] 存的是前缀和
            // 现在要把 f[i] 变成前缀和，为了获取 ans ，在变前缀和前累加到 ans 里
            for (int j = 0; j < 4; j++) {
                if (i == n - 1) ans = (ans + f[i + 1][j]) % MOD;
                f[i + 1][j] = (f[i + 1][j] + f[i][j]) % MOD; // 复用 f[i] 为前缀和
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3811 solu;
    // cout << solu.alternatingXOR(*new vector<int>{2,3,1,4}, 1, 5) << endl;
    // cout << solu.alternatingXOR(*new vector<int>{1,0,0}, 1, 0) << endl;
    cout << solu.alternatingXOR(*new vector<int>{7}, 1, 7) << endl;
    return 0;
}