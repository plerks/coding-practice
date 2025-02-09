/*
url: https://leetcode.cn/problems/sort-the-matrix-diagonally/
相关: LeetCode3446. 按对角线进行矩阵排序
标签: 对角线遍历
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1329 {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        for (int k = 1; k <= m + n - 1; k++) {
            int min_j = max(n - k, 0);
            int max_j = min(m + n - k - 1, n - 1);
            for (int j = min_j; j <= max_j; j++) {
                int i = k + j - n;
                int t_i = i;
                int t_j = j;
                while (t_i - 1 >= 0 && t_j - 1 >= 0 && mat[t_i - 1][t_j - 1] > mat[t_i][t_j]) {
                    swap(mat[t_i - 1][t_j - 1], mat[t_i][t_j]);
                    t_i--;
                    t_j--;
                }
            }
        }
        return mat;
    }
};

int main(int argc, char const *argv[]) {
    Solution1329 solu;
    auto a = solu.diagonalSort(*new vector<vector<int>>{{3,3,1,1},{2,2,1,2},{1,1,1,2}});
    return 0;
}