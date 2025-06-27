/*
url: https://leetcode.cn/problems/nearest-exit-from-entrance-in-maze/
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1926 {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };
        vector<vector<int>> vis(m, vector<int>(n));
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        vis[entrance[0]][entrance[1]] = true;
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (!legal(xx, yy) && pair{x, y} != pair{entrance[0], entrance[1]}) {
                        return level;
                    } 
                    if (legal(xx, yy) && maze[xx][yy] == '.' && !vis[xx][yy]) {
                        q.push({xx, yy});
                        vis[xx][yy] = true;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1926 solu;
    cout << solu.nearestExit(*new vector<vector<char>>{{'+','+','.','+'},{'.','.','.','+'},{'+','+','+','.'}}, *new vector<int>{1,2}) << endl;
    cout << solu.nearestExit(*new vector<vector<char>>{{'+','+','+'},{'.','.','.'},{'+','+','+'}}, *new vector<int>{1,0}) << endl;
    return 0;
}