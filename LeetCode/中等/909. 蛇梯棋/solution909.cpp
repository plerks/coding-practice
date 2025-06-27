/*
url: https://leetcode.cn/problems/snakes-and-ladders/
相关: LeetCode1293. 网格中的最短路径, LeetCode1210. 穿过迷宫的最少移动次数, LeetCode675. 为高尔夫比赛砍树
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution909 {
public:
    // 和 LeetCode1293. 网格中的最短路径 类似，也有种优先队列Dijkstra的感觉，不过这题vis不需要加维度，要简单些
    int snakesAndLadders(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();

        // 由点的编号(从1开始)，得到其行列号
        auto to_pos = [&](int idx) -> pair<int, int> {
            int d_i = (idx - 1) / n; // idx下方有 d_i 行
            int d_r = (idx - 1) % n;
            int i = m - d_i - 1; // 则i上方有 m - d_i - 1 行
            bool even = d_i % 2 == 0; // 若向上走了的行数为偶数，r向右走，否则向左
            int j;
            if (even) j = d_r;
            else j = n - 1 - d_r;
            return {i, j};
        };

        // vis表示是否已经到过
        // vis不要再有一维是掷骰子数，这可能导致走环(掷数增加，!vis，入队导致死循环)。后面更多的掷骰子次数到达同一个位置，这种走法直接舍弃
        vector<int> vis(m * n + 1);

        queue<int> q;
        q.push(1);
        vis[1] = true;
        int level = 0; // 当前的掷骰子数
        while (!q.empty()) {
            int size = q.size();
            level++;
            for (int i = 0; i < size; i++) {
                int idx = q.front(); q.pop();
                auto [x, y] = to_pos(idx);
                for (int step = 1; step <= 6; step++) {
                    int next_idx = idx + step; // 掷骰子要走到的位置
                    auto [xx, yy] = to_pos(next_idx);
                    if (next_idx > m * n) continue; // 这里可以改成直接break; 后面一定也越界
                    if (board[xx][yy] != -1) { // 要跳
                        next_idx = board[xx][yy];
                        auto t = to_pos(next_idx);
                        xx = t.first; yy = t.second;
                    }
                    // 题目保证编号为 1 和 m * n 的位置没有蛇或梯子，不需考虑掷骰子到终点又跳走，这样算不算到达终点的情况
                    if (next_idx == m * n) return level;

                    if (!vis[next_idx]) {
                        // cout << next_idx << " " << level << endl;
                        q.push(next_idx);
                        vis[next_idx] = true;
                    }
                }
            }
        }

        return -1; // 比如掷所有骰子点数都要走到返回起点的梯子，就到达不了终点
    }
};

int main(int argc, char const *argv[]) {
    Solution909 solu;
    /* cout << solu.snakesAndLadders(*new vector<vector<int>>{
                                    {-1,-1,-1,-1,-1,-1},
                                    {-1,-1,-1,-1,-1,-1},
                                    {-1,-1,-1,-1,-1,-1},
                                    {-1,35,-1,-1,13,-1},
                                    {-1,-1,-1,-1,-1,-1},
                                    {-1,15,-1,-1,-1,-1}}) << endl; */

    cout << solu.snakesAndLadders(*new vector<vector<int>>{{1,1,-1},{1,1,1},{-1,1,1}}) << endl;
    return 0;
}