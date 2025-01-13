/*
url: https://leetcode.cn/problems/minimize-the-maximum-edge-weight-of-graph/description/
参考: https://leetcode.cn/problems/minimize-the-maximum-edge-weight-of-graph/solutions/3045060/liang-chong-fang-fa-er-fen-da-an-dijkstr-eb7d/
      https://www.bilibili.com/video/BV1HKcue9ETm/
标签: LeetCode第432场周赛, Dijkstra算法变式, 典型问题/最短路径问题/Dijkstra算法为什么不能处理含负权边的图.md
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3419 {
public:
    /* 灵茶山艾府题解解法一
    所有其他节点都可以到达节点0这个条件，把边反一下，就变成更容易判断的，0可以到达所有其它节点，
    同时，每个节点至多有threshold条出去的边 变成 每个节点至多有threshold条进去的边。
    0可以到达其它所有节点可以用dfs来判断，而dfs过程中，如果一个点已经被访问，那么是不需要再次访问的，
    也就是说，只需要一条到这个点的边就可满足可达性。
    也就是说，若0到u可达，是不需要有两条边指向u的，一定可以削减到只留一条边。
    而threshold >= 1，所以只要满足0到其它节点的可达性，就一定满足threshold的要求，这个条件多余。

    上界越大越能找到相应的树边，二分
    */
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        vector<vector<pair<int, int>>> g(n);
        int mx = 0; // 最大边权
        for (auto& e : edges) {
            // 建反图
            g[e[1]].push_back({e[0], e[2]});
            mx = max(mx, e[2]);
        }
        vector<int> vis(n);

        // 检查能否通过<=upper的权的边访问到所有节点
        auto check = [&](int upper) {
            int cnt = 0; // 访问个数
            auto dfs = [&](auto& dfs, int r) -> bool {
                if (vis[r] != upper) { // 一个小技巧，由于每次upper不同，用是否等于upper判断是否访问了，不需要每次重新初始化vis
                    cnt++;
                    vis[r] = upper;
                    for (auto& [next, w] : g[r]) {
                        if (w <= upper) dfs(dfs, next);
                    }
                }
                return cnt == n;
            };
            return dfs(dfs, 0);
        };

        // 二分搜索第一个是
        int left = 0, right = mx;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left == mx + 1 ? -1 : left;
    }

    /* 灵茶山艾府题解解法二
    用Dijkstra算法，但是不是求距离，而是求源点0到其它节点的路径中，路径最大边权的最小化。
    这里求最小化的路径最大边权(而非路径最小边权和)能用Dijkstra，可以看出与求最短路径有一定相似性。
    0到v的路径肯定是由0先到之前的节点u，再由u引到v的，且如果一个节点x的路径最大边权已经大于当前v的了，
    那么由x松弛v注定不会让v的最大边权变小。

    对于这题求路径最大边权的最小化，似乎即使图有负权边也是正确的，节点x和y，x的首次出队比y的首次出队早，即便y到x有负权边，
    max({edges_of_path_y}, y->x) >= max({edges_of_path_y}) >= max({edges_of_path_x})，所以y到x的负权边
    不会对x的min({路径最大边权})产生影响，y不会需要把x重新拉进队。(不会发生首次出队后重新入队，时间复杂度完全是正常的O(eloge))
    */
    int minMaxWeight_implementation2(int n, vector<vector<int>>& edges, int threshold) {
        vector<vector<pair<int, int>>> g(n);
        int mx = 0; // 最大边权
        for (auto& e : edges) {
            // 建反图
            g[e[1]].push_back({e[0], e[2]});
            mx = max(mx, e[2]);
        }
        vector<int> dis(n, INT_MAX);
        // [路径最大边权, 节点编号]
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dis[0] = 0;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();
            if (d > dis[node]) continue;
            for (auto [next, w] : g[node]) {
                // 从node松弛next给next的最大路径边权
                int new_d = max(d, w);
                if (new_d < dis[next]) {
                    dis[next] = new_d;
                    pq.push({new_d, next});
                }
            }
        }
        int ans = *max_element(dis.begin(), dis.end());
        return ans == INT_MAX ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3419 solu;
    cout << solu.minMaxWeight(5, *new vector<vector<int>>{{1,0,1},{2,0,2},{3,0,1},{4,3,1},{2,1,1}}, 2) << endl;
    cout << solu.minMaxWeight_implementation2(5, *new vector<vector<int>>{{1,0,1},{2,0,2},{3,0,1},{4,3,1},{2,1,1}}, 2) << endl;
    return 0;
}