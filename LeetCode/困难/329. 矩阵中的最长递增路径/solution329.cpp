/*
url: https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/
参考: https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/solutions/346614/ju-zhen-zhong-de-zui-chang-di-zeng-lu-jing-by-le-2/
相关: LeetCode417. 太平洋大西洋水流问题
标签: 【算法题单】网格图, 拓扑排序
*/
#include <bits/stdc++.h>

using namespace std;

class Solution329 {
public:
    // 要算最大长度，bfs要找最高能多少层。需要每个点都作为起点bfs一遍。不能多源bfs，因为路径可以绕路以更长，bfs得到了个最小距离。
    // 每个点都bfs一遍 + 记忆化搜索，超内存，104 / 139 个通过的测试用例
    // bfs + 记忆化 的时间复杂度是不对的，遍历matrix的过程中，往右下部bfs的部分，状态是在反复算，要用dfs + 记忆化
    int longestIncreasingPath_mle(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<vector<int>> memo(m, vector<int>(n, -1));

        int ans = 0;

        auto bfs = [&](int i, int j) {
            queue<pair<int, int>> q;
            vector<vector<int>> vis(m, vector<int>(n));
            q.push({i, j});
            vis[i][j] = true;
            int t = 0;
            int level;
            for (level = 0; !q.empty(); level++) { // level为此轮队中节点的层数(从0开始计数)
                int size = q.size();
                for (int _ = 0; _ < size; _++) {
                    auto [x, y] = q.front(); q.pop();
                    for (auto [dx, dy] : directions) {
                        int xx = x + dx, yy = y + dy;
                        if (legal(xx, yy) && matrix[xx][yy] > matrix[x][y]) { // 这里不能写&& !vis[xx][yy]，要用memo算距离
                            if (memo[xx][yy] != -1) {
                                t = max(t, level + 1 + memo[xx][yy]);
                            }
                            else {
                                q.push({xx, yy});
                                vis[xx][yy] = true;
                            }
                        }
                    }
                }
            }
            memo[i][j] = max(t, level); // 退出循环时，level代表最后一层空节点的层数，节点总数[0, level)
            ans = max(ans, memo[i][j]);
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bfs(i, j);
            }
        }
        
        return ans;
    }

    // 终点和起点的数字都不能确定，这题确实是需要每个点都作为起点计算一下，但是：
    // bfs + 记忆化 的时间复杂度是不对的，遍历matrix的过程中，往右下部bfs的部分，状态是在反复算，要用dfs + 记忆化
    // 时间复杂度O(mn)
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        int ans = 0;

        vector<vector<int>> memo(m, vector<int>(n, -1));

        auto dfs = [&](auto &dfs, int i, int j) {
            if (memo[i][j] != -1) return memo[i][j];
            int res = 1;
            for (auto [dx, dy] : directions) {
                int ii = i + dx, jj = j + dy;
                if (legal(ii, jj) && matrix[ii][jj] > matrix[i][j]) {
                    res = max(res, 1 + dfs(dfs, ii, jj));
                }
            }
            memo[i][j] = res;
            return res;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans = max(ans, dfs(dfs, i, j));
            }
        }
        
        return ans;
    }

    /* 参考官方题解，把记忆化搜索改成dp，这题的dfs计算顺序不是常见的矩阵那样按行列算，看起来像是记忆化搜索不好处理，只能用dp的样子。
    但是还是可以改成dp。关键在于，记忆化搜索有方向，是往值严格增大的方向前进的，路径的终点一定是周围没有更大的元素。所以反过来，
    按拓扑排序的顺序，每次找出度为0的点，就是新的一层。
    */
    int longestIncreasingPath_implementation2(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<vector<int>> outdegrees(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (auto [dx, dy] : directions) {
                    int ii = i + dx, jj = j + dy;
                    if (legal(ii, jj) && matrix[ii][jj] > matrix[i][j]) outdegrees[i][j]++;
                }
            }
        }

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (outdegrees[i][j] == 0) q.push({i, j});
            }
        }

        int level;
        for (level = 0; !q.empty(); level++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;
                    if (legal(xx, yy) && matrix[xx][yy] < matrix[x][y]) {
                        outdegrees[xx][yy]--;
                        if (outdegrees[xx][yy] == 0) q.push({xx, yy});
                    }
                }
            }
        }
        return level;
    }
};

int main(int argc, char const *argv[]) {
    Solution329 solu;
    // cout << solu.longestIncreasingPath_mle(*new vector<vector<int>>{{9,9,4},{6,6,8},{2,1,1}}) << endl;

    // cout << solu.longestIncreasingPath(*new vector<vector<int>>{{9,9,4},{6,6,8},{2,1,1}}) << endl;
    cout << solu.longestIncreasingPath(*new vector<vector<int>>{{7,7,5},{2,4,6},{8,2,0}}) << endl;

    cout << solu.longestIncreasingPath_implementation2(*new vector<vector<int>>{{7,7,5},{2,4,6},{8,2,0}}) << endl;
    return 0;
}