/*
url: https://leetcode.cn/problems/count-sub-islands/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1905 {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size(), n = grid1[0].size();

        auto dfs = [&](auto& dfs, int i, int j) -> bool { // 返回值代表是否有遇到 grid2位置为1 而 grid1对应位置为0 的情况
            if (i < 0 || i >= m || j < 0 || j >= n || grid2[i][j] == 0) return true;
            if (grid1[i][j] == 0 && grid2[i][j] == 1) return false;
            grid2[i][j] = 0; // 改成0，可以替代vis的作用
            bool res = true;
            res &= dfs(dfs, i - 1, j);
            res &= dfs(dfs, i + 1, j);
            res &= dfs(dfs, i, j - 1);
            res &= dfs(dfs, i, j + 1);
            return res;
        };

        int ans = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid2[i][j] == 1) {
                    ans += dfs(dfs, i, j);
                }
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1905 solu;
    cout << solu.countSubIslands(*new vector<vector<int>>{{1,1,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,1,1}}
        , *new vector<vector<int>>{{1,1,1,0,0},{0,0,1,1,1},{0,1,0,0,0},{1,0,1,1,0},{0,1,0,1,0}});
    return 0;
}