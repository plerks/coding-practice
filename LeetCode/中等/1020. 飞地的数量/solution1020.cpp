/*
url: https://leetcode.cn/problems/number-of-enclaves/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1020 {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<vector<int>> vis(m, vector<int>(n, false));

        auto dfs = [&](auto& dfs, int i, int j) -> pair<bool, int> { // dfs返回是否走出了边界, 以及连通分量大小
            if (!legal(i, j)) return {true, 0};
            if (vis[i][j] || grid[i][j] == 0) return {false, 0};

            vis[i][j] = true;
            bool p1 = false;
            int p2 = 1;
            for (auto [dx, dy] : directions) {
                int ii = i + dx, jj = j + dy;
                auto [outbound, sz] = dfs(dfs, ii, jj);
                p1 |= outbound;
                p2 += sz;
            }
            return {p1, p2};
        };
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                auto [p1, p2] = dfs(dfs, i, j);
                if (!p1) ans += p2;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1020 solu;
    cout << solu.numEnclaves(*new vector<vector<int>>{{0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0}}) << endl;
    return 0;
}