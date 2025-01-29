/*
url: https://leetcode.cn/problems/longest-special-path/
参考: https://leetcode.cn/problems/longest-special-path/solutions/3051377/shu-shang-hua-chuang-pythonjavacgo-by-en-rh5m/
相关: LeetCode3. 无重复字符的最长子串
标签: LeetCode第148场双周赛, 树上滑窗
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3425 {
public:
    /* 参考灵茶题解，树上滑窗，
    对每条路径，进行滑窗，在这个过程中，需要记录当前节点的颜色上一次出现的最近位置(深度)，为了
    计算路径长度，将路径上经过的路径长度之和加起来作前缀和
    */
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> g(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        pair<int, int> ans = {-1, 0}; // 路径长度，路径节点数的负数(取相反数，这样就直接用pair的比较大小逻辑)
        vector<int> dis{0}; // 路径上边长度的前缀和
        unordered_map<int, int> last_depth; // last_depth[color]表示color在路径上上一次出现的深度(从1开始计数)

        // x为当前dfs到的节点，fa为上一个访问的节点，top_depth为当前滑窗root的深度
        auto dfs = [&](auto &dfs, int x, int fa, int top_depth) -> void {
            int color = nums[x]; // 当前节点的颜色
            int old_depth = last_depth[color];
            top_depth = max(old_depth, top_depth); // 滑窗上端点向下移动

            // 现在窗口中没有颜色相同的节点，路径长度用前缀和得出，路径节点数用深度差得出(记录负数)
            ans = max(ans, {dis.back() - dis[top_depth], -(dis.size() - top_depth)});

            last_depth[color] = dis.size(); // 这里递归实例的副作用需要后续进行恢复

            // 窗口下端点滑动
            for (auto [y, w] : g[x]) {
                if (y == fa) continue;
                dis.push_back(dis.back() + w);
                dfs(dfs, y, x, top_depth);
                dis.pop_back(); // 恢复现场
            }
            last_depth[color] = old_depth; // x回退时恢复现场
        };
        dfs(dfs, 0, -1, 0);
        return {ans.first, -ans.second};
    }
};

int main(int argc, char const *argv[]) {
    Solution3425 solu;
    auto a = solu.longestSpecialPath(*new vector<vector<int>>{{0,1,2},{1,2,3},{1,3,5},{1,4,4},{2,5,6}}, *new vector<int>{2,1,2,1,3,1});
    return 0;
}