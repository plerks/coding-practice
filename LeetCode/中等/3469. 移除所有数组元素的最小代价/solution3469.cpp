/*
url: https://leetcode.cn/problems/find-minimum-cost-to-remove-array-elements/
参考: https://www.bilibili.com/video/BV1m39bYiEVV/
      https://leetcode.cn/problems/find-minimum-cost-to-remove-array-elements/solutions/3591399/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-905d/
标签: LeetCode第151场双周赛, 特殊动态规划
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3469 {
public:
    /* 参考灵茶题解，dp，很奇妙的dp，
    这整个过程，nums的状态一定是前面有个单独的数，然后剩下的部分作为尾，即i, [j, n-1]这样的状态(不会出现多段，这个性质很重要)，
    然后可以记忆化搜索/dp，时间复杂度O(n^2)。
    */
    int minCost(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> f(n, vector<int>(n + 1)); // f[i][j]表示i, [j, n-1]这样的状态下的最小开销
        // f[i][j] = min({max(nums[i], nums[j]) + f[j + 1][j + 2], max(nums[j], nums[j + 1]) + f[i][j + 2], max(nums[i], nums[j + 1]) + f[j][j + 2]})
        for (int i = 0; i < n; i++) {
            f[i][n] = nums[i];
            f[i][n - 1] = max(nums[i], nums.back());
        }
        /* 根据递推关系，从右往左算。答案为f[0][1]，j每次变化2，当n为奇数时f[0][1]的最后一步j是n-2，
        当n为偶数时f[0][1]计算的最后一步j是n-3，所以j从n - 3 + n % 2开始枚举，且每次-2，不用算f的每个值！
        只需要关心计算f[0][1]相关的位置。不过一般写的话，把j多留个n, n+1下标作为哨兵，然后填整个表容易写，也不容易出错。
        */
        for (int j = n - 3 + n % 2; j > 0; j -= 2) {
            for (int i = j - 1; i >= 0; i--) {
                f[i][j] = min({max(nums[i], nums[j]) + f[j + 1][j + 2], max(nums[j], nums[j + 1]) + f[i][j + 2], max(nums[i], nums[j + 1]) + f[j][j + 2]});
            }
        }
        return f[0][1];
    }
};

int main(int argc, char const *argv[]) {
    Solution3469 solu;
    cout << solu.minCost(*new vector<int>{6,2,8,4}) << endl;
    cout << solu.minCost(*new vector<int>{1}) << endl;
    return 0;
}