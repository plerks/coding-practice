/*
url: https://leetcode.cn/problems/house-robber/
相关: https://leetcode.cn/problems/house-robber-ii/
      https://leetcode.cn/problems/maximum-subarray/
      https://leetcode.cn/problems/longest-increasing-subsequence/
      https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
标签: 动态规划, 不相邻取数
*/

public class Solution198 {
    public int rob(int[] nums) {
        if (nums.length == 1) return nums[0];
        int n = nums.length;
        /* dp[i][j]表示对[0..i]间房屋的最大值，这里dp不需要像53. 最大子数组和那样设为以nums[i]结尾，最大子数组和需要那样设是
        因为子数组要求连续，如果将dp设为nums[0..i]中的最大子数组和，在递推时无法保证子数组连续 */
        int[] dp = new int[n];
        dp[0] = nums[0];
        dp[1] = Math.max(nums[0], nums[1]);
        for (int i = 2; i < nums.length; i++) {
            dp[i] = Math.max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[n - 1];
    }

    public static void main(String[] args) {
        Solution198 solu = new Solution198();
        System.out.println(solu.rob(new int[]{1, 2, 3, 5}));
    }
}