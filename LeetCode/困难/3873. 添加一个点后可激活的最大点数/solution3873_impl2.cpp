/*
url: https://leetcode.cn/problems/maximum-points-activated-with-one-addition/
参考: https://leetcode.cn/problems/maximum-points-activated-with-one-addition/solutions/3925851/jian-tu-bfs-by-tsreaper-2i6y/
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3873 {
public:
    // TsReaper 解法，一个分量内本来有 O(n^2) 条边，但是可以通过巧妙地建图使其只有 O(n) 条边
    // 然后再用 bfs/dfs 求分量大小即可
    int maxActivated(vector<vector<int>>& points) {
        int n = points.size();
        // 按坐标点来分类
        unordered_map<int, vector<int>> mpX, mpY;
        for (int i = 0; i < n; i++) {
            int x = points[i][0], y = points[i][1];
            // 只需要这两种横向/竖向的边就可以把分量连起来，而不需要 O(n^2) 条边
            mpX[x].push_back(i);
            mpY[y].push_back(i);
        }

        vector<int> g[n];
        auto build = [&](unordered_map<int, vector<int>> &mp) {
            for (auto& [_, vec] : mp) {
                for (int i = 1; i < vec.size(); i++) {
                    int u = vec[i], v = vec[i - 1];
                    g[u].push_back(v), g[v].push_back(u);
                }
            }
        };
        build(mpX), build(mpY);

        // 图建好了，求最大的两个分量的大小即可
        int mx1 = 0, mx2 = 0;

        vector<int> vis(n);
        auto bfs = [&](int r) {
            queue<int> q;
            q.push(r);
            vis[r] = true;
            int sz = 1;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                for (int nbr : g[node]) {
                    if (!vis[nbr]) {
                        q.push(nbr);
                        vis[nbr] = true;
                        sz++;
                    }
                }
            }
            return sz;
        };

        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            int sz = bfs(i);
            if (sz > mx1) {
                mx2 = mx1;
                mx1 = sz;
            }
            else if (sz > mx2) mx2 = sz;
        }

        return mx1 + mx2 + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3873 solu;
    cout << solu.maxActivated(*new vector<vector<int>>{{1,1},{1,2},{2,2}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{2,2},{1,1},{3,3}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{-1000000000,-1000000000},{1000000000,1000000000},{1,1}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{5,-4},{5,9}}) << endl;
    return 0;
}