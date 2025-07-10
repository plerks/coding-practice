/*
url: https://leetcode.cn/problems/find-eventual-safe-states/
参考: https://leetcode.cn/problems/find-eventual-safe-states/solutions/916155/zhao-dao-zui-zhong-de-an-quan-zhuang-tai-yzfz/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution802 {
public:
    /* 参考官方题解，这题的题目没说清楚，以为是不能经过非安全节点，实际是必须能走到安全节点结束，
    题意是：若起始节点位于一个环内，或者能到达一个环，则该节点不是安全的。否则，该节点是安全的。
    
    如果是不能经过非安全节点，得先找出安全节点，然后用 Floyd 或者 对每个节点做一次独立的dfs ，找出节点之间可达性？
    
    如果是有向图找环，需要用 UNDISCOVERED, DISCOVERED, VISITED 三种状态来标记节点，不能用简单的vis数组，
    必须用三种状态来判断环，因为这是有向图，后向边代表找到了环，而跨边不是，用vis无法区分后向边和跨边。

    LeetCode管这个叫三色标记法，不过这题不止是要找环，还要找环上的所有节点以及会进入环的节点，状态定义还不一样。
    LeetCode207的三色标记法才是最原始的定义。

    此题的定义是：
    0. UNDISCOVERED
    1. DISCOVERED 或者 已经确认其与环关联    (或者说暂时认为其与环关联，不安全？)
    2. 安全节点，即节点不在环上，也不会进入环

    注意此题图中可能包含自环。
    */
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        // 0. UNDISCOVERED
        // 1. DISCOVERED 或者 已经确认其与环关联
        // 2. 安全节点，不在环上，也不会进入环
        vector<int> color(n, 0);

        // 返回节点是否安全
        auto dfs = [&](auto& dfs, int x) -> bool {
            if (color[x] != 0) return color[x] == 2;
            color[x] = 1; // 暂时直接认为其与环关联，不安全
            for (int y : graph[x]) {
                if (!dfs(dfs, y)) { // y不安全
                    return false; // 则x不安全，上面认为color[x] = 1是正确的，不用改
                }
            }
            // 能到这里，说明x安全
            color[x] = 2;
            return true;
        };

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (dfs(dfs, i)) ans.push_back(i);
        }

        return ans;
    }

    /* 官方题解解法二，在反图上拓扑排序。
    如果一个节点没有出边，其是安全的，若一个节点出边相连的边都是安全节点，则此节点是安全的。
    于是，可以把边全反向，然后在反图上拓扑排序，所有进过队列的点都是安全的。
    */
    vector<int> eventualSafeNodes_implementation2(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> rg(n);
        vector<int> indeg(n);
        for (int i = 0; i < n; i++) {
            for (int j : graph[i]) {
                rg[j].push_back(i);
                indeg[i]++;
            }
        }

        // 在rg上拓扑排序
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int y : rg[x]) {
                indeg[y]--;
                if (indeg[y] == 0) {
                    q.push(y);
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) ans.push_back(i);

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution802 solu;
    auto a = solu.eventualSafeNodes(*new vector<vector<int>>{{1,2},{2,3},{5},{0},{5},{},{}});

    auto b = solu.eventualSafeNodes(*new vector<vector<int>>{{1,2},{2,3},{5},{0},{5},{},{}});
    return 0;
}