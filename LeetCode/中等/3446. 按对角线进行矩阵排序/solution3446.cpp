/*
url: https://leetcode.cn/problems/sort-matrix-by-diagonals/
相关: LeetCode1329. 将矩阵按对角线排序
标签: LeetCode第436场周赛, 对角线遍历
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3446 {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            for (int k = 0; i + k < n; k++) {
                int tempI = i + k;
                int tempJ = k;
                while (tempJ - 1 >= 0 && grid[tempI - 1][tempJ - 1] < grid[tempI][tempJ]) {
                    swap(grid[tempI][tempJ], grid[tempI - 1][tempJ - 1]);
                    tempI--;
                    tempJ--;
                }
            }
        }
        for (int j = 1; j < n; j++) {
            for (int k = 0; j + k < n; k++) {
                int tempI = k;
                int tempJ = j + k;
                while (tempI - 1 >= 0 && grid[tempI - 1][tempJ - 1] > grid[tempI][tempJ]) {
                    swap(grid[tempI][tempJ], grid[tempI - 1][tempJ - 1]);
                    tempI--;
                    tempJ--;
                }
            }
        }
        return grid;
    }

    /* 灵茶题解中这里在写对角线遍历时有个模版化的写法，令 k = n - (j - i)，则从最右上的对角线到最左下的对角线，k的取值
    从 1 到 m+n-1，对某条k具体的线，i,j的范围怎么定？
    假设每条线上i都能取0 -> m-1，则 j = n+i-k 从 n-k 到 m+n-k-1，但是要考虑j越界，因此实际j的范围是
    min_j = max(n - k, 0)
    max_j = min(m + n - k - 1, n - 1)
    同时由 i = k + j - n可以求出i，这样 k, j 的两层循环即可完成对角线遍历
    */
};

int main(int argc, char const *argv[]) {
    Solution3446 solu;
    auto a = solu.sortMatrix(*new vector<vector<int>>{{1,7,3},{9,8,2},{4,5,6}});
    return 0;
}