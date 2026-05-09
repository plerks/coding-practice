// https://leetcode.cn/problems/multi-source-flood-fill/

#include <bits/stdc++.h>

using namespace std;

class Solution3905 {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        vector<vector<int>> grid(n, vector<int>(m, 0));
        queue<pair<int, int>> q;
        set<pair<int, int>> vis;
        for (auto& v : sources) {
            int r = v[0], c = v[1], color = v[2];
            grid[r][c] = color;
            q.push({r, c});
            vis.insert({r, c});
        }
        const int N = 1e5 + 1;
        auto h = [&](int r, int c) {
            return r * N + c;
        };
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int r, int c) {
            return 0 <= r && r < n && 0 <= c && c < m;
        };
        
        while (!q.empty()) {
            map<pair<int, int>, int> mp;
            for (int _ = q.size() - 1; _ >= 0; _--) {
                auto [r, c] = q.front(); q.pop();
                for (auto [dr, dc] : directions) {
                    int rr = r + dr, cc = c + dc;
                    if (!legal(rr, cc) || vis.count({rr, cc})) continue;
                    mp[{rr, cc}] = max(mp[{rr, cc}], grid[r][c]);
                }
            }
            for (auto &[p, color] : mp) {
                q.push({p.first, p.second});
                vis.insert({p.first, p.second});
                grid[p.first][p.second] = color;
            }
        }
        return grid;
    }

    // 灵茶题解解法，如何方便处理：同时到达非染色单元格时，采用具有最大值的颜色？
    // 入队时按color排序，这样先到的就是color最大的，就不用特别处理了
    vector<vector<int>> colorGrid_impl2(int n, int m, vector<vector<int>>& sources) {
        vector<vector<int>> ans(n, vector<int>(m));
        sort(sources.begin(), sources.end(), [&](auto &x, auto& y) {
            return x[2] > y[2];
        });

        queue<pair<int, int>> q;
        for (auto& vec : sources) {
            int x = vec[0], y = vec[1], color = vec[2];
            ans[x][y] = color;
            q.push({x, y});
        }
        // ans == 0 可以用来判断 vis
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int r, int c) {
            return 0 <= r && r < n && 0 <= c && c < m;
        };
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto [dx, dy] : directions) {
                int xx = x + dx, yy = y + dy;
                if (legal(xx, yy) && ans[xx][yy] == 0) {
                    ans[xx][yy] = ans[x][y];
                    q.push({xx, yy});
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}