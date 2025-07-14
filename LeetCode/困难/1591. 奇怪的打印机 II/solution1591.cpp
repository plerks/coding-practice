/*
url: https://leetcode.cn/problems/strange-printer-ii/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1591 {
public:
    bool isPrintable(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 找每个数字区域的矩形
        /*
        注意，不能用 struct Info {
            int x;
            int y; // (x, y)为左上角
            int w;
            int h;
        };
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int num = grid[i][j];
                if (!map.count(num)) {
                    map[num] = Info {i, j, 1, 1};
                }
                else {
                    map[num].x = min(map[num].x, i);
                    map[num].y = min(map[num].y, j); // 先更新左上角
                    map[num].h = max(map[num].h, i - map[num].x + 1); // 再更新宽高
                    map[num].w = max(map[num].w, j - map[num].y + 1);
                }
            }
        }
        来算每个数字的矩形区域，例如 (0, 3) (1, 0) 计算出来的宽不对
        */
        struct Info {
            // (x, y)左上角 (p, q)右下角
            int x;
            int y;
            int p;
            int q;
        };
        unordered_map<int, Info> map; // (数字，矩形信息)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int num = grid[i][j];
                if (!map.count(num)) {
                    map[num] = Info {i, j, i, j};
                }
                else {
                    map[num].x = min(map[num].x, i);
                    map[num].y = min(map[num].y, j);
                    map[num].p = max(map[num].p, i);
                    map[num].q = max(map[num].q, j);
                }
            }
        }

        // 1 <= targetGrid[row][col] <= 60
        vector<vector<int>> g(61); // 这里内层用vector虽然可能有重复的 A -> B，A -> B，但是没问题
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int num = grid[i][j];
                for (auto& [t, info] : map) {
                    if (num == t) continue;
                    auto [x, y, p, q] = info;
                    if (x <= i && i <= p && y <= j && j <= q) { // (i, j)这个点被包含，有拓扑序关系
                        g[t].push_back(num);
                    }
                }
            }
        }
        
        // 检查是否有拓扑序
        // A -> B 的边表示要先涂A，再涂B
        return check_topo_order(g);
    }

    // 检查整个图是否有拓扑序
    bool check_topo_order(vector<vector<int>>& g) {
        int n = g.size();
        vector<int> indeg(n);
        for (int x = 0; x < n; x++) {
            for (int y : g[x]) {
                indeg[y]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        int cnt = 0; // 能拓扑序的元素个数
        while (!q.empty()) {
            int x = q.front(); q.pop();
            cnt++;
            for (int y : g[x]) {
                indeg[y]--;
                if (indeg[y] == 0) q.push(y);
            }
        }
        return cnt == n;
    }
};

int main(int argc, char const *argv[]) {
    Solution1591 solu;
    // cout << solu.isPrintable(*new vector<vector<int>>{{1,1,1,1},{1,1,3,3},{1,1,3,4},{5,5,1,4}}) << endl;
    // cout << solu.isPrintable(*new vector<vector<int>>{{1,1,1},{3,1,3}}) << endl;
    cout << solu.isPrintable(*new vector<vector<int>>{{6,2,2,5},{2,2,2,5},{2,2,2,5},{4,3,3,4}}) << endl;
    return 0;
}