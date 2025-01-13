/*
url: https://leetcode.cn/problems/zigzag-grid-traversal-with-skip/
参考: https://leetcode.cn/problems/zigzag-grid-traversal-with-skip/solutions/3045134/mo-ni-pythonjavacgo-by-endlesscheng-9jn7/
标签: LeetCode第432场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3417 {
public:
    // 我的写法，通过
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> ans;
        int d = 2;
        int j = 0;
        for (int i = 0; i < m; i++) {
            while (0 <= j && j < n) {
                ans.push_back(grid[i][j]);
                j += d;
            }
            if (j == n) j = n - 1;
            if (j == n + 1) j = n - 2;
            if (j == -2) j = 1;
            if (j == -1) j = 0;
            d = -d;
        }
        return ans;
    }

    // 灵茶山艾府题解写法，把奇数行反转，并用一个变量记录是否要加入ans
    vector<int> zigzagTraversal_implementation2(vector<vector<int>>& grid) {
        vector<int> ans;
        bool ok = true;
        for (int i = 0; i < grid.size(); i++) {
            if (i % 2) {
                reverse(grid[i].begin(), grid[i].end());
            }
            for (int x : grid[i]) {
                if (ok) ans.push_back(x);
                ok = !ok;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3417 solu;
    auto a = solu.zigzagTraversal(*new vector<vector<int>>{{1,2,3},{4,5,6},{7,8,9}});
    auto b = solu.zigzagTraversal_implementation2(*new vector<vector<int>>{{1,2,3},{4,5,6},{7,8,9}});
    return 0;
}