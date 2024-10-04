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
    LeetCode1928能那样剪枝是因为计算cost时权在节点上，当x的邻居i,j,k依次出优先队列想要松弛x节点时，加的都是passingFees[x]，一定有
    cost(i) + passingFees[x] <= cost(j) + passingFees[x] <= cost(k) + passingFees[x]，
    (以k为例)所以只需要看到k的用时比最短用时长，则可知道当前路径0 ~ k -> x相比前面的某条路径属于cost大用时也高，则这条路径直接剪掉。

    但是这题计算cost时权在边上，i,j,k的cost和station可能分别是[1, 2] [3, 4] [6, 3]，然后其松弛x时会加上**各自**的边权w1,w2,w3，
    例如变成[101, 3] [4, 5] [9, 4]，找到的到x的路径的cost不是单增的，当前路径站数大不一定cost大，不能只看有站数更小的就剪，
    会导致把[9, 4]这条可能是最优解的路径剪掉。

    同样都是"若判断存在cost更小且station更少的到x的路则剪掉当前这条路"的剪枝策略，但是这在LeetCode1928中好实现，这题则不好实现。

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
