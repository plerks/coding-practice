/*
url: https://leetcode.cn/problems/build-a-matrix-with-conditions/
标签: 【算法题单】图论算法, 构造
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2392 {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        // 只要能拓扑排序，就能知道k个数该在的行列
        // 行列独立，把rowConditions和colConditions分别拓扑排序
        vector<vector<int>> g(k);
        vector<int> indeg(k);
        for (auto &v : rowConditions) {
            int a = v[0] - 1, b = v[1] - 1;
            g[a].push_back(b);
            indeg[b]++;
        }
        vector<int> row_topo = topo_order(g);

        g = vector<vector<int>>(k);
        indeg = vector<int>(k);
        for (auto &v : colConditions) {
            int a = v[0] - 1, b = v[1] - 1;
            g[a].push_back(b);
            indeg[b]++;
        }
        vector<int> col_topo = topo_order(g);

        if (row_topo.size() < k || col_topo.size() < k) return {}; // 不能拓扑排序

        vector<pair<int, int>> pos(k + 1); // [1, k]的安放位置
        for (int i = 0; i < k; i++) {
            int x = row_topo[i] + 1;
            pos[x].first = i;
        }
        for (int i = 0; i < k; i++) {
            int x = col_topo[i] + 1;
            pos[x].second = i;
        }

        vector<vector<int>> ans(k, vector<int>(k));
        for (int i = 1; i <= k; i++) {
            ans[pos[i].first][pos[i].second] = i;
        }

        return ans;
    }

    vector<int> topo_order(vector<vector<int>>& g) {
        int n = g.size();
        vector<int> indeg(n);
        for (int x = 0; x < n; x++) {
            for (int y : g[x]) indeg[y]++;
        }

        vector<int> topo_order;
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            topo_order.push_back(x);
            for (int y : g[x]) {
                indeg[y]--;
                if (indeg[y] == 0) q.push(y);
            }
        }
        return topo_order;
    }
};

int main(int argc, char const *argv[]) {
    Solution2392 solu;
    auto a = solu.buildMatrix(3, *new vector<vector<int>>{{1,2},{3,2}},
                                *new vector<vector<int>>{{2,1},{3,2}});
    return 0;
}