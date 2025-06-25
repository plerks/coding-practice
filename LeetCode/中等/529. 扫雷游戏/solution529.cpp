/*
url: https://leetcode.cn/problems/minesweeper/
标签: 【算法题单】网格图
*/
#include <bits/stdc++.h>

using namespace std;

class Solution529 {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int m = board.size(), n = board[0].size();
        const int cx = click[0], cy = click[1];
        const vector<pair<int, int>> directions = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        // 题目保证click位置是未被揭露的点
        if (board[cx][cy] == 'M') { // 挖到雷
            board[cx][cy] = 'X';
            return board;
        }

        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<vector<int>> vis(m, vector<int>(n, false));

        auto reveal = [&](auto& reveal, int x, int y) -> void {
            vis[x][y] = true;
            int cnt = 0;
            for (auto [dx, dy] : directions) {
                int xx = x + dx;
                int yy = y + dy;
                if (legal(xx, yy) && board[xx][yy] == 'M') {
                    cnt++;
                }
            }

            // 挖到空块，周围有雷
            if (cnt > 0) {
                board[x][y] = '0' + cnt;
                return;
            }

            // 挖到空块，周围无雷
            board[x][y] = 'B';
            for (auto [dx, dy] : directions) {
                int xx = x + dx;
                int yy = y + dy;
                if (legal(xx, yy) && !vis[xx][yy]) reveal(reveal, xx, yy);
            }
        };

        reveal(reveal, cx, cy);

        return board;
    }
};

int main(int argc, char const *argv[]) {
    Solution529 solu;
    auto a = solu.updateBoard(*new vector<vector<char>>{{'E','E','E','E','E'},{'E','E','M','E','E'},{'E','E','E','E','E'},{'E','E','E','E','E'}},
                             *new vector<int>{3,0});
    return 0;
}