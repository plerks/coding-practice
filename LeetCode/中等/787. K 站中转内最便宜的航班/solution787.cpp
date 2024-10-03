/*
url: https://leetcode.cn/problems/cheapest-flights-within-k-stops/description/
参考: https://leetcode.cn/problems/cheapest-flights-within-k-stops/solutions/954402/k-zhan-zhong-zhuan-nei-zui-bian-yi-de-ha-abzi/
相关: LeetCode1928. 规定时间内到达终点的最小花费
标签: 图, Bellman-Ford算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution787 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : flights) {
            graph[e[0]].emplace_back(e[1], e[2]);
        }
        // [开销, 节点编号, 经过站数], 这里站数把开头结尾都算上
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
        vector<int> minCost(n, INT_MAX);
        vector<int> stations(n, INT_MAX);
        /* 用这样一条最优路径来帮忙剪枝：
        最优路径按cost, station的优先级进行比较，若cost小，则更优，cost相同，则station小的更优。
        minCost[x], stations[i]记录到i的最优路径的cost和station
        */
        minCost[src] = 0;
        stations[src] = 0;
        q.push({0, src, 1});

        while (!q.empty()) {
            auto [cost, id, station] = q.top();
            q.pop();
            if (id == dst) return cost;
            /* 这里不能像传统Dijkstra算法一样 if (cost > minCost[id]) continue;
            因为这里有站数k的限制，最短费用的路径可能time是超的，次优路径也需要考虑
            */
            for (auto p : graph[id]) { // 邻居
                int nid = p.first;
                int ncost = cost + p.second;
                int nstation = station + 1;
                if (nstation > k + 2) continue;
                if (!(ncost >= minCost[nid] && nstation >= stations[nid])) {
                    q.emplace(ncost, nid, nstation);
                }
                if (ncost < minCost[nid]) {
                    minCost[nid] = ncost;
                    stations[nid] = nstation;
                }
                else if (ncost == minCost[nid] && nstation < stations[nid]) {
                    stations[nid] = nstation;
                }
            }

        }
        return -1;
    }

    /* 这题好像没办法像 LeetCode1928. 规定时间内到达终点的最小花费 minCost_implementation2() 那样剪枝，
    多次松弛到某一个节点x时，能丢弃的路径是，存在其它路径长度也短，经过站数也少的路径的情况，这题权在边上，不好判断这个。
    正解应该是像官方题解用Bellman-Ford */
    int findCheapestPrice_implementation2(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // 中间节点能有k个，则最多k + 1条边
        vector<vector<int>> f(k + 2, vector<int>(n, 0x3f3f3f3f)); // f[i]表示中间有i条边时的单源最短路径
        // d(u) = d(v) + w(u, v)，最开始0条变，然后每次加边进来松弛
        f[0][src] = 0;
        for (int i = 1; i <= k + 1; i++) {
            for (auto &e : flights) {
                int u = e[0], v = e[1], w = e[2];
                f[i][v] = min(f[i][v], f[i - 1][u] + w);
            }
        }
        int ans = INT_MAX;
        for (int i = 1; i <= k + 1; i++) {
            ans = min(ans, f[i][dst]);
        }
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution787 solu;
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    // cout << solu.findCheapestPrice(4, flights, 0, 3, 1) << endl;

    vector<vector<int>> flights2 = {{0,3,3},{3,4,3},{4,1,3},{0,5,1},{5,1,100},{0,6,2},{6,1,100},{0,7,1},{7,8,1},{8,9,1},{9,1,1},{1,10,1},{10,2,1},{1,2,100}};
    cout << solu.findCheapestPrice(11, flights2, 0, 2, 4) << endl;
    return 0;
}
