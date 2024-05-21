/*
url: https://leetcode.cn/problems/check-if-grid-satisfies-conditions/description/
标签: LeetCode第130场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3142 {
public:
    bool satisfiesConditions(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int j = 1; j < n; j++) {
            if (grid[0][j] == grid[0][j - 1]) return false;
        }
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < m; i++) {
                if (grid[i - 1][j] != grid[i][j]) return false;
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
