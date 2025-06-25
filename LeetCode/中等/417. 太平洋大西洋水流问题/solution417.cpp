/*
url: https://leetcode.cn/problems/pacific-atlantic-water-flow/
参考: https://leetcode.cn/problems/pacific-atlantic-water-flow/solutions/1447341/tai-ping-yang-da-xi-yang-shui-liu-wen-ti-sjk3/
标签: 【算法题单】网格图, [special]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution417 {
public:
    /* 我的解法，74 / 113 个通过的测试用例，超内存了。想法是，这题的连通性是单向的，5能流到4 而 4不能流到5，不能求连通分量，
    因为一个连通分量里的元素不一定都能流到外面，例如4只能通过5流到外面，5连通4，会导致忽略了4不能到5这件事。
    所以需要对每个点都dfs一遍，但是这会超时，于是再加上记忆化搜索。
    */
    vector<vector<int>> pacificAtlantic_mle(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        map<pair<int, int>, pair<bool, bool>> memo;
        vector<vector<int>> vis(m, vector<int>(n, false));
        /* is_source是为了处理这样一种情况，某轮以(i, j)为起点，到了(ii, jj)，由于dfs(ii, jj)不能回去访问已经访问过的点，
        可能会认为(ii, jj)到不了两种边界，然后直接写memo[ii][jj]为不可到达了。没is_source的话[[1,1],[1,1],[1,1]]这个用例会wa。
        */
        auto dfs = [&](auto& dfs, int i, int j, bool is_source = false) { // 能否流出左上和右下
            pair<bool, bool> res = {false, false};
            if (!legal(i, j)) {
                if (i < 0 || j < 0) res.first = true;
                if (i >= m || j >= n) res.second = true;
                return res;
            }
            if (memo.count({i, j})) return memo[{i, j}];
            vis[i][j] = true;
            for (auto [dx, dy] : directions) {
                int ii = i + dx, jj = j + dy;
                if (!legal(ii, jj) || !vis[ii][jj] && heights[i][j] >= heights[ii][jj]) {
                    auto [ok1, ok2] = dfs(dfs, ii, jj);
                    res.first |= ok1;
                    res.second |= ok2;
                }
            }
            if (is_source) memo[{i, j}] = res;
            return res;
        };

        vector<vector<int>> ans;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vis = vector<vector<int>>(m, vector<int>(n, false));
                if (dfs(dfs, i, j, true) == pair{true, true}) {
                    ans.push_back({i, j});
                }
            }
        }

        return ans;
    }

    /* 参考官方题解，这题 起点多(O(mn))而终点少(O(m + n))，所以反向，改成从终点开始遍历，让水往高处流。
    这时求连通分量就是对的了，因为4能流到外面，那么与4相邻的更高的5就可以被连通。
    */
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // 要用dfs的话从4条边界的点都dfs一遍，不过这里可以用多源bfs
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<int>> ans;
        
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        
        auto bfs = [&](auto& q, auto& vis) {
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && !vis[xx][yy] && (!legal(x, y) || heights[xx][yy] >= heights[x][y])) {
                        vis[xx][yy] = true;
                        q.push({xx, yy});
                    }
                }
            }
        };

        queue<pair<int, int>> q;
        vector<vector<int>> vis1(m, vector<int>(n, false));
        // 太平洋作为起点
        for (int i = 0; i < m; i++) {
            q.push({i, -1});
        }
        for (int j = 0; j < n; j++) {
            q.push({-1, j});
        }
        bfs(q, vis1);

        q = queue<pair<int, int>>();
        vector<vector<int>> vis2(m, vector<int>(n, false));
        // 大西洋作为起点
        for (int i = 0; i < m; i++) {
            q.push({i, n});
        }
        for (int j = 0; j < n; j++) {
            q.push({m, j});
        }
        bfs(q, vis2);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (vis1[i][j] && vis2[i][j]) ans.push_back({i, j});
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution417 solu;
    auto a = solu.pacificAtlantic(*new vector<vector<int>>{{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}});
    auto b = solu.pacificAtlantic(*new vector<vector<int>>{{1,1},{1,1},{1,1}});
    return 0;
}