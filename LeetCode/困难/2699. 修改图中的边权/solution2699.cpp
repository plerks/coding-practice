/*
url: https://leetcode.cn/problems/modify-graph-edge-weights/
参考: https://leetcode.cn/problems/modify-graph-edge-weights/solutions/2278296/xiang-xi-fen-xi-liang-ci-dijkstrachou-mi-gv1m/
      https://www.bilibili.com/video/BV1Qm4y1t7cx/
      https://leetcode.cn/problems/modify-graph-edge-weights/solutions/2300101/xiu-gai-tu-zhong-de-bian-quan-by-leetcod-66bg/
标签: 【题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2699 {
public:
    /* 参考灵茶题解，两次Dijkstra。
    首先分析无解的情况，把所有-1的特殊边全变成1，能得到 s 到 d 的最短的距离，把所有-1边全变成2e9，能得到最长的距离，
    如果最短距离 > target / 最长距离 < target ，则无解。

    然后，所有-1的特殊边边权最小都是 1，考虑在Dijkstra的过程中去增大这些特殊边，比如 s 1 a 2 b 3 d，如果要把最短路径变为 target = 7，
    可以把 s - a 变成 2。但是，增大边权以达到距离为 target 之后却不一定是最短距离了，最短距离可能更小，因为此时可能走别的路径。
    但是可以再改，只要按照Dijkstra的顺序来，就会在过程中发现更小的路径，那就接着算diff改边权。

    所以要两次Dijkstra，第一次算距离，用于第二次算该把边权变大多少。
    */
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        vector<vector<pair<int, int>>> g(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            g[u].push_back({v, i}); // 记录边的id，方便修改
            g[v].push_back({u, i});
        }

        vector<vector<int>> dis(2, vector<int>(n, 0x3f3f3f3f)); // 两轮Dijkstra
        dis[0][source] = dis[1][source] = 0;
        dijkstra0(g, source, destination, target, dis[0], edges);
        if (dis[0][destination] > target) return {};

        dijkstra1(g, source, destination, target, dis, edges);
        if (dis[1][destination] < target) return {};

        for (auto& e : edges) if (e[2] == -1) e[2] = 1; // 剩余没修改的边全改成1
        return edges;
    }

    // 第一轮Dijkstra，算 s 到其它节点的最短路径
    void dijkstra0(vector<vector<pair<int, int>>>& g, int s, int d, int target, vector<int>& dis, vector<vector<int>>& edges) {
        int n = g.size();
        // 本题为稠密图，用朴素实现的Dijkstra效率更高
        vector<bool> vis(n);
        while (true) {
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!vis[i] && (u < 0 || dis[i] < dis[u])) {
                    u = i;
                }
            }
            // u 为选出的此轮最小
            // 一到 d 就可以返回了，第二次也不会用到其余部分的路径，当前到d的最短路径要么有特殊边，要么无特殊边
            // 若无特殊边，且距离 < target，则无解；若距离 > target，则也无解，因为此时把特殊边都变1了，已经是最小了
            // 若有特殊边，则距离 < target，第二轮会操作；若距离 > target，也是无解的
            if (u == d) return;
            vis[u] = true;
            for (auto [v, eid] : g[u]) {
                int w = edges[eid][2];
                if (w == -1) w = 1; // 还没改edge，但是算距离时权值为1
                dis[v] = min(dis[v], dis[u] + w);
            }
        }
    }

    // 第二轮Dijkstra，去修改特殊边的边权
    void dijkstra1(vector<vector<pair<int, int>>>& g, int s, int d, int target, vector<vector<int>>& dis, vector<vector<int>>& edges) {
        int n = g.size();
        vector<bool> vis(n);
        while (true) {
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!vis[i] && (u < 0 || dis[1][i] < dis[1][u])) {
                    u = i;
                }
            }
            if (u == d) return;
            vis[u] = true;
            for (auto [v, eid] : g[u]) {
                int w = edges[eid][2]; // -1代表特殊边
                if (w == -1) w = 1;
                /* s ~ u - v ~ d 这条路径，s ~ u 的最短距离为 dis1[u]，
                v ~ d 的最短距离为 dis0[d] - dis0[v]（实际如果v不在最短路径上，距离不是这二者相减，而是更大，但是不影响最终正确性，也不用单独去求一遍每个节点到d的距离）
                dis1[u] + w + dis0[d] - dis0[v] = target，
                则 w 要为 target - dis0[d] + dis0[v] - dis1[u]
                */
                if (edges[eid][2] == -1) { // 可以改权值的特殊边。只有第一次能改，这时候是到u的最短路径，后面再算新的new_w只会更小，导致前面调整的等于target的最短路径变成<target
                    int new_w = target - dis[0][d] + dis[0][v] - dis[1][u];
                    if (new_w > 1) edges[eid][2] = w = new_w;
                }
                dis[1][v] = min(dis[1][v], dis[1][u] + w);
            }
        }
    }

    /* 官方题解还有个二分的解法，时间复杂度不如两次Dijkstra，但是这题也是可以二分做的，
    具体来说，考虑以下方案序列，二分去搜索方案下标，“每把一条特殊边的权+1，source到destination的最短距离要么不变要么+1(取决于最短路径有没有选这条边)”。
    如果有k条特殊边，最开始都是1，每条特殊边最多增加到target，一共有 k * (target - 1) + 1 种边权情况:
    [1, 1, 1, ... , 1]
    [2, 1, 1, ... , 1]
    [3, 1, 1, ... , 1]
    ...
    [t, 1, 1, ... , 1]
    [t, 2, 1, ... , 1]
    [t, 3, 1, ... , 1]
    ...
    [t, t, t, ... , t]
    也就是每次选第一个还能增加的边权 +1，
    这些情况，最短路径长度会单增(每次要么不变，要么 +1)，于是可以通过二分找到 最短距离 == target 的方案。

    这个方法最有意思的点在于，为什么可以这样顺序对边 +1，而不需要考虑 +1 的排列？
    见<https://leetcode.cn/problems/modify-graph-edge-weights/solutions/2300101/xiu-gai-tu-zhong-de-bian-quan-by-leetcod-66bg/comments/2086692/>，
    这样枚举，最短路径的长度是单增的，由于介值定理，一定能在中间找到 == target 的方案，因此我们不需要全面枚举所有排列那么多，
    只需要按这种方式考虑就能找到答案
    */
};

int main(int argc, char const *argv[]) {
    Solution2699 solu;
    auto a = solu.modifiedGraphEdges(5, *new vector<vector<int>>{{4,1,-1},{2,0,-1},{0,3,-1},{4,3,-1}}, 0, 1, 5);
    return 0;
}