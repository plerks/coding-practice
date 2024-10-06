/*
url: https://leetcode.cn/problems/remove-methods-from-project/description/
标签: LeetCode第418场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3310 {
public:
    // 周赛时这题没理清楚逻辑就开始写了，导致用了很多时间，这题是先要看有没有非可疑节点指向可疑节点，若有则直接返回[0 - n)，若没有则返回所有非可疑节点
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        for (auto &e : invocations) {
            graph[e[0]].push_back(e[1]);
        }

        vector<int> visited(n, false);
        vector<int> suspicious(n);

        auto dfs = [&](auto &dfs, int root) {
            if (visited[root]) return;
            visited[root] = true;
            suspicious[root] = true;
            for (auto &next : graph[root]) dfs(dfs, next);
        };

        dfs(dfs, k);

        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (suspicious[i]) continue;
            for (auto &x : graph[i]) {
                if (suspicious[x]) {
                    vector<int> ans(n);
                    iota(ans.begin(), ans.end(), 0);
                    return ans;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) ans.push_back(i);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3310 solu;
    int n = 4;
    int k = 1;
    vector<vector<int>> invocations = {{1,2},{0,1},{3,2}};
    auto a = solu.remainingMethods(n, k, invocations);
    return 0;
}
