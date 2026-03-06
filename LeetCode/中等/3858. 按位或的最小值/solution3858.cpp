/*
url: https://leetcode.cn/problems/minimum-bitwise-or-from-grid/
标签: LeetCode第491场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3858 {
public:
    // 按位考虑
    int minimumOR(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> f(m, vector<int>(21)); // f[i][b] 表示第 i 位的 0 的个数
        for (int b = 20; b >= 0; b--) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (((grid[i][j] >> b) & 1) == 0) f[i][b]++;
                }
            }
        }
        vector<vector<bool>> del(m, vector<bool>(n, false));
        int ans = 0;
        for (int b = 20; b >= 0; b--) {
            bool ok = true;
            for (int i = 0; i < m; i++) {
                if (f[i][b] == 0) {
                    ok = false;
                    break;
                }
            }
            if (!ok) { // ans 这一位得是 1 ，且无论如何选都会是 1 ，不用去考虑具体怎么选的
                ans |= (1 << b);
            }
            else {
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        int x = grid[i][j];
                        if (((x >> b) & 1) && !del[i][j]) { // 可以把 ans 这位变成 0 ，这位为 1 的全不能用
                            for (int bb = b; bb >= 0; bb--) {
                                if (((x >> bb) & 1) == 0) f[i][bb]--;
                            }
                            del[i][j] = true;
                        }
                    }
                }
            }
        }
        return ans;
    }

    /* 灵茶题解写法，更简洁，不需要用一个del数组去记录删除情况，
    而是用 x | mask == mask 来判断 x 是否已经被排除过了，
    具体来说，如果 ans 前面的位是 0，那么 x 的位为 1 的全部排除(x | mask == mask 能判断出来)，
    如果 ans 前面的位是 1，那么不会排除数，x | mask 也会 == mask
    */
    int minimumOR_impl2(vector<vector<int>>& grid) {
        int mx = 0;
        for (auto& row : grid) {
            mx = max(mx, *max_element(row.begin(), row.end()));
        }

        int ans = 0;
        for (int i = __lg(mx); i >= 0; i--) {
            int mask = ans | ((1 << i) - 1);
            for (auto& row : grid) {
                bool found0 = false;
                for (int x : row) {
                    if ((x | mask) == mask) {
                        found0 = true;
                        break;
                    }
                }
                if (!found0) {
                    ans |= 1 << i;
                    break;
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}