/*
url: https://leetcode.cn/problems/minimum-cost-to-partition-a-binary-string/
标签: LeetCode第492场周赛
*/
// 这次周赛 4 题，不过题比较简单

#include <bits/stdc++.h>

using namespace std;

class Solution3864 {
public:
    // 直接模拟即可，注意这题不需要记忆化，不涉及重复计算，过程相当于把 n 长度的区间类似线段树分治，最后得到二叉树，有 O(n) 个节点
    long long minCost(string s, int encCost, int flatCost) {
        // f[i] = min(不拆分，f左 + f右)，左右的代价只和 L , X 有关
        using i64 = long long;
        int n = s.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + (s[i] == '1');

        auto dfs = [&](auto& dfs, int l, int r) -> i64 {
            if (r - l + 1 == 1) {
                // printf("l: %d, r: %d, ret: %d\n", l, r, s[r] == '0' ? flatCost : encCost);
                return s[r] == '0' ? flatCost : encCost;
            }
            i64 res = INT64_MAX;
            i64 cnt1 = pre[r + 1] - pre[l - 1 + 1];
            // 不拆分
            if (cnt1 == 0) res = min(res, (i64)flatCost);
            else res = min(res, (r - l + 1) * cnt1 * encCost);

            // 拆分
            if ((r - l + 1) % 2 == 0) {
                int mi = (l + r) / 2;
                res = min(res, dfs(dfs, l, mi) + dfs(dfs, mi + 1, r));
            }
            // printf("l: %d, r: %d, res: %lld\n", l, r, res);
            return res;
        };

        return dfs(dfs, 0, n - 1);
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}