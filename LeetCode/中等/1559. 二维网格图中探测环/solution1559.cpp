/*
url: https://leetcode.cn/problems/detect-cycles-in-2d-grid/
标签: 【算法题单】网格图, bfs检测环, 无向图bfs检测环
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1559 {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, false));

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        auto bfs = [&](int i, int j) -> bool { // 返回是否发现了环
            if (vis[i][j]) return false;
            queue<pair<pair<int, int>, pair<int, int>>> q; // (当前点, 父节点(拉自己进队的点))
            q.push({{i, j}, {-1, -1}});
            vis[i][j] = true;
            while (!q.empty()) {
                auto [node, parent] = q.front(); q.pop();
                auto [x, y] = node;
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    // 无向图用bfs检测环，需要判断 neighbor != parent。不然(x, y)拉(xx, yy)入队，(xx, yy)遍历邻居时会认为和(x, y)之间有环
                    if (legal(xx, yy) && pair{xx, yy} != parent && grid[xx][yy] == grid[i][j]) {
                        if (vis[xx][yy]) {
                            return true;
                        }
                        else {
                            vis[xx][yy] = true;
                            q.push({{xx, yy}, {x, y}});
                        }
                    }
                }
            }
            return false;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (bfs(i, j)) return true;
            }
        }

        return false;
    }

    // 这题官方题解用的并查集，遍历每条边，发现相邻元素相等则通过并查集将二者合并，如果合并前二人已在同一集合，则说明有环
    // 遍历边的写法是：二层循环i, j遍历点，对每个点操作 右方 + 下方 的两条边（也可每次 左方 + 上方）
};

int main(int argc, char const *argv[]) {
    Solution1559 solu;
    // cout << solu.containsCycle(*new vector<vector<char>>{{'a','a','a','a'},{'a','b','b','a'},{'a','b','b','a'},{'a','a','a','a'}}) << endl;
    cout << solu.containsCycle(*new vector<vector<char>>{{'a','b','b'},{'b','z','b'},{'b','b','a'}}) << endl;
    return 0;
}