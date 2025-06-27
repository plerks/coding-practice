/*
url: https://leetcode.cn/problems/cut-off-trees-for-golf-event/
相关: LeetCode1293. 网格中的最短路径, LeetCode909. 蛇梯棋, LeetCode1210. 穿过迷宫的最少移动次数
标签: 【算法题单】网格图
*/

#include <bits/stdc++.h>

using namespace std;

class Solution675 {
public:
    // 我的解法，2056ms，能通过。用的类似 LeetCode1293、909、1210 等题的方法。
    // 时间复杂度应该是 O((mn)^2)，一共最多 m * n * (mn) 个状态。不过应该是常数比较大，所以用了2000多ms
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size(), n = forest[0].size();

        const vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto legal = [&](int i, int j) {
            return 0 <= i && i < m && 0 <= j && j < n;
        };

        vector<int> h;
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
            if (forest[i][j] > 1) { // 是树
                h.push_back(forest[i][j]);
            }
        }
        sort(h.begin(), h.end());
        const int total = h.size();
        
        queue<tuple<int, int, int>> q; // (x, y, c) 坐标与砍过的树的数量
        vector<vector<vector<int>>> vis(m, vector<vector<int>>(n, vector<int>(total + 1))); // 砍过的树最多为total，不过这时返回了，所以第三维长度为total不会越界
        if (forest[0][0] == h[0]) {
            q.push({0, 0, 1});
            vis[0][0][1] = true;
        }
        else if (forest[0][0] == 1 || forest[0][0] > h[0]) { // 非障碍，为空地或更高的树
            q.push({0, 0, 0});
            vis[0][0][0] = true;
        }

        for (int level = 1; !q.empty(); level++) { // level为这一轮要进队的节点的深度
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [x, y, c] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int xx = x + dx, yy = y + dy;

                    if (legal(xx, yy) && forest[xx][yy] != 0) { // 非墙
                        // 空地或更高的树
                        // 如果你站的地方有一棵树，那么你可以决定是否要砍倒它。所以遇到更高的树可以当空地
                        // 如果是更矮的树也可以当空地走，比如 9 走到 12 再 走到 5，都不能砍，但是可以走
                        if ((forest[xx][yy] == 1 || forest[xx][yy] > h[c] || forest[xx][yy] < h[c]) && !vis[xx][yy][c]) {
                            q.push({xx, yy, c});
                            vis[xx][yy][c] = true;
                        }
                        // (xx, yy)处是树
                        else if (forest[xx][yy] == h[c]) { // 树，得是h[c]才能砍
                            if (c + 1 == total) return level; // 砍完最后那棵树
                            else if (!vis[xx][yy][c + 1]) {
                                q.push({xx, yy, c + 1});
                                vis[xx][yy][c + 1] = true;
                            }
                        }
                    }
                }
            }
            int debug = 1; // 在这里断下来时，q中的所有节点的层数为level
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution675 solu;
    // cout << solu.cutOffTree(*new vector<vector<int>>{{1,2,3},{0,0,4},{7,6,5}}) << endl;

    // 这个用例全是高树，把高度整成编号
    vector<vector<int>> forest = {{54581641,64080174,24346381,69107959},
                                  {86374198,61363882,68783324,79706116},
                                  {668150,92178815,89819108,94701471},
                                  {83920491,22724204,46281641,47531096},
                                  {89078499,18904913,25462145,60813308}};
    vector<int> nums;
    for (int i = 0; i < forest.size(); i++) {
        for (int j = 0; j < forest[0].size(); j++) {
            nums.push_back(forest[i][j]);
        }
    }
    sort(nums.begin(), nums.end());
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); i++) mp[nums[i]] = i + 2;
    for (int i = 0; i < forest.size(); i++) {
        for (int j = 0; j < forest[0].size(); j++) {
            forest[i][j] = mp[forest[i][j]];
        }
    }
    cout << solu.cutOffTree(forest) << endl;

    return 0;
}