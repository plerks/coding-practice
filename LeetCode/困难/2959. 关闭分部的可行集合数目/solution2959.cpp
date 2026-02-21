/*
url: https://leetcode.cn/problems/number-of-possible-sets-of-closing-branches/
标签: Floyd
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2959 {
public:
    // 二进制枚举 + Floyd，时间复杂度 O(e + n^3 * 2^n)
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        const int inf = INT_MAX / 2;
        vector<vector<int>> d(n, vector<int>(n, inf));

        auto check = [&](int s) -> bool {
            // s 对应位为 0 代表无此节点，1 代表有
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    d[i][j] = inf;
                }
            }
            for (int i = 0; i < n; i++) d[i][i] = 0;
            for (auto& e : roads) {
                int u = e[0], v = e[1], w = e[2];
                if (((s >> u) & 1) && ((s >> v) & 1)) d[u][v] = min(d[u][v], w), d[v][u] = min(d[v][u], w); // 有重边
            }

            // Floyd
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (d[i][k] != inf && d[k][j] != inf) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int ok1 = ((s >> i) & 1);
                    int ok2 = ((s >> j) & 1);
                    if (ok1 && ok2 && d[i][j] > maxDistance) return false;
                }
            }
            return true;
        };

        int ans = 0;
        for (int s = 0; s < (1 << n); s++) {
            if (check(s)) ans++;
        }
        return ans;
    }

    /*
    参考灵茶题解，状压 dp
    Floyd 原来的定义 f[k][i][j] 表示从 i 到 j 的最短路长度，并且这条最短路的中间节点编号都 ≤ k
    这题有些节点不能用，所以用个 S 记录可用的中间节点状态，变成 f[S][i][j] ，然后递推
    对于计算 f[S][i][j]，考虑 S 中一个可用的 1 (k) 在中间 (任选一个就行，不管选哪个都能变成子问题)，
    则 f[S][i][j] = min(f[T][i][j], f[T][i][k] + f[T][k][j])
    */
    int numberOfSets_impl2(int n, int maxDistance, vector<vector<int>>& roads) {
        const int inf = INT_MAX / 2;
        vector<vector<vector<int>>> f(1 << n, vector<vector<int>>(n, vector<int>(n, inf)));
        for (auto& e : roads) {
            int u = e[0], v = e[1], w = e[2];
            f[0][u][v] = min(f[0][u][v], w); // 有重边
            f[0][v][u] = min(f[0][v][u], w);
        }
        int ans = 1; // 递推的基础状态，s = 0 的时候
        for (int s = 1; s < (1 << n); s++) {
            int k = __builtin_ctz(s); // 选最后那个 1 为 k
            int t = s ^ (1 << k);
            bool ok = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    f[s][i][j] = min(f[s][i][j], f[t][i][j]);
                    if (f[t][i][k] != inf && f[t][k][j] != inf) {
                        f[s][i][j] = min(f[s][i][j], f[t][i][k] + f[t][k][j]);
                    }
                    // 剩余节点的距离过大
                    // 这里没去写 f[s][i][i] = 0，i < j 的判断能避免 f[s][i][i] = inf 把 ok 搞成 false
                    if (ok && j < i && (s >> i & 1) && (s >> j & 1) && f[s][i][j] > maxDistance) ok = false;
                }
            }
            ans += ok;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2959 solu;
    // cout << solu.numberOfSets(3, 5, *new vector<vector<int>>{{0,1,2},{1,2,10},{0,2,10}}) << endl;
    cout << solu.numberOfSets_impl2(3, 5, *new vector<vector<int>>{{0,1,2},{1,2,10},{0,2,10}}) << endl;
    return 0;
}