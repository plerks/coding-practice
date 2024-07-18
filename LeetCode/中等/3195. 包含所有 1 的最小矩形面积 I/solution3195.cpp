/*
url: https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-i/
参考: https://www.bilibili.com/video/BV1MZ421M74P/
相关: LeetCode3197. 包含所有 1 的最小矩形面积 II
标签: LeetCode第403场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3195 {
public:
    // 我的解法，用4条线去围1
    int minimumArea(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int x1, y1, x2, y2;
        x1 = 0;
        y1 = 0;
        x2 = m - 1;
        y2 = n - 1;
        vector<int> rows(m, 0); // 每行有无1
        vector<int> cols(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    rows[i] = 1;
                    cols[j] = 1;
                }
            }
        }
        while (!rows[x1]) x1++;
        while (!rows[x2]) x2--;
        while (!cols[y1]) y1++;
        while (!cols[y2]) y2--;
        return (y2 - y1 + 1) * (x2 - x1 + 1);
    }

    // 灵茶山艾府题解解法，直接遍历即可，不用用map记录
    int minimumArea_implementation2(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int x1, y1, x2, y2;
        x1 = m - 1;
        x2 = 0;
        y1 = n - 1;
        y2 = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    x1 = min(x1, i);
                    x2 = max(x2, i);
                    y1 = min(y1, j);
                    y2 = max(y2, j);
                }
            }
        }
        return (y2 - y1 + 1) * (x2 - x1 + 1);
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
