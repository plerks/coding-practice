/*
url: https://leetcode.cn/problems/minimize-malware-spread/
相关: LeetCode928. 尽量减少恶意软件的传播 II
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution924 {
public:
    // 此题为无向图，graph[i][j] == graph[j][i]
    // 时间复杂度 O(n^3)
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();

        vector<int> vis(n, -1);
        auto bfs = [&](int remove) {
            queue<int> q;
            for (int node : initial) {
                if (node == remove) continue;
                q.push(node);
                vis[node] = remove; // 用特异值remove标记访问状态
            }
            int cnt = 0; // 感染数
            while (!q.empty()) {
                int x = q.front(); q.pop();
                for (int y = 0; y < n; y++) {
                    if (graph[x][y] == 0 || x == y) continue;
                    if (vis[y] != remove) {
                        q.push(y);
                        vis[y] = remove;
                        cnt++;
                    }
                }
            }
            return cnt;
        };

        int min = INT_MAX;
        int ans = INT_MAX;
        for (int node : initial) {
            int cnt = bfs(node); // 多源bfs，除去initial[i]
            if (cnt < min) {
                ans = node;
                min = cnt;
            }
            else if (cnt == min) ans = std::min(ans, node);
        }
        return ans;
    }

    /* 参考灵茶题解，更优的做法，
    由于只能删除一个节点，所以，要找的其实是，最大的只含有一个感染节点的连通分量

    这可以通过dfs进行，如何记录连通分量中的感染节点？用一个set吗？
    可以不用，用-1代表没遇到感染节点，-2代表遇到>=2个感染节点，一个x (x >= 0) 代表有一个感染节点，且x就是感染节点编号。
    如果没有只含有一个感染节点的连通分量，则删除哪个点，被感染的节点数都一样，返回initial的最小值

    时间复杂度 O(n^2)，只需要对graph做一遍完整的dfs
    */
    int minMalwareSpread_implementation2(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();

        vector<int> vis(n);
        int status;
        unordered_set<int> st(initial.begin(), initial.end());

        auto dfs = [&](auto &dfs, int x) -> int {
            vis[x] = true;
            int size = 1;
            if (st.count(x)) {
                status = status == -1 ? x : -2;
            }
            for (int y = 0; y < n; y++) {
                if (graph[x][y] && !vis[y]) {
                    size += dfs(dfs, y);
                }
            }
            return size;
        };

        int mx = 0;
        int ans = -1;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                status = -1;
                int size = dfs(dfs, i);
                if (status >= 0) { // 连通分量恰一个污染点
                    if (size > mx) {
                        mx = size;
                        ans = status;
                    }
                    else if (size == mx) ans = min(ans, status);
                }
            }
        }
        return ans == -1 ? *min_element(initial.begin(), initial.end()) : ans;
    }

    /* 灵茶题解扩展: 题目改成移除 k 个节点，怎么求？
    求出每个连通分量的size和感染节点数。问题转化为0-1背包问题，必须把一个连通分量里的感染节点全部移除才能保证不被感染，
    感染节点数为商品重量，size为商品收益，k为背包容量
    */
};

int main(int argc, char const *argv[]) {
    Solution924 solu;
    // cout << solu.minMalwareSpread(*new vector<vector<int>>{{1,1,0},{1,1,0},{0,0,1}}, *new vector<int>{0, 1}) << endl;
    cout << solu.minMalwareSpread(*new vector<vector<int>>{{1,1,1},{1,1,1},{1,1,1}}, *new vector<int>{1, 2}) << endl;

    cout << solu.minMalwareSpread_implementation2(*new vector<vector<int>>{{1,1,1},{1,1,1},{1,1,1}}, *new vector<int>{1, 2}) << endl;
    return 0;
}