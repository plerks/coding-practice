/*
url: https://leetcode.cn/problems/length-of-longest-v-shaped-diagonal-segment/
参考: https://www.bilibili.com/video/BV1pmAGegEcw/
      https://leetcode.cn/problems/length-of-longest-v-shaped-diagonal-segment/solutions/3076747/ji-yi-hua-sou-suo-pythonjavacgo-by-endle-jrjj/
标签: LeetCode第437场周赛, 记忆化搜索
*/

// 这次周赛2题

#include <bits/stdc++.h>

using namespace std;

class Solution3459 {
public:
    /* 参考灵茶题解，再结合我周赛时写的没调出来的代码，
    周赛时错误的地方在于: 
        1. dfs里面res要初始化为1而不是0，执行到res那里的话一定是合法的位置，至少可以走一个点。
        2. 这题可以转一次的意思是全场最多转一次前进方向，而不是在一个点最多转一次。想想也是，如果是后者的话可以走成环了。
    此外，dfs的参数里不需要存当前所在的格子的值status，周赛时写的dfs参数带了status，记忆化memo也有一维是status，实际并不需要。

    这题属于dfs无法转为dp的情况，难以知道终点，也难以确定计算过程。
    */
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        vector<pair<int, int>> start;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    start.push_back({i, j});
                }
            }
        }

        auto otherstat = [](int status) {
            return status == 1 ? 2 : status == 0 ? 2 : 0;
        };

        auto legal = [&](int x, int y) {
            return (0 <= x && x < m && 0 <= y && y < n);
        };

        vector<vector<array<array<int, 2>, 4>>> memo(m, vector<array<array<int, 2>, 4>>(n)); // 这题可以用0来表示未填数据

        // dfs表示能走的点的数量。dirc为当前方向，turn为是否还剩转弯次数
        auto dfs = [&](auto &dfs, int x, int y, int dirc, int turn) -> int {
            if (!legal(x, y)) return 0;
            if (memo[x][y][dirc][turn] > 0) return memo[x][y][dirc][turn];
            int res = 1; // 这里要是1，如果没有下一步落脚的地方，则能走的点的数量为1
            int xx1 = x + directions[dirc][0];
            int yy1 = y + directions[dirc][1];
            if (legal(xx1, yy1) && grid[xx1][yy1] == otherstat(grid[x][y])) {
                res = max(res, 1 + dfs(dfs, xx1, yy1, dirc, turn));
            }

            int xx2 = x + directions[(dirc + 1) % 4][0];
            int yy2 = y + directions[(dirc + 1) % 4][1];
            if (turn && legal(xx2, yy2) && grid[xx2][yy2] == otherstat(grid[x][y])) {
                res = max(res, 1 + dfs(dfs, xx2, yy2, (dirc + 1) % 4, 0));
            }
            memo[x][y][dirc][turn] = res;
            return res;
        };

        int ans = 0;
        for (auto &p : start) {
            ans = max(ans, dfs(dfs, p.first, p.second, 0, 1));
            ans = max(ans, dfs(dfs, p.first, p.second, 1, 1));
            ans = max(ans, dfs(dfs, p.first, p.second, 2, 1));
            ans = max(ans, dfs(dfs, p.first, p.second, 3, 1));
        }
        return ans;
    }

    /* 灵茶题解中有个小技巧，上面的dfs写法的考虑方式是：当前在(x, y)并且上一步走到当前位置依靠的方向是dirc，
    然后接下来可以怎么走，这样需要算xx1, yy1, xx2, yy2两次。
    换个考虑方式，当前在(x, y)并且这一步选择以dirc为方向走，这样就能直接确定目的地，不需要计算两组坐标，只要
    计算一组就行了，然后枚举两种可能的方向就行。这样代码会简洁一些。
    */
    int lenOfVDiagonal_implementation2(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        vector<pair<int, int>> start;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    start.push_back({i, j});
                }
            }
        }

        auto otherstat = [](int status) {
            return status == 1 ? 2 : status == 0 ? 2 : 0;
        };

        auto legal = [&](int x, int y) {
            return (0 <= x && x < m && 0 <= y && y < n);
        };

        vector<vector<array<array<int, 2>, 4>>> memo(m, vector<array<array<int, 2>, 4>>(n)); // 这题可以用0来表示未填数据

        // dfs表示能走的点的数量。dirc为当前方向，turn为是否还剩转弯次数
        auto dfs = [&](auto &dfs, int x, int y, int dirc, int turn) -> int {
            if (!legal(x, y)) return 0;
            if (memo[x][y][dirc][turn] > 0) return memo[x][y][dirc][turn];
            int xx = x + directions[dirc][0];
            int yy = y + directions[dirc][1];
            int res = 1; // 这里要是1，如果没有下一步落脚的地方，则能走的点的数量为1
            if (legal(xx, yy) && grid[xx][yy] == otherstat(grid[x][y])) {
                res = max(res, 1 + dfs(dfs, xx, yy, dirc, turn));
                if (turn) { // 有转向机会的话再多考虑下转向的情况
                    res = max(res, 1 + dfs(dfs, xx, yy, (dirc + 1) % 4, 0));
                }
            }
            memo[x][y][dirc][turn] = res;
            return res;
        };

        int ans = 0;
        for (auto &p : start) {
            ans = max(ans, dfs(dfs, p.first, p.second, 0, 1));
            ans = max(ans, dfs(dfs, p.first, p.second, 1, 1));
            ans = max(ans, dfs(dfs, p.first, p.second, 2, 1));
            ans = max(ans, dfs(dfs, p.first, p.second, 3, 1));
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3459 solu;
    cout << solu.lenOfVDiagonal(*new vector<vector<int>>{{2,2,1,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}}) << endl;
    cout << solu.lenOfVDiagonal_implementation2(*new vector<vector<int>>{{2,2,1,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}}) << endl;
    return 0;
}