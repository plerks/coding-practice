/*
url: https://leetcode.cn/problems/shortest-path-to-get-all-keys/
标签: 【算法题单】网格图, 状态压缩, 状压bfs
*/
#include <bits/stdc++.h>

using namespace std;

class Solution864 {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int sx, sy;
        int key_cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    sx = i;
                    sy = j;
                }
                else if ('a' <= grid[i][j] && grid[i][j] <= 'z') {
                    key_cnt++;
                }
            }
        }

        auto hash = [&](int x, int y, int s) {
            // 1 <= m, n <= 30
            return s * 31 * 31 + y * 31 + x;
        };

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        auto legal = [&](int i, int j, int s) {
            return 0 <= i && i < m && 0 <= j && j < n && 
                    (grid[i][j] == '@' || grid[i][j] == '.' || ('a' <= grid[i][j] && grid[i][j] <= 'z') || 
                        ('A' <= grid[i][j] && grid[i][j] <= 'Z' && ((s >> (grid[i][j] - 'A')) & 1)));
        };

        unordered_set<int> vis; // 到达某个坐标位置时自身带有状态(身上有哪些钥匙)
        queue<tuple<int, int, int>> q; // (x, y, s) s为钥匙状态，压缩到一个int里，此题钥匙'a'-'f'，钥匙的数目范围是 [1, 6]
        q.push({sx, sy, 0});
        vis.insert(hash(sx, sy, 0));
        for (int level = 0; !q.empty(); level++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, s] = q.front(); q.pop();
                /* bitset<32> b(s);
                cout << x << ' ' << y << ' ' << b << endl; */
                if (__builtin_popcount(s) == key_cnt) return level;
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy, s) && !vis.count(hash(xx, yy, s))) {
                        if ('a' <= grid[xx][yy] && grid[xx][yy] <= 'z') {
                            int ss = s | (1 << (grid[xx][yy] - 'a'));
                            if (!vis.count(hash(xx, yy, ss))) {
                                q.push({xx, yy, ss});
                                vis.insert(hash(xx, yy, ss));
                            }
                        }
                        else if (!vis.count(hash(xx, yy, s))) {
                            q.push({xx, yy, s});
                            vis.insert(hash(xx, yy, s));
                        }
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution864 solu;
    // cout << solu.shortestPathAllKeys(*new vector<string>{"@.a..","###.#","b.A.B"}) << endl;
    cout << solu.shortestPathAllKeys(*new vector<string>{"@abcdeABCDEFf"}) << endl;
    return 0;
}