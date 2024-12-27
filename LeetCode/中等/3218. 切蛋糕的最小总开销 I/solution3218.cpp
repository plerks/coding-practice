/*
url: https://leetcode.cn/problems/minimum-cost-for-cutting-cake-i/description/?envType=daily-question&envId=2024-12-25
相关: LeetCode3219. 切蛋糕的最小总开销 II
*/

#include <bits/stdc++.h>

using namespace std;

// 此题与`LeetCode3219. 切蛋糕的最小总开销 II`题目相同，数据范围更小
class Solution3218 {
public:
    // 我的解法，记忆化搜索，很慢但是能通过，2692ms
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        map<tuple<int, int, int, int>, int> memo;

        auto dfs = [&](auto &dfs, int row, int col, int rowCount, int colCount) {
            if (rowCount <= 1 && colCount <= 1) return 0;
            if (memo.count({row, col, rowCount, colCount})) return memo[{row, col, rowCount, colCount}];

            // 枚举第一刀
            int t = INT_MAX;

            for (int i = row; i < row + rowCount - 1; i++) {
                t = min(t, horizontalCut[i] + 
                dfs(dfs, row, col, (i - row + 1), colCount) + 
                dfs(dfs, i + 1, col, rowCount - (i - row + 1), colCount)
                );
            }

            for (int j = col; j < col + colCount - 1; j++) {
                t = min(t, verticalCut[j] + 
                dfs(dfs, row, col, rowCount, (j - col + 1)) +
                dfs(dfs, row, j + 1, rowCount, colCount - (j - col + 1))
                );
            }

            memo[{row, col, rowCount, colCount}] = t;

            return t;
        };

        return dfs(dfs, 0, 0, m, n);
    }

    // 用时0ms，`LeetCode3219. 切蛋糕的最小总开销 II`的解法，具体见那题
    int minimumCost_implementation2(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        sort(horizontalCut.begin(), horizontalCut.end());
        sort(verticalCut.begin(), verticalCut.end());
        int p = 0, q = 0;
        long long ans = 0;
        while (!horizontalCut.empty() || !verticalCut.empty()) {
            if (!horizontalCut.empty() && (verticalCut.empty() || horizontalCut.back() >= verticalCut.back())) {
                ans += horizontalCut.back() * (q + 1);
                horizontalCut.pop_back();
                p++;
            }
            else {
                ans += verticalCut.back() * (p + 1);
                verticalCut.pop_back();
                q++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3218 solu;
    int m = 3;
    int n = 2;
    vector<int> horizontalCut = {1, 3};
    vector<int> verticalCut = {5};
    cout << solu.minimumCost(m, n, horizontalCut, verticalCut) << endl;
    return 0;
}
