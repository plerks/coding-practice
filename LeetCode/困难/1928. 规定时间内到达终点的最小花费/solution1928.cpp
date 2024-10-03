/*
url: https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/description/?envType=daily-question&envId=2024-10-03
参考: https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/solutions/869919/gui-ding-shi-jian-nei-dao-da-zhong-dian-n3ews/
      https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/solutions/2937601/chao-yue-98de-dijkstrayou-hua-si-lu-by-c-fipw/
相关: LeetCode787. K 站中转内最便宜的航班
标签: 图, Dijkstra算法变式, 带限制的Dijkstra, 权在节点上的Dijkstra, 两次Dijkstra, 动态规划例题
*/

#include <bits/stdc++.h>

using namespace std;

// 这题的开销在节点上，而不在边上，比较特殊
// 这题相比普通的用优先队列实现的Dijkstra，优先队列中需要用其松弛邻居的元素要多些

class Solution1928 {
public:
    /* 官方题解的做法。用f[t][i]表示恰好用t分钟到达i节点的最小费用，则
    f[t][i] = min{f[t - cost(j, i)][j] + passingFees[i]}，j枚举i的所有邻居
    */
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<int>> f(maxTime + 1, vector<int>(n, 0x3f3f3f3f));
        f[0][0] = passingFees[0];
        for (int t = 1; t <= maxTime; t++) {
            for (auto & e : edges) {
                int i = e[0], j = e[1], timeCost = e[2];
                if (t - timeCost >= 0) {
                    f[t][i] = min(f[t][i], f[t - timeCost][j] + passingFees[i]);
                    f[t][j] = min(f[t][j], f[t - timeCost][i] + passingFees[j]);
                }
            }
        }

