/*
url: https://leetcode.cn/problems/count-square-submatrices-with-all-ones/
相关: LeetCode1504. 统计全 1 子矩形, LeetCode221. 最大正方形
标签: 【算法题单】单调栈
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1277 {
public:
    // 可以用LeetCode1504的解法，不过由于限定为正方形，用LeetCode221的dp解法更简单一些
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> f(m + 1, vector<int>(n + 1));

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    f[i + 1][j + 1] = 1 + min({f[i - 1 + 1][j + 1], f[i + 1][j - 1 + 1], f[i - 1 + 1][j - 1 + 1]});
                    ans += f[i + 1][j + 1];
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1277 solu;
    cout << solu.countSquares(*new vector<vector<int>>{{0,1,1,1},{1,1,1,1},{0,1,1,1}}) << endl;
    return 0;
}