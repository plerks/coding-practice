/*
url: https://leetcode.cn/problems/cracking-the-safe/
参考: https://leetcode.cn/problems/cracking-the-safe/solutions/393529/po-jie-bao-xian-xiang-by-leetcode-solution/
标签: Hierholzer 算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution753 {
public:
    /* 参考官方题解，
    考虑这个过程 00 -> 01 -> 11 -> 10 ，每次只变一位（有点格雷码的感觉），
    实际是下一个数字用上一个数字的后 n - 1 位，然后在末尾补上自己的一位，
    计算这 k^n 个数字的连接关系，然后除开第一个数，每次在 ans 末尾加上下一个数的末尾数字。
    这变成了求哈密顿路径的问题，但是找到一个哈密顿路径/回路是一个NPC问题，没有已知的多项式时间内的求解算法。

    这题的问题可以转换成求欧拉路径，每个点只看后 n - 1 位，然后边是末尾的一位数字，
    于是有 k^{n - 1} 个点，k^n 条有向边，变成了求欧拉路径问题。且由于每个点的度都是 k ，一定有欧拉回路，
    从任一个点开始都可以。
    */
    string crackSafe(int n, int k) {
        unordered_set<int> vis;
        string ans;
        auto dfs = [&](auto& dfs, int x) -> void {
            for (int d = 0; d < k; d++) {
                int t = x * 10 + d;
                if (!vis.count(t)) {
                    vis.insert(t);
                    dfs(dfs, t % (int)pow(10, n - 1));
                    ans += '0' + d; // 按后序访问节点，最后 reverse
                }
            }
        };
        dfs(dfs, 0);

        reverse(ans.begin(), ans.end());
        ans = string(n - 1, '0') + ans;

        // 这里是 reverse 得到了欧拉回路的结果，再在开头补上了开始的 n - 1 个 '0' ，实际这题的结果反转也是 ans，
        // 所以可以直接 ans += string(n - 1, '0')，不用 reverse
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution753 solu;
    cout << solu.crackSafe(1, 2) << endl;
    cout << solu.crackSafe(2, 2) << endl;
    return 0;
}