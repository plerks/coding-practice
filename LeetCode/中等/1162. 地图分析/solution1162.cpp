/*
url: https://leetcode.cn/problems/as-far-from-land-as-possible/description/
参考: https://leetcode.cn/problems/as-far-from-land-as-possible/solutions/147423/di-tu-fen-xi-by-leetcode-solution/
相关: LeetCode815. 公交路线
标签: 最短路径, Dijkstra算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1162 {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        // 这题如果暴力的话要O(n^4)
        // 把所有陆地单元格当作一个整体的源点，用Dijkstra求海洋单元格到其距离，就求出了海洋单元格到陆地的最近距离
        // 如果把海洋单元格作为源，则能求出某个陆地单元格与最近海洋的距离，但是想知道的是某个海洋与最近陆地的距离
        auto comparator = [](vector<int> &v1, vector<int> &v2) { // 节点横坐标，纵坐标，距离
            return v1[2] > v2[2];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comparator)> pq(comparator);
        vector<vector<int>> dis(n, vector<int>(n, 0x3f3f3f3f));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    pq.push({i, j, 0});
                    dis[i][j] = 0;
                }
            }
        }
        vector<vector<int>> visited(n, vector<int>(n, false));
        int ans = -1;
        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();
            int x = p[0];
            int y = p[1];
            int d = p[2];
            if (visited.at(x).at(y)) continue;
            for (auto &direction : directions) {
                int xx = x + direction[0];
                int yy = y + direction[1];
                if (xx >= 0 && xx < n && yy >= 0 && yy < n) {
                    if (grid[xx][yy] == 1) continue; // 跳过陆地
                    if (d + 1 < dis[xx][yy]) {
                        dis[xx][yy] = d + 1;
                        ans = max(ans, dis[xx][yy]);
                        pq.push({xx, yy, dis[xx][yy]});
                    }
                }
            }
            visited[x][y] = true;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1162 solu;
    vector<vector<int>> grid = {{1,0,1},{0,0,0},{1,0,1}};
    cout << solu.maxDistance(grid) << endl;
    return 0;
}
