/*
url: https://leetcode.cn/problems/range-sum-query-2d-immutable/description/
参考: https://oi-wiki.org/basic/prefix-sum/#%E4%BA%8C%E7%BB%B4%E5%A4%9A%E7%BB%B4%E5%89%8D%E7%BC%80%E5%92%8C
相关: LeetCode303. 区域和检索 - 数组不可变, LeetCode2132. 用邮票贴满网格图
标签: 二维前缀和
*/

#include <bits/stdc++.h>

using namespace std;

// 这题`LeetCode2132. 用邮票贴满网格图`要用到
class NumMatrix {
public:
    vector<vector<int>> sum;

    NumMatrix(vector<vector<int>>& matrix) : sum(matrix.size() + 1, vector<int>(matrix[0].size() + 1)) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row1][col2 + 1] - sum[row2 + 1][col1] + sum[row1][col1];
    }
};

int main(int argc, char const *argv[]) {
    vector<vector<int>> matrix = {{3,0,1,4,2},{5,6,3,2,1},{1,2,0,1,5},{4,1,0,1,7},{1,0,3,0,5}};
    NumMatrix solu(matrix);
    cout << solu.sumRegion(2,1,4,3) << endl;
    cout << solu.sumRegion(1,1,2,2) << endl;
    cout << solu.sumRegion(1,2,2,4) << endl;
    return 0;
}
