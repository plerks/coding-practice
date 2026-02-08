/*
url: https://leetcode.cn/problems/maximum-score-using-exactly-k-pairs/
标签: LeetCode第488场周赛, LCS
*/

// 这次周赛4题，不过题简单
#include <bits/stdc++.h>

using namespace std;

class Solution3836 {
public:
    /* 周赛时的解法，
    这题 n 和 k 范围只有100，最开始的想法是先枚举第一步选的位置p1, p2，然后在状态里枚举下一步的q1, q2，总共有 n^2 * k 个状态，
    每个状态的计算时间是 n^2，时间复杂度会是 O(n^4 * k)，不行。
    还是要从后面开始考虑，类似LCS，当前末尾是 i, j 位置，考虑 i, j 选或不选，然后就是类似LCS的递推方式了
    */
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();

        // f[i][j][K] = max({f[i - 1][j - 1][K - 1] + nums1[i] * nums2[j], f[i - 1][j][K], f[i][j - 1][K], f[i - 1][j - 1][K]})
        long long f[n + 1][m + 1][k + 1];
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; i++) { // 下标从1开始，或者说采取左闭右开区间 nums1[0, i)，nums2[0, j) 表示当前范围
            for (int j = 1; j <= m; j++) {
                for (int K = 1; K <= k; K++) {
                    f[i][j][K] = INT64_MIN;
                    if (min(i, j) < K) continue; // 不合法的选择该为 -inf，合法的选择（包括选 0 对）该为 0
                    // f[i - 1][j - 1][K - 1] + nums1[i - 1] * 1LL * nums2[j - 1] 这里的 f 如果选 0 对也该是 0 ，因为后面有选配对，是 0 才不影响加的结果
                    // 但是对于 f[i - 1][j][K] 这种分支，如果没配对，按上面 f 的值的逻辑，这里要特殊判断让其返回 -inf，否则会返回 0 了，而这题有负数，可能最佳方案也是负，可能造成 0 把最佳方案掩盖
                    f[i][j][K] = max({
                        f[i - 1][j - 1][K - 1] + nums1[i - 1] * 1LL * nums2[j - 1], 
                        i - 1 <= 0 || K == 0 ? INT64_MIN : f[i - 1][j][K], 
                        j - 1 <= 0 || K == 0 ? INT64_MIN : f[i][j - 1][K], 
                        i - 1 <= 0 || j - 1 <= 0 || K == 0 ? INT64_MIN : f[i - 1][j - 1][K] // 参考灵茶题解，这个分支不用单独考虑，被上面包含了
                    });
                }
            }
        }

        return f[n][m][k];
    }

    // 参考灵茶题解，[0, i) × [0, j) 的情况不用单独考虑，包含在了 [0, i) × [0, j] 与 [0, i] × [0, j) 中
    long long maxScore_impl2(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();

        // f[i][j][K] = max({f[i - 1][j - 1][K - 1] + nums1[i] * nums2[j], f[i - 1][j][K], f[i][j - 1][K]})
        long long f[n + 1][m + 1][k + 1];
        std::fill_n(&f[0][0][0], 1LL * (n + 1) * (m + 1) * (k + 1), INT64_MIN); // 第一个参数是 &f[0][0][0] 而不是 f，前者类型是 long long*，后者是 long long (*)[m + 1][k + 1] (指向long long [m + 1][k + 1]二维数组的指针)
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                f[i][j][0] = 0;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int K = 1; K <= k; K++) {
                    if (min(i, j) < K) continue;
                    f[i][j][K] = max({
                        f[i - 1][j - 1][K - 1] + nums1[i - 1] * 1LL * nums2[j - 1], 
                        f[i - 1][j][K], 
                        f[i][j - 1][K]
                    });
                }
            }
        }

        return f[n][m][k];
    }
};

int main(int argc, char const *argv[]) {
    Solution3836 solu;
    cout << solu.maxScore(*new vector<int>{-3,-2}, *new vector<int>{1,2}, 2) << endl;
    cout << solu.maxScore_impl2(*new vector<int>{-3,-2}, *new vector<int>{1,2}, 2) << endl;
    return 0;
}