/*
url: https://leetcode.cn/problems/count-visited-nodes-in-a-directed-graph/
标签: 【算法题单】图论算法, [mark], 模板题
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2876 {
public:
    // n 个节点，每个节点一条出边，一定为基环树森林。
    // 找基环树分量，图是基环内向树森林。每个基环树，环上的点能到的点数量为环大小，树枝点能到的点数量为环大小 + 1
    // 如何区分基环树的环和树枝节点？
    // 参考<https://leetcode.cn/problems/count-visited-nodes-in-a-directed-graph/solutions/2464852/nei-xiang-ji-huan-shu-pythonjavacgo-by-e-zrzh/comments/2139686/>
    // 由于基环树从一个点出发dfs，一定能走完环。把中间的节点暂存，dfs发现已访问节点时既找到了环，退环上所有节点即可找到环上的所有节点
    // dfs的起点不一定是环上的点，例如 1 -> 2 -> 3 -> 4 -> 2，所以dfs(1)要dfs(2)，
    // 树枝节点能到达多少个点还未记录，对于树枝节点v，子dfs返回后，只要记录数组没被写，说明其为树枝，ans[u] = ans[v] + 1，v为u指出的点
    // 用时52ms
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        vector<int> ans(n, -1); // 每个点能到达的节点数(包括自身)
        int cur_code = 0; // 对节点编号
        vector<int> stack; // 记录调用链节点
        vector<int> codes(n, -1); // 每个节点的编号，-1代表未访问
        auto dfs = [&](auto& dfs, int x) -> void {
            if (codes[x] != -1) { // x访问过，x -> x 为环，stack里存了点
                int cnt = cur_code - codes[x]; // 环长
                while (stack.back() != x) { // 环上节点能到的节点数都为cnt
                    ans[stack.back()] = cnt;
                    stack.pop_back();
                }
                // 栈顶的 x 也要退
                ans[stack.back()] = cnt;
                stack.pop_back();
                return;
            }
            else {
                stack.push_back(x);
                codes[x] = cur_code++;
                // 注意这里不能换成 if (codes[edges[x]] == -1) ， 邻居节点被访问过，但是 ans 还没算，是要进 dfs 的，因为要退栈算环长度
                // codes == -1 起到了判断 DISCOVERED 的作用，ans == -1 起到了判断 VISITED 的作用
                // 这样就能在发现邻居已经 DISCOVERED 时判断：1. 是发现环 2. 是树枝节点发现了环上节点
                if (ans[edges[x]] == -1) dfs(dfs, edges[x]);
            }
            if (!stack.empty() && stack.back() == x) stack.pop_back(); // 由树枝节点找到的环，把栈中的树枝节点退掉，不过不写也可以对
            if (ans[x] == -1) { // dfs(x)完后还是-1，说明x在树枝上
                ans[x] = ans[edges[x]] + 1;
            }
        };

        for (int i = 0; i < n; i++) {
            if (codes[i] == -1) { // 未访问过
                dfs(dfs, i);
            }
        }

        return ans;
    }

    /* 参考灵茶题解，
    如何区分树枝节点与环上节点？
    用入度是否为0不行，树枝可能很长，树枝节点也可能有入度。
    拓扑排序，剩下的点就是环上的点。

    用时276ms
    */
    vector<int> countVisitedNodes_implementation2(vector<int>& edges) {
        int n = edges.size();
        vector<int> indeg(n);
        vector<vector<int>> rg(n); // 反图，原图每个节点一条出边，反图则不一定，所有要用二维数组
        for (int u = 0; u < n; u++) {
            int v = edges[u];
            indeg[v]++;
            rg[v].push_back(u);
        }
        
        // 拓扑排序
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int x = q.front(); q.pop();
            int y = edges[x];
            indeg[y]--;
            if (indeg[y] == 0) q.push(y);
        }
        // 拓扑排序后，树枝节点的indeg变成0了，这样就能区分基环节点与树枝节点了

        vector<int> ans(n);
        auto rdfs = [&](auto& rdfs, int x, int cnt) -> void {
            ans[x] = cnt;
            for (int y : rg[x]) {
                if (indeg[y] == 0) {
                    rdfs(rdfs, y, cnt + 1);
                }
            }
        };

        // 先找出环
        for (int i = 0; i < n; i++) {
            if (indeg[i] <= 0) continue;
            vector<int> ring; // 环上节点
            for (int x = i;;) {
                indeg[x] = -1; // 把环上节点入度标记为-1
                ring.push_back(x);
                x = edges[x];
                if (x == i) break;
            }
            // 从环上的每个节点出发，只往树枝的方向dfs反图(只递归indeg为0的节点)
            for (int x : ring) {
                rdfs(rdfs, x, ring.size()); // 环上节点能到达的节点数为ring.size()，树枝节点则视树枝长度要多一些
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2876 solu;
    auto a = solu.countVisitedNodes(*new vector<int>{1,2,0,0});

    auto b = solu.countVisitedNodes_implementation2(*new vector<int>{3,6,1,0,5,7,4,3});
    return 0;
}