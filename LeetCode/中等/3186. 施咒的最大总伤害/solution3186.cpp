/*
url: https://leetcode.cn/problems/maximum-total-damage-with-spell-casting/description/
LeetCode参考: https://leetcode.cn/problems/maximum-total-damage-with-spell-casting/solutions/2812389/tao-lu-da-jia-jie-she-pythonjavacgo-by-e-p9b5/
              https://www.bilibili.com/video/BV1T1421k7Hi/
相关: LeetCode198. 打家劫舍, LeetCode740. 删除并获得点数
标签: LeetCode第402场周赛, 考虑值域, 动态规划, 记忆化搜索, 双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3186 {
public:
    /* 周赛时的做法，通过。一开始想的是，dp[i]表示选power[i]情况下的最大值，然后去考虑上一次选的是左边哪个位置，若左边有等于power[i]的，
    则子问题是power[i - 1]，否则二分查找最后一个< power[i] - 2的位置，然后子问题是power[pos]，但是这样是错的。
    对[2,2,3,5,7,8,9,9,10,10]这个用例，最优解是2,2,7,10,10，7的上一步并不是选最近符合的3，而是选两个2。
    然后考虑换个思路，dp[i]表示使用power[0...i]的最大值，为了能分解问题，需要考虑power[i]到底选不选，于是dp还要多一个维度，
    用dp[i][0]表示power[i]不选，用dp[i][1]表示power[i]选，像`LeetCode3165. 不包含相邻元素的子序列的最大和`那样把dp[i][1]定义成
    power[i]选/不选两种情况下的最大值应该也可以。
    */
    long long maximumTotalDamage(vector<int>& power) {
        int n = power.size();
        sort(power.begin(), power.end());
        vector<vector<long long>> dp(n, vector<long long>(2, 0));
        long long ans = 0;
        dp[0][0] = 0;
        dp[0][1] = power[0];
        for (int i = 1; i < n; i++) {
            // 不选power[i]
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);

            // 选power[i]
            if (power[i - 1] == power[i]) {
                dp[i][1] = max(dp[i][1], dp[i - 1][1] + power[i]); // power[i - 1] == power[i]，选power[i]的情况下肯定把power[i-1]也选上更大
                continue;
            }
            // 二分查找最后一个< power[i] - 2的位置
            int left = 0, right = i - 1;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (power[mid] < power[i] - 2) {
                    left = mid + 1;
                }
                else right = mid - 1;
            }
            int pos = left - 1;
            if (pos == -1) dp[i][1] = power[i];
            else dp[i][1] = max(dp[i][1], max(dp[pos][0], dp[pos][1]) + power[i]); // 这里不能贪心地认为power[pos]必选，pos位置选或不选都可能
        }
        for (int i = 0; i < n; i++) {
            ans = max(ans, max(dp[i][0], dp[i][1]));
        }
        return ans;
    }

    // 灵茶山艾府解法，用记忆化搜索来写，把power中的数字记频率去重，然后变成相邻左右两个位置不可取，然后变成`LeetCode打家劫舍`的变形
    long long maximumTotalDamage_implementation2(vector<int>& power) {
        unordered_map<int, int> map;
        for (int p : power) map[p]++;
        vector<pair<int, int>> vec(map.begin(), map.end()); // 处理出值域
        sort(vec.begin(), vec.end());
        int n = vec.size();
        vector<long long> memo(n, -1);

        // dfs(i)表示用去重后的[i, n - 1]部分的数得到的最大值
        // 这里lambda递归必须用dfs(dfs, i)的写法，由于lambda参数为auto，因此需要C++14标准。
        // 如果用function<long long(int)>，会超时，540 / 554 个通过的测试用例，出乎意料
        auto dfs = [&](auto& dfs, int i) -> long long {
            if (i >= n) return 0;
            auto &p = vec[i];
            if (memo[i] != -1) return memo[i];
            if (i == n - 1) return (long long)p.first * p.second;
            // 选i
            // 找右边第一个> power[i] + 2的，后续范围变为[j, n - 1]，由于对power进行了去重记频率(类似python的Counter())，所以很快会找到
            int j = i;
            while (j < n && vec[j].first <= vec[i].first + 2) {
                j++;
            }
            long long res1 = dfs(dfs, j) + (long long)p.first * p.second;
            // 不选i
            long long res2 = dfs(dfs, i + 1);
            memo[i] = max(res1, res2);
            return memo[i];
        };

        // 这里是移动左边界从左往右选，也可以移动右边界从右往左选
        return dfs(dfs, 0);
    }

    // 灵茶山艾府题解解法，递推
    long long maximumTotalDamage_implementation3(vector<int>& power) {
        unordered_map<int, int> map;
        for (int p : power) map[p]++;
        vector<pair<int, int>> vec(map.begin(), map.end()); // 处理出值域
        sort(vec.begin(), vec.end());
        int n = vec.size();
        // dp数组开头多填一个0，不去特殊考虑i为0的情况
        vector<long long> dp(n + 1, 0); // dp[i + 1]表示使用vec[0...i]范围，得到的最大值

        // 这种dp填充一位的技巧，i仍然是power的范围，只是dp时候的下标要加上1，**i仍然表示原本的下标，只有涉及到dp数组时要加1**
        /* j表示第一个>= vec[i].first - 2的位置。这里j是双指针，在i变大的途中，需要找第一个>= vec[i].first - 2的位置，而
        vec是排序了的，所以j只会单调增加，适合双指针，比对每个i，向左遍历找j的位置更优 */
        for (int i = 0, j = 0; i < n; i++) {
            // 选或不选vec[i]
            // 选
            while (vec[j].first < vec[i].first - 2) {
                j++;
            }
            // j - 1是最后一个<vec[i].first - 2的位置，然后这里dp数组开头多填了个0，所以dp数组的下标要加1
            long long res1 = dp[j - 1 + 1] + (long long)vec[i].first * vec[i].second;
            // 不选
            long long res2 = dp[i];
            dp[i + 1] = max(res1, res2);
        }
        return dp[n];
    }
};

int main(int argc, char const *argv[]) {
    Solution3186 solu;
    vector<int> power1 = {1,1,3,4};
    vector<int> power2 = {1,1,3,4};
    vector<int> power3 = {1,1,3,4};
    cout << solu.maximumTotalDamage(power1) << endl;
    cout << solu.maximumTotalDamage_implementation2(power2) << endl;
    cout << solu.maximumTotalDamage_implementation3(power3) << endl;
    return 0;
}
