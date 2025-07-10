/*
url: https://leetcode.cn/problems/number-of-provinces/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution547 {
public:
    // 此题 graph 为邻接矩阵
    int findCircleNum(vector<vector<int>>& graph) {
        int n = graph.size();
        int ans = 0;
        vector<int> vis(n);

        auto dfs = [&](auto &dfs, int r) -> void {
            vis[r] = true;
            for (int next = 0; next < n; next++) {
                if (graph[r][next] && next != r && !vis[next]) { // 这里可以不写 next != r 的判断
                    dfs(dfs, next);
                }
            }
        };

        
        for (int i = 0; i < n; i++) {
            if (!vis[i]) { // 这里保证了每个dfs分量的起点是未访问的
                ans++;
                dfs(dfs, i);
            }
        }
    
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution547 solu;
    // cout << solu.findCircleNum(*new vector<vector<int>>{{1,1,0},{1,1,0},{0,0,1}}) << endl;
    cout << solu.findCircleNum(*new vector<vector<int>>{{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}}) << endl;
    return 0;
}