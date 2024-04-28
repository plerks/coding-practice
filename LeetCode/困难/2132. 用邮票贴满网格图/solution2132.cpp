/*
url: https://leetcode.cn/problems/lexicographically-smallest-palindrome/description/
LeetCode参考: https://leetcode.cn/problems/stamping-the-grid/solutions/1199673/er-wei-qian-zhui-he-er-wei-chai-fen-by-n-wlzw/
              https://leetcode.cn/problems/stamping-the-grid/solutions/2562069/yong-you-piao-tie-man-wang-ge-tu-by-leet-kiaq/
相关: LeetCode303. 区域和检索 - 数组不可变, LeetCode304. 二维区域和检索 - 矩阵不可变
标签: 二维前缀和, 差分数组
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2132 {
public:
    /* 头一次遇到二维前缀和和差分数组的问题。
    由于只需返回是否能放满，尽量放邮票进去，当尝试以某一个位置为左上角时，首先需要解决的问题是，
    以这个位置为左上角的块是否有被占据的点，这可以通过二维前缀和然后范围求和实现，只要和大于1说明有被占据的块。
    第二个问题是，若可以放下，此时按理说应该标记这一块的点为可放，但是实际不需要这么做。
    对于以(i, j)为左上角，则[i, i + w - 1] × [j, j + h - 1]的范围内的点都能被填充一次。但是不需要直接遍历让这部分的填充计数都加1。
    用一个diff数组记录差值，若(i, j)位置可以放一张邮票则只需让diff[i][j]加1(只记录差分)。现在由差分数组算前缀和数组。
    参考题解，若只把(i, j)记一个1，则算前缀和之后整个[i, INF) × [j, INF)都会+1，实际我们只想让[i, i + w - 1] × [j, j + h - 1]的范围内
    计数+1，因此还需在(i, y)和(x, j)记一个-1，(x, y)记一个+1。这样再算前缀和，就能使差分的1刚好只被积累进[i, i + w - 1] × [j, j + h - 1]
    的范围内，从而算出了每个点的被填充次数。
    */
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> sum(m + 2, vector<int>(n + 2));
        // 求前缀和以判定以(i, j)为左上角的那一块是否有被占据
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
        vector<vector<int>> diff(m + 2, vector<int>(n + 2));
        // 枚举左上角
        for (int i = 1; i + stampHeight - 1 <= m; i++) {
            for (int j = 1; j + stampWidth - 1 <= n; j++) {
                // 左上角为(i, j)，右下角为(x, y)
                int x = i + stampHeight - 1;
                int y = j + stampWidth - 1;
                if (sum[x][y] - sum[i - 1][y] - sum[x][j - 1] + sum[i - 1][j - 1] == 0) {
                    // 关键技巧
                    diff[i][j]++;
                    diff[i][y + 1]--;
                    diff[x + 1][j]--; // 这里x + 1可能为m + 1，所以sum和diff必须定义为m + 2行
                    diff[x + 1][y + 1]++;
                }
            }
        }
        // 用差分数组diff原地计算出前缀和数组(计数每个点被填充的次数)
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                diff[i][j] = diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1] + diff[i][j];
                // grid[i - 1][j - 1] == 1的位置是被占据的位置，一定会有前缀和为0，但是不该返回false
                if (diff[i][j] == 0 && grid[i - 1][j - 1] == 0) { // 非被占据的位置无法被填充
                    return false;
                }
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution2132 solu;
    vector<vector<int>> grid = {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};
    cout << solu.possibleToStamp(grid, 4, 3) << endl;
    vector<vector<int>> grid2 = {{0},{0},{0},{0},{0},{0}};
    cout << solu.possibleToStamp(grid2, 6, 1) << endl;
    return 0;
}