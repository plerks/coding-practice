/*
url: https://leetcode.cn/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/
参考: https://leetcode.cn/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/solutions/2093243/zhuan-huan-cheng-qiu-lun-kuo-shi-fou-xia-io8x/
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2556 {
public:
    // 参考灵茶题解，还以为是要找关节点什么的，实际只需遍历两次，第一次遍历把路径点都变成障碍，第二次不能连通了就说明可以翻转使矩阵不连通了
    bool isPossibleToCutPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        auto dfs = [&](auto& dfs, int i, int j) -> bool {
            if (i == m - 1 && j == n - 1) return true;
            grid[i][j] = 0; // 改成障碍
            bool ok = false; // 能否到达
            if (i + 1 < m && grid[i + 1][j] == 1) {
                ok = dfs(dfs, i + 1, j);
            }
            if (ok) return true;
            if (j + 1 < n && grid[i][j + 1] == 1) {
                ok = dfs(dfs, i, j + 1);
            }
            return ok;
        };

        return !dfs(dfs, 0, 0) || !dfs(dfs, 0, 0); // 两次都能到达说明连通
    }

    // 灵茶题解原本的写法，理解起来绕了一点，不过很简洁
    bool isPossibleToCutPath_implementation2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        auto dfs = [&](auto& dfs, int i, int j) -> bool {
            if (i == m - 1 && j == n - 1) return true;
            grid[i][j] = 0; // 改成障碍
            return i + 1 < m && grid[i + 1][j] && dfs(dfs, i + 1, j) ||
                   j + 1 < n && grid[i][j + 1] && dfs(dfs, i, j + 1);
        };

        return !dfs(dfs, 0, 0) || !dfs(dfs, 0, 0);
    }
};

int main(int argc, char const *argv[]) {
    Solution2556 solu;
    cout << solu.isPossibleToCutPath(*new vector<vector<int>>{{1,1,1},{1,0,0},{1,1,1}}) << endl;

    cout << solu.isPossibleToCutPath_implementation2(*new vector<vector<int>>{{1,1,1},{1,0,0},{1,1,1}}) << endl;
    return 0;
}