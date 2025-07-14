/*
url: https://leetcode.cn/problems/largest-color-value-in-a-directed-graph/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1857 {
public:
    /* 应该可以记忆化搜索，这里用拓扑排序来dp，枚举每个点作为路径尾部
    */
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> g(n);
        vector<int> indeg(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            indeg[v]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        int ans = 1;

        // 最优路径一定能是以那个最优color为首尾的，但是仍然要记录选择其它颜色的最大值，否则接不上，例如 aaca
        vector<vector<int>> len(n, vector<int>(26)); // 以i结尾，选择颜色color的最大长度

        int topo_cnt = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            topo_cnt++;
            int color = colors[x] - 'a';
            len[x][color] = max(len[x][color], 1);
            // 也可以这里：ans = max(ans, len[x][color]); 最优路径一定能以那个最优color结尾

            // x去刷表y
            for (int y : g[x]) {
                for (int c = 0; c < 26; c++) {
                    len[y][c] = max(len[y][c], len[x][c] + (colors[y] - 'a' == c));
                    ans = max(ans, len[y][c]);
                }
                indeg[y]--;
                if (indeg[y] == 0) q.push(y);
            }
        }

        if (topo_cnt < n) return -1;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1857 solu;
    cout << solu.largestPathValue("abaca", *new vector<vector<int>>{{0,1},{0,2},{2,3},{3,4}}) << endl;
    return 0;
}