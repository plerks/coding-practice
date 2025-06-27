/*
url: https://leetcode.cn/problems/k-highest-ranked-items-within-a-price-range/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

struct Info {
    int dis = -1;
    int row = -1;
    int col = -1;
};

class Solution2146 {
public:
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        int m = grid.size();
        int n = grid[0].size();
        
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<Info> infos;
        queue<Info> q;
        vector<vector<int>> vis(m, vector<int>(n));
        q.push({0, start[0], start[1]});
        vis[start[0]][start[1]] = true;
        if (grid[start[0]][start[1]] > 1 && pricing[0] <= grid[start[0]][start[1]] && grid[start[0]][start[1]] <= pricing[1]) { // 是商品
            infos.push_back({0, start[0], start[1]});
        }
        
        while (!q.empty() && infos.size() < k) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                auto [dis, x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx;
                    int yy = y + dy;
                    int disdis = dis + 1;
                    if (legal(xx, yy) && !vis[xx][yy] && grid[xx][yy] >= 1) {
                        q.push({disdis, xx, yy});
                        if (grid[xx][yy] > 1 && pricing[0] <= grid[xx][yy] && grid[xx][yy] <= pricing[1]) {
                            infos.push_back({disdis, xx, yy});
                        }
                        vis[xx][yy] = true;
                    }
                }
            }
        }

        sort(infos.begin(), infos.end(), [&](Info x, Info y) {
            if (x.dis != y.dis) return x.dis < y.dis;
            if (grid[x.row][x.col] != grid[y.row][y.col]) return grid[x.row][x.col] < grid[y.row][y.col];
            if (x.row != y.row) return x.row < y.row;
            return x.col < y.col;
        });

        vector<vector<int>> ans;
        for (int i = 0; i < min(k, (int)infos.size()); i++) {
            ans.push_back({infos[i].row, infos[i].col});
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2146 solu;
    auto a = solu.highestRankedKItems(*new vector<vector<int>>{{1,2,0,1},{1,3,0,1},{0,2,5,1}},
                                        *new vector<int>{2, 5}, *new vector<int>{0, 0}, 3);

    auto b = solu.highestRankedKItems(*new vector<vector<int>>{{1,0,1},{3,5,2},{1,0,1}},
                                        *new vector<int>{2, 5}, *new vector<int>{1, 1}, 9);
    return 0;
}