/*
url: https://leetcode.cn/problems/shortest-path-with-alternating-colors/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1129 {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<pair<int, int>>> g(n);
        const int BLANK = 0, RED = 1, BLUE = 2;
        for (auto& v : redEdges) {
            int a = v[0], b = v[1];
            g[a].push_back({b, RED});
        }

        for (auto& v : blueEdges) {
            int a = v[0], b = v[1];
            g[a].push_back({b, BLUE});
        }

        queue<tuple<int, int>> q; // (节点，上一步颜色)
        
        // 可以用vis，这题bfs就行，不用dis
        vector<vector<int>> dis(n, vector<int>(3, INT_MAX)); // dis[node][color]表示node，上一步颜色为color的情况下的最小距离

        q.push({0, 0});
        dis[0][0] = 0;
        // 检查颜色是否交替
        auto legal = [&](int x, int y) {
            if (x == BLANK || y == BLANK) return true;
            return x != y;
        };
        for (int level = 0; !q.empty(); level++) {
            int size = q.size();
            for (int _ = 0; _ < size; _++) {
                auto [node, color] = q.front(); q.pop();
                dis[node][color] = level;
                for (auto [next, edge_color] : g[node]) {
                    if (legal(color, edge_color) && dis[next][edge_color] == INT_MAX) {
                        q.push({next, edge_color});
                        dis[next][edge_color] = level;
                    }
                }
            }
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int t = min({dis[i][0], dis[i][1], dis[i][2]});
            if (t == INT_MAX) t = -1;
            ans[i] = t;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1129 solu;
    // auto a = solu.shortestAlternatingPaths(3, *new vector<vector<int>>{{0,1},{1,2}}, *new vector<vector<int>>{});
    auto b = solu.shortestAlternatingPaths(3, *new vector<vector<int>>{{0,1},{0,2}}, *new vector<vector<int>>{{1,0}});
    return 0;
}