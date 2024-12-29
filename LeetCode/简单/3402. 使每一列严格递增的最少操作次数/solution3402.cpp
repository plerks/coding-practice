/*
url: https://leetcode.cn/problems/minimum-operations-to-make-columns-strictly-increasing/
标签: LeetCode第430场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3402 {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < m; i++) {
                if (grid[i][j] > grid[i - 1][j]) continue;
                ans += grid[i - 1][j] + 1 - grid[i][j];
                grid[i][j] = grid[i - 1][j] + 1;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
