/*
url: https://leetcode.cn/problems/find-the-maximum-sequence-value-of-array/description/?envType=daily-question&envId=2025-01-18
参考: https://leetcode.cn/problems/find-the-maximum-sequence-value-of-array/solutions/2917604/qian-hou-zhui-fen-jie-er-wei-0-1-bei-bao-8icz/
      https://leetcode.cn/problems/find-the-maximum-sequence-value-of-array/solutions/2917491/mei-ju-dp-by-tsreaper-ozq5/
标签: 子序列
*/

#include <bits/stdc++.h>

using namespace std;

// 注意不要写到class Solution {}里面了，不然会反复创建
bool pre[401][202][1 << 7], suf[401][202][1 << 7];

class Solution3287 {
public:
    /* 参考灵茶山艾府题解，
    考虑值域，
    用pre[i][j][x]表示，对于前i个元素，nums[0 ... i），使用j个元素，能否|出x
    用suf[i][j][x]表示，对于后i个元素，nums[n - i ... n)，使用j个元素，能否|出x
    则若 pre[i][j][x]为true，则
        1. 若不选nums[i]，则pre[i + 1][j][x]为true
        2. 若选nums[i]，则pre[i + 1][j + 1][x | nums[i + 1]]为true
    若 suf[i][j][x]为true，则 suf[i - 1][j + 1][x | nums[i - 1]]为true

    灵茶题解中称为"刷表法"，本题如果考虑对求f[i][j][x]，上一步选nums[i - 1]，那么上一步由谁 ? | nums[i - 1] = x，
    对?的计算是困难的，但是计算 x | nums[i - 1]（能转移到谁）是简单的：
        在动态规划中，根据转移来源计算状态叫查表法，用当前状态更新其他状态叫刷表法。
    */
    // 用vector要954ms
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        const int MX = 1 << 7; // 1 <= nums[i] < 2^7
        vector<vector<vector<int>>> pre(n + 1, vector<vector<int>>(k + 2, vector<int>(MX, false)));
        pre[0][0][0] = true;
        for (int i = 0; i < n; i++) { // 域
            for (int j = 0; j <= k; j++) { // 个数
                for (int x = 0; x < MX; x++) { // 值
                    int v = nums[i];
                    if (pre[i][j][x]) { // 刷表
                        pre[i + 1][j][x] = true;
                        pre[i + 1][j + 1][x | v] = true;
                    }
                }
            }
        }
        vector<vector<vector<int>>> suf(n + 1, vector<vector<int>>(k + 2, vector<int>(MX, false)));
        suf[n][0][0] = true;
        for (int i = n; i > 0; i--) {
            for (int j = 0; j <= k; j++) {
                for (int x = 0; x < MX; x++) {
                    int v = nums[i - 1];
                    if (suf[i][j][x]) {
                        suf[i - 1][j][x] = true;
                        suf[i - 1][j + 1][x | v] = true;
                    }
                }
            }
        }
        int ans = 0;
        // 前后缀分解，枚举分界线，前面[0, i)，后面[i, n)
        for (int i = k; n - i >= k; i++) {
            for (int x1 = 0; x1 < MX; x1++) {
                for (int x2 = 0; x2 < MX; x2++) {
                    if (pre[i][k][x1] && suf[i][k][x2]) {
                        ans = max(ans, x1 ^ x2);
                    }
                }
            }
        }
        return ans;
    }

    // 用全局数组，307ms
    int maxValue_implementation2(vector<int>& nums, int k) {
        int n = nums.size();
        constexpr int MX = 1 << 7; // 1 <= nums[i] < 2^7
        for (int i = 0; i < n + 1; i++) { // 多次创建Solution对象，全局数组的初始化
            for (int j = 0; j < k + 2; j++) {
                for (int x = 0; x < (1 << 7); x++) {
                    pre[i][j][x] = suf[i][j][x] = false;
                }
            }
        }
        pre[0][0][0] = true;
        for (int i = 0; i < n; i++) { // 域
            for (int j = 0; j <= k; j++) { // 个数
                for (int x = 0; x < MX; x++) { // 值
                    if (pre[i][j][x]) { // 刷表
                        pre[i + 1][j][x] = true;
                        pre[i + 1][j + 1][x | nums[i]] = true;
                    }
                }
            }
        }
        suf[n][0][0] = true;
        for (int i = n; i > 0; i--) {
            for (int j = 0; j <= k; j++) {
                for (int x = 0; x < MX; x++) {
                    if (suf[i][j][x]) {
                        suf[i - 1][j][x] = true;
                        suf[i - 1][j + 1][x | nums[i - 1]] = true;
                    }
                }
            }
        }
        int ans = 0;
        // 前后缀分解，枚举分界线，前面[0, i)，后面[i, n)
        for (int i = k; n - i >= k; i++) {
            for (int x1 = 0; x1 < MX; x1++) {
                for (int x2 = 0; x2 < MX; x2++) {
                    if (pre[i][k][x1] && suf[i][k][x2]) {
                        ans = max(ans, x1 ^ x2);
                    }
                }
            }
        }
        return ans;
    }

    // 灵茶题解解法一，相比maxValue()，由于计算答案时只需要j==k时的数据，因此可以优化空间使用，类似0-1背包问题的空间优化技巧
    int maxValue_implementation3(vector<int>& nums, int k) {
        int n = nums.size();
        const int MX = 1 << 7; // 1 <= nums[i] < 2^7
        // 用pre[i-1][][]算出pre[i][][]后，只需要存pre[i][x]，pre里记录的全是j==k时候的
        vector<vector<int>> pre(n - k + 1, vector<int>(MX, false));
        // 用于计算的f[j][x]
        vector<vector<int>> f(k + 1, vector<int>(MX, false));
        f[0][0] = true;
        for (int i = 0; i < n - k; i++) {
            for (int j = min(k - 1, i); j >= 0; j--) { // x | v会变大，左侧会更新右侧，j必须从右往左遍历
                for (int x = 0; x < MX; x++) {
                    int v = nums[i];
                    if (f[j][x]) { // 刷表
                        f[j + 1][x | v] = true;
                    }
                }
            }
            pre[i + 1] = f[k];
        }
        int ans = 0;
        // 用于计算的f[j][x]
        f = vector<vector<int>>(k + 1, vector<int>(MX, false));
        f[0][0] = true;
        for (int i = n - 1; i >= k; i--) {
            for (int j = min(k - 1, n - i); j >= 0; j--) {
                for (int x = 0; x < MX; x++) {
                    int v = nums[i];
                    if (f[j][x]) {
                        f[j + 1][x | v] = true;
                    }
                }
            }
            if (i > n - k) continue;
            // 这时候的f[k]就是suf[i]
            // 现在后缀用的是 [i - 1, n) 范围内的数
            for (int x1 = 0; x1 < MX; x1++) {
                for (int x2 = 0; x2 < MX; x2++) {
                    if (pre[i][x1] && f[k][x2]) {
                        ans = max(ans, x1 ^ x2);
                    }
                }
            }
        }
        return ans;
    }

    // 待做: 灵茶题解还有个解法二，以后再看吧
    int maxValue_implementation4(vector<int>& nums, int k) {

    }
};

int main(int argc, char const *argv[]) {
    Solution3287 solu;
    // cout << solu.maxValue(*new vector<int>{2,6,7}, 1) << endl;
    cout << solu.maxValue(*new vector<int>{4,2,5,6,7}, 2) << endl;
    cout << solu.maxValue_implementation2(*new vector<int>{4,2,5,6,7}, 2) << endl;
    // cout << solu.maxValue_implementation3(*new vector<int>{4,2,5,6,7}, 2) << endl;
    cout << solu.maxValue_implementation3(*new vector<int>{50,41,124,66}, 2) << endl;
    return 0;
}