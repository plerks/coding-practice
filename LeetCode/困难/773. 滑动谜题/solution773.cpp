/*
url: https://leetcode.cn/problems/sliding-puzzle/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution773 {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int m = 2, n = 3; // board 是 2 * 3 的
        string origin;
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) origin.push_back(board[i][j] + '0');

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int x, int y) {
            return 0 <= x && x < m && 0 <= y && y < n;
        };

        auto bfs = [&]() {
            if (origin == "123450") return 0;
            queue<pair<string, int>> q;
            unordered_set<string> vis;
            int origin_idx; // 初始时 0 的位置
            for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) if (board[i][j] == 0) origin_idx = i * n + j;
            q.push({origin, origin_idx});
            vis.insert(origin);
            int level = 1;
            while (!q.empty()) {
                int sz = q.size();
                for (int i = 0; i < sz; i++) {
                    auto [s, idx] = q.front(); q.pop(); // s 为棋盘状态，idx 为 s 里 0 的位置
                    int x = idx / n, y = idx % n; // (x, y) 为 0 的位置
                    for (auto& [dx, dy] : directions) {
                        int xx = x + dx, yy = y + dy;
                        if (legal(xx, yy)) {
                            int pos = xx * n + yy;
                            string next = s;
                            swap(next[idx], next[pos]);
                            if (next == "123450") return level;
                            if (!vis.count(next)) {
                                q.push({next, pos});
                                vis.insert(next);
                            }
                        }
                    }
                }
                level++;
            }
            return -1;
        };

        return bfs();
    }

    // 这题也可以用 A* 来搜索，不过 A* 不改变最坏情况的时间复杂度
};

int main(int argc, char const *argv[]) {
    Solution773 solu;
    // cout << solu.slidingPuzzle(*new vector<vector<int>>{{1,2,3},{4,0,5}}) << endl;
    cout << solu.slidingPuzzle(*new vector<vector<int>>{{4,1,2},{5,0,3}}) << endl;
    return 0;
}