/*
url: https://leetcode.cn/problems/house-robber-ii/
相关: https://leetcode.cn/problems/house-robber/
标签: 动态规划, 不相邻取数
*/

public class Solution213 {
    public int rob(int[] nums) {
        if (nums.length == 1) return nums[0];
        // 环形，特殊点在于第一个和最后一个不能同时取，其它与198. 打家劫舍相同。因此分别两次dp，分别表示第一个不取和最后一个不取
        int[] nums1 = new int[nums.length - 1];
        int[] nums2 = new int[nums.length - 1];
        for (int i = 0; i < nums1.length; i++) {
            nums1[i] = nums[i];
        }
        for (int i = 0; i < nums2.length; i++) {
            nums2[i] = nums[i + 1];
        }
        return Math.max(doDp(nums1), doDp(nums2));
    }

    public int doDp(int[] nums) {
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
        Solution213 solu = new Solution213();
        System.out.println(solu.rob(new int[]{0}));
    }
}