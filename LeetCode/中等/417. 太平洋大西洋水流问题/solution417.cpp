/*
url: https://leetcode.cn/problems/pacific-atlantic-water-flow/
参考: https://leetcode.cn/problems/pacific-atlantic-water-flow/solutions/1447341/tai-ping-yang-da-xi-yang-shui-liu-wen-ti-sjk3/
相关: LeetCode542. 01 矩阵, LeetCode329. 矩阵中的最长递增路径
标签: 【算法题单】网格图, [special], 多源bfs
*/
#include <bits/stdc++.h>

using namespace std;

class Solution417 {
public:
    /* 我的解法，74 / 113 个通过的测试用例，超内存了。想法是，这题的连通性是单向的(非严格，相等值可以双向流)，5能流到4 而 4不能流到5，不能求连通分量，
    因为一个连通分量里的元素不一定都能流到外面，例如4只能通过5流到外面，5连通4，会导致忽略了4不能到5这件事。
    所以需要对每个点都dfs一遍，但是这会超时，于是再加上记忆化搜索。

    但是这题特殊，dfs + 记忆化 是不行的。

    这题由于可以走到相邻的高度值相同的点，例如 7 5₁ 5₂，dfs(5₁)依赖dfs(5₂)，dfs(5₂)又依赖dfs(5₁)，会有循环依赖，dfs的计算
    没有单向性，所以不能像 LeetCode329 一样直接记忆化搜索。
    
    如果要记忆化搜索的话，应该可以这样做：把相邻的相同值合并起来，作为一个新点，这样合并相等分量之后，虽然别处可能有相等的值，但是问题变成了
    每次只能走到严格更低的点，dfs就有单向性了，就可以记忆化搜索了。
    
    具体见 pacificAtlantic_mle() 里的注释
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
        /*
        这题和 LeetCode329. 矩阵中的最长递增路径 不同，可以走到相邻的高度值相同的点，不用vis控制，相邻的相等元素会无限dfs互拉。
        于是加上vis，但是这又有问题，[[7,2,..],[3,5,..],..]，dfs(7)，7先把2，3标记为已访问，dfs(5)就会认为不能用2，3了，于是会在memo
        里标记 5 不能到达边界。

        于是再加上 is_source 来控制，每次dfs，只能改变根节点的memo状态。
        
        但是这样又不是记忆化搜索了，遍历矩阵每个点进行dfs的过程中，右下部的点每次dfs计算了又不可以记忆化，时间复杂度是超了的。

        为什么只能改变根节点的memo？
        !vis避免了无限互拉，但是会wa，dfs(root)的结果一定是对的，其它与root节点值相等的node，dfs(node)结果都可能是错的。
        例如 7 5₁ 5₂，7能否到达边界 取决于 5₁是否能够到达边界，
        而 5₁是否能够到达边界 又取决于 5₂是否能够到达边界，这个循环依赖关系通过 vis 破除了，但是万一5₂真的需要经过5₁到达边界呢？强制5₂不能经过
        5₁，于是dfs(5₂)算出来为错误的false。不过虽然dfs(5₁)依赖dfs(5₂)，但是 5₁ 5₂ 5₁ ... 边界 的路，dfs(5₁)能通过另外一条路搜索到，所以
        虽然dfs(5₂)是错误的，dfs(5₁)却是对的。
        再来看，5₀ 5₁ 5₂，只有dfs(5₀)的结果一定是对的，dfs(5₁)和dfs(5₂)都可能是错的。

        所以，相邻的相等元素（一个等值分量），只有一个代表元的dfs()结果一定是对的。

        所以，一次dfs(i, j)，各个等值分量的代表元的memo是可以写的？
        否，pacificAtlantic_wa()是错的，漏了解。因为可能有这种情况：
        B A C，C很小，B分量可以 B -> A -> C，从而到达边界，但是dfs到B分量的时候，A分量已经被标记为visited了，会认为B到不了边界，
        所以漏解了。

        所以，每次dfs，只有一开始的那个点的memo是可以写的，只有一个点，子递归实例全都不可以改memo。

        总结：

        由于此题可以走到相邻的高度值相同的点，dfs没有单向性。需要vis避免无限互拉，但是这又会导致每轮dfs，只有根节点一个点的memo可以写。时间复杂度不对。

        应该可以这样做：把相邻的相同值合并起来，作为一个新点，这样合并相等分量之后，虽然别处可能有相等的值，但是问题变成了
        每次只能走到严格更低的点，就可以记忆化搜索了。
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

    vector<vector<int>> pacificAtlantic_wa(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        map<pair<int, int>, pair<bool, bool>> memo;
        vector<vector<int>> vis(m, vector<int>(n, false));
        
        auto dfs = [&](auto& dfs, int i, int j, int si, int sj) { // 能否流出左上和右下
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
                if (!legal(ii, jj)) {
                    auto [ok1, ok2] = dfs(dfs, ii, jj, ii, jj);
                    res.first |= ok1;
                    res.second |= ok2;
                }
                else if (!vis[ii][jj] && heights[i][j] >= heights[ii][jj]) {
                    if (heights[i][j] == heights[ii][jj]) {
                        auto [ok1, ok2] = dfs(dfs, ii, jj, si, sj);
                        res.first |= ok1;
                        res.second |= ok2;
                    }
                    else {
                        auto [ok1, ok2] = dfs(dfs, ii, jj, ii, jj);
                        res.first |= ok1;
                        res.second |= ok2;
                    }
                }
            }
            if (i == si && j == sj || heights[i][j] != heights[si][sj]) memo[{i, j}] = res;
            return res;
        };

        vector<vector<int>> ans;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vis = vector<vector<int>>(m, vector<int>(n, false));
                if (dfs(dfs, i, j, i, j) == pair{true, true}) {
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