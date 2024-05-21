/*
url: https://leetcode.cn/problems/find-the-minimum-cost-array-permutation/description/
LeetCode参考: https://leetcode.cn/problems/find-the-minimum-cost-array-permutation/solutions/2775272/zhuang-ya-dpcong-ji-yi-hua-sou-suo-dao-d-s9t5/
              https://leetcode.cn/circle/discuss/tXLS3i/
相关: LeetCode46. 全排列, LeetCode47. 全排列 II
标签: LeetCode第397场周赛, 记忆化搜索, 状压dp, 全排列, 排列型dp-相邻相关
*/

#include <bits/stdc++.h>

using namespace std;

// 这次周赛通过3题

class Solution3149 {
public:
    // 暴力法 + 剪枝，938 / 939 个通过的测试用例，超时
    vector<int> findPermutation_time_limit_exceeded(vector<int>& nums) {
        int n = nums.size();
        int min = INT_MAX;
        vector<int> visited(n, 0);
        vector<int> perm;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            perm.push_back(i);
            visited[i] = true;
            dfs(i, 0, nums, visited, perm, min, ans, 1);
            visited[i] = false;
            perm.pop_back();
        }
        return ans;
    }

    void dfs(int i, int sum, vector<int> &nums, vector<int> &visited, vector<int> &perm, int &min, vector<int> &ans, int count) {
        int n = nums.size();
        if (sum >= min) return; // 剪枝
        if (count == n) {
            sum += abs(perm[n - 1] - nums[perm[0]]);
            if (sum < min) {
                ans = perm;
                min = sum;
            }
            return;
        }
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            perm.push_back(i);
            visited[i] = true;
            dfs(i, sum + abs(perm[count - 1] - nums[perm[count]]), nums, visited, perm, min, ans, count + 1);
            visited[i] = false;
            perm.pop_back();
        }
    }

    // 同上面的暴力法，但是改成用函数对象避免dfs传参麻烦，增加第一个元素一定为0的剪枝，也超时
    vector<int> findPermutation_time_limit_exceeded2(vector<int>& nums) {
        int n = nums.size();
        int min = INT_MAX;
        vector<int> visited(n, 0);
        vector<int> perm;
        vector<int> ans;

        // lambda不能递归，要用std::function包一下，具体见scratch/recursive_lambda.cpp
        function<void(int, int, int)> dfs = [&](int i, int sum, int count) {
            int n = nums.size();
            if (sum >= min) return; // 剪枝
            if (count == n) {
                sum += abs(perm[n - 1] - nums[perm[0]]);
                if (sum < min) {
                    ans = perm;
                    min = sum;
                }
                return;
            }
            for (int i = 1; i < n; i++) {
                if (visited[i]) continue;
                perm.push_back(i);
                visited[i] = true;
                dfs(i, sum + abs(perm[count - 1] - nums[perm[count]]), count + 1);
                visited[i] = false;
                perm.pop_back();
            }
        };

        // 剪枝。这题排列的分数的定义，分数值与起点无关，相当于是个循环数组，要求字典序最小，因此首位一定是0
        perm.push_back(0);
        visited[0] = true;
        dfs(0, 0, 1);
        visited[0] = false;
        perm.pop_back();
        return ans;
    }

    /* 灵茶山艾府题解解法一，记忆化搜索。观察暴力法，当枚举某一个位置选x时，这时为了算分数，只需关心左侧的成分和上一次选的数即可，
    而上面暴力法枚举了左侧的全排列，这就存在优化的空间，且左侧部分是子问题的特征。
    dfs(s, j)，s是已选的数的集合，2 <= n == nums.length <= 14，状压，用每位的1表示选出数，j是最新选的数，然后用记忆化搜索，当左侧所选的成分相同时，
    不需要知道具体排列方式，只需要知道成分已经上一次选的数即可，因此可以dp。

    时间复杂度: 记忆化搜索的时间复杂度为状态个数 * 单个状态的计算时间 = (2 ^ n * n) * n = O(n^2 * 2^n)
    */
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(1 << n, vector<int>(n, -1));

        // dfs()返回当前状态(已选出的数)为s且上一个选出的元素为j的前提下，右边能摆出的最小值
        // s相当于一个set，存已选出的数
        function<int(int, int)> dfs = [&](int s, int j) {
            if (memo[s][j] != -1) return memo[s][j];
            if (s == (1 << n) - 1) {
                memo[s][j] = abs(j - nums[0]);
                return abs(j - nums[0]); // 第一个位置一定是0
            }
            int min = INT_MAX;
            for (int k = 0; k < n; k++) { // 这一次的选择
                if ((s & (1 << k)) == 0) {
                    int temp = abs(j - nums[k]) + dfs(s | (1 << k), k);
                    min = std::min(min, temp);
                }
            }
            memo[s][j] = min;
            return min;
        };

        dfs(1, 0);
        vector<int> ansVec;

        // 前面知道了最小值，再次dfs求对应的字典序最小的解
        function<void(int, int)> reDfs = [&](int s, int j) {
            ansVec.push_back(j);
            if (s == (1 << n) - 1) {
                return;
            }
            int rightMin = memo[s][j]; // 右侧部分的最优值
            for (int k = 0; k < n; k++) {
                if ((s & (1 << k)) == 0) {
                    int temp = abs(j - nums[k]) + memo[s | (1 << k)][k];
                    if (temp == rightMin) {
                        reDfs(s | (1 << k), k);
                        break; // 找到第一个直接停止，因此找到的是字典序最小的
                    }
                }
            }
        };

        reDfs(1, 0);
        return ansVec;
    }

    /* 灵茶山艾府题解解法二，从记忆化搜索到dp。
    按照递归"归"的过程计算，dp的初始值等于递归的递归边界，所以这里要倒着dp，且s | (1 << k)是大于s的，所以有个
    确定的计算顺序，能dp。
    具体来说，
    f[s][j] = max{abs(j - nums[k]) + f[s | (1 << k)][k]}
    f[s][j]依赖于f[s | (1 << k)][k]，所以必须先算f[s | (1 << k)][k]，而j正向或者逆向遍历都可以，依赖项都是计算完毕了的
    f[s][j]相当于当前已选为s，最新选择为j的情况下，剩余数字所能达到的最小值。

    时间复杂度O(n^2 * 2^n)
    */
    vector<int> findPermutation_implementation2(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> f(1 << n, vector<int>(n, INT_MAX));
        vector<vector<int>> next(1 << n, vector<int>(n, INT_MAX)); // 最优解的下一个选择
        for (int j = 0; j < n; j++) {
            if ((((1 << n) - 1) & j) != 0) {
                f[((1 << n) - 1)][j] = abs(j - nums[0]);
            }
        }
        for (int s = ((1 << n) - 3); s > 0; s -= 2) { // 从一开始就一定会选0，所以s一定是奇数，于是直接跳过偶数
            for (int j = 0; j < n; j++) {
                if (((s >> j) & 1) == 0) continue; // j必须在s中
                for (int k = 0; k < n; k++) {
                    if (s >> k & 1) continue; // k必须不在s中
                    int temp = abs(j - nums[k]) + f[s | (1 << k)][k];
                    if (temp < f[s][j]) {
                        f[s][j] = temp;
                        next[s][j] = k;
                    }
                }
            }
        }
        vector<int> ansVec;
        int s = 1;
        int j = 0;
        for (int i = 0; i < n; i++) {
            s |= 1 << j;
            ansVec.push_back(j);
            j = next[s][j];
        }
        return ansVec;
    }

    /* 这题算是比较奇妙的，居然可以不用暴力法，虽然不同排列之间确实有重合，但是能有办法用起来这种重合。
    关键点在于，对... i ...这样的排列，对这题要计算的值，只需关心i左边的组成成分 + 上一个选取，
    连具体排列方式都不需要关心。由于拆分并复用了子问题，时间复杂度只需O(n^2 * 2^n)，相比之下全排列有n!个。
    这种问题灵茶山艾府总结称之为"排列型dp-相邻相关"，见<https://leetcode.cn/circle/discuss/tXLS3i/>
    相邻相关是指，对于选i，需要知道左边最新选取的值，所以是相邻相关的。
    */
};

int main(int argc, char const *argv[]) {
    Solution3149 solu;
    vector<int> nums = {0,2,1};
    auto a = solu.findPermutation(nums);
    auto b = solu.findPermutation_implementation2(nums);
    return 0;
}
