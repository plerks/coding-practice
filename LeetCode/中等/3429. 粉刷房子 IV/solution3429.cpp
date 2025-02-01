/*
url: https://leetcode.cn/problems/paint-house-iv/
参考: https://www.bilibili.com/video/BV17RwBeqErJ/
标签: LeetCode第433场周赛, 并步动态规划
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3429 {
public:
    /* 参考灵茶题解，
    头一次见的动态规划方式，要在对称位置，一次两步地进行规划
    */
    long long minCost(int n, vector<vector<int>>& cost) {
        vector<array<array<long long, 3>, 3>> f(n / 2); // f[i][c1][c2]表示在i位置涂c1，在n - i - 1涂c2的最小开销
        for (int c1 = 0; c1 < 3; c1++) {
            for (int c2 = 0; c2 < 3; c2++) {
                if (c1 == c2) continue;
                f[0][c1][c2] = cost[0][c1] + cost[n - 1][c2];
            }
        }
        for (int i = 1; i < n / 2; i++) {
            for (int c1 = 0; c1 < 3; c1++) {
                for (int c2 = 0; c2 < 3; c2++) {
                    long long res = LLONG_MAX;
                    if (c1 == c2) continue;
                    for (int pre_c1 = 0; pre_c1 < 3; pre_c1++) {
                        for (int pre_c2 = 0; pre_c2 < 3; pre_c2++) {
                            if (pre_c1 == pre_c2) continue;
                            if (c1 == pre_c1 || c2 == pre_c2) continue;
                            res = min(res, f[i - 1][pre_c1][pre_c2] + cost[i][c1] + cost[n - 1 - i][c2]);
                        }
                    }
                    f[i][c1][c2] = res;
                }
            }
        }
        long long ans = LLONG_MAX;
        for (int c1 = 0; c1 < 3; c1++) {
            for (int c2 = 0; c2 < 3; c2++) {
                if (c1 != c2) ans = min(ans, f[n / 2 - 1][c1][c2]);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3429 solu;
    cout << solu.minCost(4, *new vector<vector<int>>{{3,5,7},{6,2,9},{4,8,1},{7,3,5}}) << endl;
    return 0;
}