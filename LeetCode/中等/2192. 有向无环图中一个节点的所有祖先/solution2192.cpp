/*
url: https://leetcode.cn/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/
参考: https://leetcode.cn/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/solutions/2723203/liang-chong-fang-fa-ni-xiang-zheng-xiang-rwjs/
      https://leetcode.cn/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/solutions/1364674/you-xiang-wu-huan-tu-zhong-yi-ge-jie-dia-6ed5/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2192 {
public:
    // 暴力，维护路径的前缀节点，从每个点出发都做一遍完整的dfs，然后排序去重，77 / 80 个通过的测试用例，会超内存
    vector<vector<int>> getAncestors_mle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
        }

        vector<vector<int>> ans(n);

        vector<int> vis(n);
        auto dfs = [&](auto &dfs, int r, vector<int>& ancestors) -> void {
            vis[r] = true;
            for (int next : g[r]) {
                if (!vis[next]) {
                    ancestors.push_back(r);
                    for (int ancestor : ancestors) ans[next].push_back(ancestor);
                    dfs(dfs, next, ancestors);
                    ancestors.pop_back();
                }
            }
        };

        for (int i = 0; i < n; i++) {
            vis = vector<int>(n);
            vector<int> ancestors;
            dfs(dfs, i, ancestors);
        }

        for (auto &v : ans) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        }

        return ans;
    }

    // 参考灵茶题解，确实需要从每个点出发做一遍完整的dfs（指新的一轮要把vis清空），
    // 但是每轮只记录一开始的根到ans[j]里，不要记录前缀，否则会加大量重复点进去
    // 由于是从小到大走轮次的，所以ans里是排好序了的
    // 题目的输入是一个有向无环图，但是此方法不需要这个条件，有环也可以
    // 时间复杂度 O(n(n + m))，n轮完整的dfs。用时55ms
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
        }

        vector<vector<int>> ans(n);

        vector<int> vis(n, -1); // 别忘了初始化为特异值-1
        int start; // dfs一开始的起点
        auto dfs = [&](auto &dfs, int r) -> void {
            vis[r] = start;
            if (r != start) ans[r].push_back(start); // start是从小到大遍历的，所以ans里是排好序了的。r != start 的判断是为了防止加入自己
            for (int next : g[r]) {
                if (vis[next] != start) {
                    // 也可以这里写 ans[next].push_back(start);
                    dfs(dfs, next);
                }
            }
        };

        for (start = 0; start < n; start++) {
            /* 小技巧：
            本来此题这里是要把vis重新清空做完全新一轮的dfs的，
            但是每次dfs start不同，可以用特异值start作为visited标记，不需要重新初始化vis
            */
            dfs(dfs, start);
        }

        return ans;
    }

    /* 灵茶题解另一种解法，把所有边反向，从i dfs能到达的点即为ans[i]。
    一次dfs完成后，遍历vis，访问过的点就是ans[i]，这样就能保证ans[i]是排好序的

    时间复杂度 O(n(n + m) + n^2)
    用时81ms

    题目的输入是一个有向无环图，但是此方法不需要这个条件，有环也可以
    */
    vector<vector<int>> getAncestors_implementation2(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[1]].push_back(e[0]); // 反向边
        }

        vector<vector<int>> ans(n);
        vector<int> vis(n, -1);

        int start;
        auto dfs = [&](auto &dfs, int r) -> void {
            vis[r] = start;
            for (int next : g[r]) {
                if (vis[next] != start) dfs(dfs, next);
            }
        };

        for (start = 0; start < n; start++) {
            dfs(dfs, start);
            for (int i = 0; i < n; i++) { // 这样ans[start]就是顺序的
                // ans[start] 不含 start
                if (i != start && vis[i] == start) ans[start].push_back(i);
            }
        }

        return ans;
    }

    /* 官方题解解法，按拓扑排序的方式遍历一遍图，一个节点的祖先为 其父节点的祖先 ∪ 父节点

    此方法就需要用到图为有向无环图的条件了，因为要拓扑排序

    时间复杂度：
        这题的拓扑排序部分由于要遍历unordered_set，每次set大小最多为n，总时间 n + m + mn
        ans排序部分 n * nlogn
        总时间复杂度 O(mn + n^2 * logn)
    用时358ms
    */
    vector<vector<int>> getAncestors_implementation3(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        vector<int> indeg(n); // 入度
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            indeg[e[1]]++;
        }

        vector<unordered_set<int>> ancestors(n); // 一个节点的祖先节点(不包括自己)
        queue<int> q; // 拓扑排序
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) { // 邻居
                // v的祖先包括父节点u以及u的祖先
                ancestors[v].insert(u);
                for (int a : ancestors[u]) {
                    ancestors[v].insert(a);
                }
                indeg[v]--;
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        vector<vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            for (int node : ancestors[i]) {
                ans[i].push_back(node);
            }
            sort(ans[i].begin(), ans[i].end());
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2192 solu;
    auto a = solu.getAncestors(8, *new vector<vector<int>>{{0,3},{0,4},{1,3},{2,4},{2,7},{3,5},{3,6},{3,7},{4,6}});
    auto b = solu.getAncestors_implementation2(8, *new vector<vector<int>>{{0,3},{0,4},{1,3},{2,4},{2,7},{3,5},{3,6},{3,7},{4,6}});
    return 0;
}