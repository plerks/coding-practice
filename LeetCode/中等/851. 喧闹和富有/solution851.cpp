/*
url: https://leetcode.cn/problems/loud-and-rich/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution851 {
public:
    /*
    所有拥有的钱肯定不少于 person x，如何才是肯定不少于？
    拓扑排序有不能确定顺序的节点关系，要摒除这一种情况，对于依赖关系的反图，dfs(x)能走到的点才是一定比x rich的。
    要求反图dfs(x)能走到的点的quite最小值，按原图的拓扑序来dp计算，f[x] = min(f[反图中x的neighbor], quite[x])
    */
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> g(n);
        vector<vector<int>> ig(n); // 反图
        for (auto &vec : richer) {
            int u = vec[0], v = vec[1];
            g[u].push_back(v);
            ig[v].push_back(u);
        }

        vector<int> order = topo_order(g);
        vector<int> ans(n); // 最小人
        vector<int> val(n); // 最小值
        for (int x : order) {
            int mi = quiet[x];
            int person = x;
            for (int y : ig[x]) {
                // quiet 的所有值互不相同
                if (val[y] < mi) {
                    person = ans[y];
                    mi = val[y];
                }
            }
            ans[x] = person;
            val[x] = mi;
        }
        return ans;
    }

    vector<int> topo_order(vector<vector<int>>& g) {
        int n = g.size();
        vector<int> indeg(n);
        for (int x = 0; x < n; x++) {
            for (int y : g[x]) {
                indeg[y]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        vector<int> topo_order;
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

    // 参考宫水三叶题解，不需要建立反图，拓扑排序时顺便算就行了
    vector<int> loudAndRich_implementation2(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> g(n);
        for (auto &vec : richer) {
            int u = vec[0], v = vec[1];
            g[u].push_back(v);
        }

        vector<int> indeg(n);
        for (int x = 0; x < n; x++) {
            for (int y : g[x]) {
                indeg[y]++;
            }
        }

        vector<int> ans(n); // 最小人
        iota(ans.begin(), ans.end(), 0);
        // 不需要记录最小值，quiet[ans[x]]就是最小值
        // vector<int> val(n, INT_MAX); // 最小值
        
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();

            if (quiet[x] < quiet[ans[x]]) {
                ans[x] = x;
            }

            for (int y : g[x]) {
                indeg[y]--;
                if (indeg[y] == 0) q.push(y);

                // 松弛邻居
                if (quiet[ans[x]] < quiet[ans[y]]) {
                    ans[y] = ans[x];
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution851 solu;
    auto a = solu.loudAndRich(*new vector<vector<int>>{{1,0},{2,1},{3,1},{3,7},{4,3},{5,3},{6,3}},
                                *new vector<int>{3,2,5,4,6,1,7,0});

    auto b = solu.loudAndRich(*new vector<vector<int>>{{1,0},{2,1},{3,1},{3,7},{4,3},{5,3},{6,3}},
                                *new vector<int>{3,2,5,4,6,1,7,0});
    return 0;
}