/*
url: https://leetcode.cn/problems/maximum-amount-of-money-robot-can-earn/description/
标签: LeetCode第432场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3418 {
public:
    /* 周赛时的错误写法，调了很久到最后几分钟才调出来，以下这样写的关键问题在于，可以不走到(m - 1, n - 1)这个点，
    走到边界外的一个点就直接结束(比如走到(m, n/2))，但是实际是必须以(m - 1, n - 1)为终点的。
    处理方式是走到边界外时要返回负无穷，或者判断不会越界再递归。
    */
    int maximumAmount_wrong(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();

        vector<vector<vector<int>>> memo(m + 1, vector<vector<int>>(n + 1, vector<int>(3, -1)));

        auto dfs = [&](auto& dfs, int i, int j, int k) {
            if (i > m - 1 || j > n - 1) return 0;
            if (memo[i][j][k] != -1) return memo[i][j][k];
            int ans = INT_MIN;
            // 不用特殊能力
            ans = max(dfs(dfs, i, j + 1, k) + coins[i][j], dfs(dfs, i + 1, j, k) + coins[i][j]);
            // 用特殊能力
            if (k > 0 && coins[i][j] < 0) {
                ans = max({ans, dfs(dfs, i, j + 1, k - 1), dfs(dfs, i + 1, j, k - 1)});
            }
            memo[i][j][k] = ans;
            return ans;
        };

        return dfs(dfs, 0, 0, 2);
    }

    // 正确写法
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();

        vector<vector<vector<int>>> memo(m + 1, vector<vector<int>>(n + 1, vector<int>(3, INT_MIN)));

        // dfs表示从(i, j)走到(m-1, n-1)的最大收益
        auto dfs = [&](auto& dfs, int i, int j, int k) {
            if (i == m - 1 && j == n - 1) {
                if (k > 0) return max(0, coins[m - 1][n - 1]);
                else return coins[m - 1][n - 1];
            }
            if (memo[i][j][k] != INT_MIN) return memo[i][j][k];
            int ans = INT_MIN;
            // 不用特殊能力
            if (j + 1 < n) ans = max(ans, dfs(dfs, i, j + 1, k) + coins[i][j]);
            if (i + 1 < m) ans = max(ans, dfs(dfs, i + 1, j, k) + coins[i][j]);
            // 用特殊能力
            if (k > 0 && coins[i][j] < 0) {
                if (j + 1 < n) ans = max(ans, dfs(dfs, i, j + 1, k - 1));
                if (i + 1 < m) ans = max(ans, dfs(dfs, i + 1, j, k - 1));
            }
            memo[i][j][k] = ans;
            return ans;
        };
        int ans = dfs(dfs, 0, 0, 2);
        return ans;
    }

    /* dp的写法
    f[i][j][k] = max({f[i+1][j][k]+coins[i][j], f[i][j+1][k]+coins[i][j], f[i+1][j][k-1], f[i][j+1][k-1]})
    如果出界的话是负无穷，因为获得金币数可以是负数
    k-1会出现-1，公式改成
    f[i][j][k + 1] = max({f[i+1][j][k + 1]+coins[i][j], f[i][j+1][k + 1]+coins[i][j], f[i+1][j][k], f[i][j+1][k]})
    k的范围仍是原来的范围，答案为f[0][0][2 + 1]
    */
    int maximumAmount_implementation2(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        vector<vector<vector<int>>> f(m + 1, vector<vector<int>>(n + 1, vector<int>(4, -0x3f3f3f3f)));
        f[m - 1][n - 1][0 + 1] = coins[m - 1][n - 1];
        f[m - 1][n - 1][1 + 1] = max(0, coins[m - 1][n - 1]);
        f[m - 1][n - 1][2 + 1] = max(0, coins[m - 1][n - 1]);
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                for (int k = 0; k <= 2; k++) {
                    if (i == m - 1 && j == n - 1) continue;
                    f[i][j][k + 1] = max({f[i + 1][j][k + 1] + coins[i][j], f[i][j + 1][k + 1] + coins[i][j], f[i + 1][j][k],f[i][j + 1][k]});
                }
            }
        }
        return f[0][0][3];
    }
};

int main(int argc, char const *argv[]) {
    Solution3418 solu;
    cout << solu.maximumAmount(*new vector<vector<int>>{{-7,12,12,13},{-6,19,19,-6},{9,-2,-10,16},{-4,14,-10,-9}}) << endl;
    cout << solu.maximumAmount_implementation2(*new vector<vector<int>>{{-7,12,12,13},{-6,19,19,-6},{9,-2,-10,16},{-4,14,-10,-9}}) << endl;
    return 0;
}