/*
参考: https://leetcode.cn/problems/cut-off-trees-for-golf-event/solutions/1510776/wei-gao-er-fu-bi-sai-kan-shu-by-leetcode-rlrc/
*/

#include <bits/stdc++.h>

using namespace std;

class Solution675 {
public:
    /* 官方题解解法，树的高度各不相同，从低到高砍，砍树的顺序是确定的，于是以每棵树为起点，求下一棵要砍的树的
    最短距离。

    时间复杂度 O(mn * mn)，690ms
    */
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size(), n = forest[0].size();
        vector<pair<int, int>> tree;
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            if (forest[i][j] > 1) { // 是树
                tree.push_back({i, j});
            }
        }
        sort(tree.begin(), tree.end(), [&](pair<int, int> node1, pair<int, int> node2) {
            return forest[node1.first][node1.second] < forest[node2.first][node2.second];
        });

        int ans = 0;
        int cx = 0, cy = 0; // 当前的位置
        for (int i = 0; i < tree.size(); i++) {
            int t = bfs(forest, cx, cy, tree[i].first, tree[i].second);
            if (t == -1) { // 无法到达
                return -1;
            }
            ans += t;
            cx = tree[i].first;
            cy = tree[i].second;
        }
        return ans;
    }

    // 返回 (sx, sy) 到 (tx, ty) 的最短距离
    int bfs(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        int m = forest.size(), n = forest[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        queue<pair<int, int>> q;
        vector<vector<int>> vis(m, vector<int>(n));
        if (sx == tx && sy == ty) return 0; // 起点终点相同要特判
        if (forest[sx][sy] != 0) { // 非墙
            q.push({sx, sy});
            vis[sx][sy] = true;
        }
        for (int level = 1; !q.empty(); level++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (0 <= xx && xx < m && 0 <= yy && yy < n && !vis[xx][yy] && forest[xx][yy] != 0) {
                        if (xx == tx && yy == ty) return level;
                        q.push({xx, yy});
                        vis[xx][yy] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution675 solu;
    // cout << solu.cutOffTree(*new vector<vector<int>>{{1,2,3},{0,0,4},{7,6,5}}) << endl;
    cout << solu.cutOffTree(*new vector<vector<int>>{{2,3,4},{0,0,5},{8,7,6}}) << endl;
    return 0;
}