        int ans = 0x3f3f3f3f;
        for (int t = 1; t <= maxTime; t++) {
            ans = min(ans, f[t][n - 1]);
        }
        return ans == 0x3f3f3f3f ? -1 : ans;
    }

    // 参考<https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/solutions/2937601/chao-yue-98de-dijkstrayou-hua-si-lu-by-c-fipw/>
    // 很高效的剪枝
    int minCost_implementation2(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>> graph(n);
        for (auto e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pre_q;
        vector<int> minTime(n, 0x3f3f3f3f); // 先用一遍普通的Dijkstra求每个节点到n - 1所需的最小时间
        minTime[n - 1] = 0;
        pre_q.emplace(n - 1, 0);
        while (!pre_q.empty()) {
            auto [node, time] = pre_q.top();
            pre_q.pop();
            if (time > minTime[node]) continue;
            for (auto p : graph[node]) {
                if (minTime[node] + p.second < minTime[p.first]) {
                    minTime[p.first] = minTime[node] + p.second;
                    pre_q.emplace(p.first, minTime[p.first]);
                }
            }
        }
        // [费用, 节点编号, 用时]
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
        q.emplace(passingFees[0], 0, 0);
        vector<int> minLegalTime(n, INT_MAX); // minLegalTime[i]表示合法路径到达i的最小用时
        while (!q.empty()) {
            auto [cost, id, time] = q.top();
            q.pop();
            if (id == n - 1) return cost;
            for (auto p : graph[id]) {
                int nId = p.first;
                int nTime = time + p.second;
                int nCost = cost + passingFees[nId];
                // 利用之前求的信息，若无法在maxTime前到达n - 1，不合法
                // 这题也可以不剪枝nTime + minTime[nId] > maxTime，然后把上面改成if (id == n - 1 && time <= maxTime) return cost;，也能过，148ms
                if (nTime + minTime[nId] > maxTime) continue;
                // 至此，路径一定是合法的

                /*
                这题计算费用时，权在节点上，假设nId先后被i和j当作邻居想要更新，则两次的cost是cost[i] + passingFees[nId]
                和cost[j] + passingFees[nId]，由于是优先队列，cost[i]小，所以到nId的最短距离能确定为cost[i] + passingFees[nId]，
                也就是说第一次松弛nId时会是一个最小的cost。但是这个到nId的cost最小的路不一定是最终的解，因为可能这条路用时多，导致后续不得
                不走一些用时少但是cost很大的路，导致整体0到n - 1的cost大。
                （权在边上的话是cost[i] + w1和cost[j] + w2，不能确定哪次更新是最小值） */

                /* 如果nTime > minLegalTime[nId]，说明之前被另外一条路径更新过，由前所述，那条路径cost更小，则若当前这条
                路径用时还更长，则走当前这条路到nId一定不如走前面那条路到nId，直接剪枝丢弃 */
                if (nTime >= minLegalTime[nId]) continue; // 这里必须写>=，写>直接超时，写>=用时77ms
                /* 这里没有传统优先队列Dijkstra的
                if (distance + w < dis[next]) {
                    dis[next] = distance + w;
                    q.offer(new int[]{next, dis[next]});
                }
                会不会出现 0 -> 1 -> 2，然后2又把1入队导致尝试了路径 0 -> 1 -> 2 -> 1？
                否，上面剪枝的作用就体现出来了。
                */

                minLegalTime[nId] = nTime;
                q.emplace(nCost, nId, nTime);
            }
        }
        return -1;
    }

    /* 参考<https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/solutions/1980876/c-dai-shi-jian-xian-zhi-de-dijkstra-by-t-ms56/>
    并进行了修改的解法，这样写能过LeetCode787. K 站中转内最便宜的航班，但是这题会超时，79 / 93 个通过的测试用例，剪枝没剪够 */
    int minCost_time_limit_exceeded(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }
        // [费用, 节点编号, 用时]
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;

        /* minCost[i]和times[i]记录了从0到某节点的最优路径，最优路径按cost, time的优先级进行比较，
        若cost小，则更优，cost相同，则time小的更优 */
        vector<int> minCost(n, 0x3f3f3f3f);
        vector<int> times(n, 0x3f3f3f3f);
        q.push({passingFees[0], 0, 0});
        minCost[0] = passingFees[0];
        times[0] = 0;
        while (!q.empty()) {
            auto [cost, id, time] = q.top();
            q.pop();
            /* 这里不能像传统Dijkstra算法一样 if (cost > minCost[id]) continue;
            因为这里有maxTime的限制，最短费用的路径可能time是超的，次优路径也需要考虑
            */
            if (id == n - 1) return cost;
            for (auto p : graph[id]) {
                // 邻居
                int nextId = p.first;
                int nextCost = cost + passingFees[nextId];
                int nextTime = time + p.second;
                if (nextTime > maxTime) continue;

                /* 队列中元素保存了某条道路，有其cost和time。用时超过maxTime的被丢弃，对某个节点，
                我们已经记录好了其最优路径的cost和time，用这个最优路径来剪枝。
                最优路径按cost, time的优先级进行比较，若cost小，则更优，cost相同，则time小的更优
                
                能执行到这里，说明当前的这条路径是合法的。

                到达nextId节点的路径，由于有maxTime的限制，除非cost更大且time更大，否则都需要考虑，
                原因在于，cost最小的路径可能time较大，若time最后不超过maxTime，则可以取，否则路径不合法，
                这时就需要考虑一条cost更大但time更小的路径了（cost更大且time更大的不用考虑）。

                然后再用这条路径更新最优路径。

                总之，按cost, time的优先级定义了一条最优路径，如果cost, time都比最优路径差，则可以剪掉
                */
                if (!(nextCost >= minCost[nextId] && nextTime >= times[nextId])) {
                    q.emplace(nextCost, nextId, nextTime);
                }
                if (nextCost < minCost[nextId]) {
                    minCost[nextId] = nextCost;
                    times[nextId] = nextTime;
                }
                else if (nextCost == minCost[nextId] && nextTime < times[nextId]) {
                    times[nextId] = nextTime;
                }
            }
        }
        return -1;
    }

    /* <https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/solutions/1980876/c-dai-shi-jian-xian-zhi-de-dijkstra-by-t-ms56/>
    里的写法大致是以下这样。

    这样写的问题在于minCost[i]和minTime[i]不一定是同一条路径的值，假设3条到节点x的路径的cost和time分别是[1, 6]，[3, 4], [2, 5]，
    存在这样一种情况：使用[1, 6]会最终导致超maxTime，[3, 4]可行，[2, 5]是最优解。
    而以下这样写，前两种情况会把minCost[x]变成1，minTime[x]变成4，然后到了[2, 5]的时候，[2, 5]没有进队列，最终就是错的。
    也就是说，这样剪枝把坏的剪了，但是也把好的剪了。

    但是以下这样写能过这题，用例不够强，但是过不了LeetCode787. K 站中转内最便宜的航班，会WA
    */
    int minCost_wrong(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>> graph(n);
        for (auto e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }
        // [费用, 节点编号, 用时]
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
        vector<int> minCost(n, 0x3f3f3f3f); // 各节点到0的最小费用
        vector<int> minTime(n, 0x3f3f3f3f); // 各节点到0的最小用时
        q.push({passingFees[0], 0, 0});
        minCost[0] = passingFees[0];
        minTime[0] = 0;
        while (!q.empty()) {
            auto [cost, id, time] = q.top();
            q.pop();
            if (id == n - 1) return cost;
            for (auto p : graph[id]) {
                // 邻居
                int nextId = p.first;
                int nextCost = cost + passingFees[nextId];
                int nextTime = time + p.second;
                /* 这里不能像传统Dijkstra算法一样 if (cost > minCost[id]) continue;
                因为这里有maxTime的限制，最短费用的路径可能time是超的，次优路径也需要考虑
                */
                if (nextTime > maxTime) continue;
                if (nextCost < minCost[nextId]) {
                    q.push({nextCost, nextId, nextTime});
                    minCost[nextId] = nextCost;
                    minTime[nextId] = min(minTime[nextId], nextTime);
                }
                else if (nextTime < minTime[nextId]) {
                    q.push({nextCost, nextId, nextTime});
                    minTime[nextId] = nextTime;
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1928 solu;
    int maxTime = 30;
    vector<vector<int>> edges = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> passingFees = {5,1,2,20,20,3};
    cout << solu.minCost(maxTime, edges, passingFees) << endl;

    int maxTime2 = 10;
    vector<vector<int>> edges2 = {{0,1,2},{0,2,1},{2,3,2},{1,3,3},{3,4,2},{3,5,3},{4,6,3},{5,6,4}};
    vector<int> passingFees2 = {1,3,6,1,98,18,1};
    cout << solu.minCost_implementation2(maxTime2, edges2, passingFees2) << endl;
    return 0;
}
