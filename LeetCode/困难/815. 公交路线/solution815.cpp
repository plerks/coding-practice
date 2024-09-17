/*
url: https://leetcode.cn/problems/bus-routes/description/?envType=daily-question&envId=2024-09-17
LeetCode参考: https://leetcode.cn/problems/bus-routes/solutions/2916806/tu-jie-bfspythonjavacgojsrust-by-endless-t7oc/
相关: LeetCode1162. 地图分析
标签: 最短路径, bfs, Dijkstra算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution815 {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        /* 从source开始，同一条线路上，距离为0，和LeetCode1162. 地图分析有点像，把同一条路线上的点合成一个节点。
        然后跑Dijkstra算法，这题图特殊，可以只用bfs。为了知道当前节点的邻居，需要知道哪些公交车会经过当前节点，然后
        再去松弛这些公交车的路线上的节点
        */
        unordered_map<int, int> dis;
        dis[source] = 0;
        unordered_map<int, vector<int>> by_pass; // 记录每个车站有哪些公交车经过了它
        for (int i = 0; i < routes.size(); i++) {
            for (int r : routes[i]) {
                by_pass[r].push_back(i);
            }
        }
        queue<int> q;
        unordered_set<int> visited;
        q.push(source);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visited.insert(node);
            int d = dis[node];
            // 现在在node位置，node作为一个新的起点，其路线上的点距源点的距离为node到源点距离 + 1
            for (int i : by_pass[node]) {
                for (int r : routes[i]) {
                    if (!visited.count(r)) {
                        dis[r] = d + 1;
                        visited.insert(r); // r到源点的距离已经确定，访问已经完成
                        q.push(r);
                    }
                }
                routes[i].clear(); // 把这条路线清掉，不再遍历
            }
        }
        return dis.count(target) ? dis[target] : -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution815 solu;
    vector<vector<int>> routes = {{1,2,7},{3,6,7}};
    cout << solu.numBusesToDestination(routes, 1, 6) << endl;
    return 0;
}
