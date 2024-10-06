/*
url: https://leetcode.cn/problems/construct-2d-grid-matching-graph-layout/
参考: https://www.bilibili.com/video/BV15y1iYUE2h/
      https://leetcode.cn/problems/construct-2d-grid-matching-graph-layout/solutions/2940537/fen-lei-tao-lun-zhu-xing-gou-zao-by-endl-v3x0/
标签: LeetCode第418场周赛, 构造
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3311 {
public:
    /* 参考灵茶山艾府题解，周赛时能想到要把节点分度为2，3，4来考虑，但是没想清楚构造顺序，从左上角开始，我想的是
    其两个邻居一定是能确定，这样就会往bfs想，但是不行，接下来的bfs怎么做就不好确定了，而且这样想也不知道行列数是多少。
    */
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        vector<int> degrees(n);
        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
            degrees[e[0]]++;
            degrees[e[1]]++;
        }
        /* 从左上角开始，跟着度为3的节点走，直到度为2的节点，这样就是另外一个边界。
        但是有两种特例，一种情况是结果只有一行(或者一列)，这通过有度为1的节点来判断
        一种情况是结果只有2行(或者2列)，这通过没有度为4的节点来判断。这种情况下，例如结果是3行2列，
        可能会走出 0 - 2 - 3 - 5这种路径，所以这两种情况要特判。
        确定了第一行后，后面的行可由上一行构造出来。
        */
        int deg1Cnt = 0; // 度为1的节点个数
        int deg4Cnt = 0;
        int node = -1; // 起点
        for (int i = 0; i < n; i++) {
            int d = degrees[i];
            if (d == 1) {
                deg1Cnt++;
                node = i;
                break;
            }
            if (d == 4) deg4Cnt++;
            if (d == 2) node = i;
        }
        vector<int> used(n); // 也可以用一个pre变量防止回过去访问
        vector<int> firstRow;
        if (deg1Cnt > 0) {
            // 把node处理成第一行，不要一直往右构造，会麻烦很多
            firstRow = {node};
            used[node] = true;
        }
        else if (deg4Cnt == 0) {
            firstRow = {node};
            used[node] = true;
            for (int next : graph[node]) {
                if (degrees[next] == 2) {
                    firstRow.push_back(next);
                    used[next] = true;
                    break;
                }
            }
        }
        else {
            firstRow.push_back(node);
            used[node] = true;
            int next = -1;

            // 找下一个没用过的度为3的节点
            auto calc_next = [&](int node) {
                for (auto &neighbor : graph[node]) {
                    if (!used[neighbor] && degrees[neighbor] == 3) {
                        return neighbor;
                    }
                }
                return -1;
            };

            while (true) {
                next = calc_next(node);
                if (next == -1) {
                    for (auto &neighbor : graph[node]) {
                        if (!used[neighbor] && degrees[neighbor] == 2) {
                            firstRow.push_back(neighbor);
                            used[neighbor] = true;
                            break;
                        }
                    }
                    break;
                }
                else {
                    firstRow.push_back(next);
                    used[next] = true;
                    node = next;
                }
            }
        }
        // 由第一行计算下面的行
        int col = firstRow.size(); // 列数
        int row = n / col; // 行数
        vector<vector<int>> ans(n / firstRow.size(), vector<int>(firstRow.size(), -1));
        ans[0] = std::move(firstRow);
        for (int i = 0; i < row - 1; i++) {
            for (int j = 0; j < col; j++) {
                // [i, j]只有一个邻居未用
                for (auto &neighbor : graph[ans[i][j]]) {
                    if (!used[neighbor]) {
                        ans[i + 1][j] = neighbor;
                        used[neighbor] = true;
                    }
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3311 solu;
    vector<vector<int>> edges = {{0,1},{0,4},{0,5},{1,7},{2,3},{2,4},{2,5},{3,6},{4,6},{4,7},{6,8},{7,8}};
    // auto a = solu.constructGridLayout(9, edges);

    vector<vector<int>> edges2 = {{0,1},{1,3},{2,3},{2,4}};
    // auto b = solu.constructGridLayout(5, edges2);

    vector<vector<int>> edges3 = {{0,1},{0,2},{1,3},{2,3}};
    // auto c = solu.constructGridLayout(4, edges3);

    vector<vector<int>> edges4 = {{8, 9}, {2, 7}, {0, 4}, {8, 11}, {3, 8}, {5, 11}, {9, 10}, {1, 6}, {7, 11}, {4, 9}, {3, 6}, {0, 10}, {3, 10}, {2, 4}, {1, 8}, {1, 5}, {7, 9}};
    auto d = solu.constructGridLayout(12, edges4);
    return 0;
}
