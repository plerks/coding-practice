/*
url: https://leetcode.cn/problems/longest-subsequence-with-decreasing-adjacent-difference/description/
参考: https://leetcode.cn/problems/longest-subsequence-with-decreasing-adjacent-difference/solutions/3038930/zhuang-tai-she-ji-you-hua-pythonjavacgo-qy2bu/
      https://www.bilibili.com/video/BV1SzrAYMESJ/
      https://leetcode.cn/problems/longest-subsequence-with-decreasing-adjacent-difference/solutions/3038827/dp-qian-zhui-he-you-hua-by-tsreaper-qrq0/
标签: LeetCode第147场双周赛, 考虑值域, 值域dp, dp的奇妙设法, 后缀最大值
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3409 {
public:
    // 周赛时的思路，不过有些细节当场没调完，调完之后如下，但是会超时
    int longestSubsequence_tle(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(1e4 + 1, vector<int>(301, -1));
        
        // dfs表示上一次选的数是nums[i]，且nums[i]和下一个选出的数的绝对差是d的情况下，前面能获得的最大长度
        auto dfs = [&](auto &dfs, int i, int d) -> int {
            if (i == 0) return 0;
            if (memo[i][d] != -1) return memo[i][d];
            int mx = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (abs(nums[i] - nums[j]) >= d) {
                    mx = max(mx, 1 + dfs(dfs, j, abs(nums[i] - nums[j])));
                }
            }
            memo[i][d] = mx;
            return mx;
        };
        int ans = 0;
        /* 这里有层循环，记n为nums长度，D为nums中元素的最大差值，最后的时间复杂度为O(n^2 + nD)，n最大1e4，D最大299，会超时。
        但是没这层循环又不行，需要将dfs(i, d)定义为选nums[i]的情况下，前面的最大长度，如果不确定选/不选，那么枚举j之后，就无法确定
        j与j右边那个选出的数(不知道是谁)的绝对差是否 >= d
        */
        for (int i = n - 1; i >= 0; i--) {
            ans = max(ans, 1 + dfs(dfs, i, 0));
        }
        return ans;
    }

    /* 灵茶山艾府题解解法一。
    由于D较小，所以考虑枚举值域，假如将f[i][j]定义为以nums[i]结尾，且最后两个数的差 == j 的最长长度，
    那么 for (int i = 1; i <= n; i++) {
            for (int d = 0; d <= D; d++) {
                f[i][d] = f[last[i - nums[i]]][?] + 1;
                f[i][d] = f[last[i + nums[i]]][?] + 1;
            }
        }
    ?处还需要枚举其取值为 >= d 的所有取值，时间复杂度为O(n * D^2)，会超时(可以通过记录对某个i，d>=d0范围内的后缀最大f值来优化)。
    而我们实际需要的是?处 >=d 即可，因此，改变f设法，将f[i][j]定义为以nums[i]结尾，且最后两个数的差 >= j 的最长长度。
    注意对同样的x，j越小，f越大，因此f[i][j + 1]就是对第二个维度的后缀最大值，这样就少了一重循环。
    那么，对f[i][j]，可以让i单独一个数，这样也认为最后两个数之差够大(或者f的定义里加上一种情况就是单个元素的)，
    也可以让最后两数之差为j，这样f[i][j] = f[last[nums[i] +/- j]][j] + 1，
    也可以让最后两数之差>j，即>=j+1，这样f[i][j] = f[i][j + 1]，(也就是让nums[i]前面那个选出的数更小)
    然后这几种情况取max:
    f[i][j] = max(1, f[last[nums[i] + j]][j] + 1, f[last[nums[i] - j]][j] + 1, f[i][j + 1])
    这个dp的定义产生了本质的区别，很奇妙。关键点应该在于，设成>=之后，使得f对第二个维度单调了，因此f[i][j + 1]就是对第二个维度的后缀最大值。
    也就是说，**定义为 >= ，变成了定义为 == 情况下的后缀最大值**。

    时间复杂度O(nD)，空间复杂度O(nD)
    */
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int D = *max_element(nums.begin(), nums.end()) - *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());
        vector<vector<int>> f(n, vector<int>(D + 2));
        vector<int> last(mx + 1, -1); // last[x]表示x最近出现的位置，同样的diff下，nums[i]的前一个元素更靠右，有更多选择机会，子序列能更长
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int d = D; d >= 0; d--) { // 初始情况，当 d >= D + 1 时f[i][d + 1]是0
                f[i][d] = max(1, f[i][d + 1]);
                if (x - d >= 0 && last[x - d] >= 0) {
                    f[i][d] = max(f[i][d], f[last[x - d]][d] + 1);
                }
                if (x + d <= mx && last[x + d] >= 0) {
                    f[i][d] = max(f[i][d], f[last[x + d]][d] + 1);
                }
                ans = max(ans, f[i][d]);
            }
            last[x] = i; // 动态维护last
        }
        return ans;
    }

    /* 灵茶山艾府题解解法二，
    实际上f的第一维更关心的是具体的nums[i]的值，因此改变f的定义
    定义f[x][d]为以值x结尾，最后两个数的绝对差>=d(或者序列只有一个数)的要求下，的最大长度。这样就不需要last数组。
    f[x][d] = max(1, f[x][d + 1], f[x + d][d] + 1, f[x - d][d] + 1)
    注意这里和上一种解法有区别，当d == 0时，f[x + d][d]和f[x][d]相同，没有变成子问题，会产生自增1的问题，需要用一个临时变量先算4种情况再更新f[x][d]
    
    时间复杂度O(nD)，空间复杂度O(D^2)
    */
    int longestSubsequence_implementation2(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        int D = mx - *min_element(nums.begin(), nums.end());
        vector<vector<int>> f(mx + 1, vector<int>(D + 1));
        int ans = 0;
        for (int x : nums) {
            int t = 1; // 这里把对 1和f[x][d + 1] 取max合并了
            for (int d = D; d >= 0; d--) {
                // t现在是上一轮的f[x][d + 1]，接下来计算f[x][d]
                if (x + d <= mx) {
                    t = max(t, f[x + d][d] + 1);
                }
                if (x - d >= 0) {
                    t = max(t, f[x - d][d] + 1);
                }
                f[x][d] = t;
                ans = max(ans, t);
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3409 solu;
    cout << solu.longestSubsequence(*new vector<int>({5,2,3,10,10})) << endl;
    cout << solu.longestSubsequence_implementation2(*new vector<int>({5,2,3,10,10})) << endl;
    return 0;
}