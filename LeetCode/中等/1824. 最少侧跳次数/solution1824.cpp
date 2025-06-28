/*
url: https://leetcode.cn/problems/minimum-sideway-jumps/
相关: LeetCode2290. 到达角落需要移除障碍物的最小数目, LeetCode1368. 使网格图至少有一条有效路径的最小代价
标签: 【算法题单】网格图, 0-1 Dijkstra
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1824 {
public:
    // 时间复杂度O(3n)
    int minSideJumps(vector<int>& obstacles) {
        int m = 3;
        int n = obstacles.size(); // 相当于个 3 * n 的网格图
        vector<vector<int>> dis(m + 1, vector<int>(n, 0x3f3f3f3f));
        deque<tuple<int, int, int>> dq; // (cost, x, y)
        dq.push_back({0, 1, 0}); // 初始在(1, 0)
        dis[1][0] = 0;
        while (!dq.empty()) {
            auto [c, x, y] = dq.front(); dq.pop_front();
            if (c > dis[x][y]) continue;
            if (y == n - 1) return min({dis[0][y], dis[1][y], dis[2][y]});
            // 现在在(x, y)，可以往上下走，也可以往右走
            for (int xx = 0; xx < 3; xx++) { // 上下走到(xx, y)
                if (xx == x) continue;
                if (obstacles[y] - 1 != xx) { // 换跑道，无障碍
                    if (c + 1 < dis[xx][y]) {
                        dq.push_back({c + 1, xx, y});
                        dis[xx][y] = c + 1;
                    }
                }
            }
            // 往右走到(x, yy)
            int yy = y + 1; // yy一定不会越界，否则就是 y == n - 1，早返回了
            if (obstacles[yy] - 1 != x) {
                if (c < dis[x][yy]) {
                    dq.push_front({c, x, yy});
                    dis[x][yy] = c;
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1824 solu;
    cout << solu.minSideJumps(*new vector<int>{0,1,2,3,0}) << endl;
    return 0;
}