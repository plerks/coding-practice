/*
url: https://leetcode.cn/problems/detonate-the-maximum-bombs/
标签: 【算法题单】图论算法, Floyd算法 + bitset优化
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2101 {
public:
    // 时间复杂度O(n^3)，图中有O(n^2)条边，每次dfs时间复杂度为O(n^2)
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<int> vis(n);
        int ans = 0;

        auto dfs = [&](auto& dfs, int root) -> int {
            long long x = bombs[root][0], y = bombs[root][1], r = bombs[root][2];
            vis[root] = true;
            int cnt = 1;
            for (int i = 0; i < n; i++) {
                long long xx = bombs[i][0], yy = bombs[i][1];
                if (root != i && !vis[i]) {
                    long long dis = (x - xx) * (x - xx) + (y - yy) * (y - yy);
                    if (dis <= r * r) cnt += dfs(dfs, i);
                }
            }
            return cnt;
        };

        for (int i = 0; i < n; i++) {
            auto& bomb = bombs[i];
            fill(vis.begin(), vis.end(), 0);
            ans = max(ans, dfs(dfs, i));
        }

        return ans;
    }

    /* 参考灵茶题解，用floyd算法计算可达性，并用bitset优化。
    如果i能到k，那么k能到的，i也能到。用f[i]表示i能到达的点的集合，f[i] = f[i] ∪ f[k]，这可以用bitset优化
    */
    int maximumDetonation_implementation2(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<bitset<100>> f(n); // 1 <= bombs.length <= 100
        // 构造边，放bitset里
        for (int i = 0; i < n; i++) {
            long long x = bombs[i][0], y = bombs[i][1], r = bombs[i][2];
            for (int j = 0; j < n; j++) {
                long long xx = bombs[j][0], yy = bombs[j][1];
                long long dis = (x - xx) * (x - xx) + (y - yy) * (y - yy);
                if (dis <= r * r) f[i].set(j);
            }
        }

        // floyd算法
        // 这里为什么只有两层循环？其实是3层，有一层是用bitset直接枚举了j，bitset有n位，二者or也要O(n)
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (f[i].test(k)) { // i能到k
                    f[i] |= f[k]; // k能到的，i也能到
                }
            }
        }

        // 返回1最多的bitset
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, (int)f[i].count());
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2101 solu;
    cout << solu.maximumDetonation(*new vector<vector<int>>{{2,1,3},{6,1,4}}) << endl;
    return 0;
}