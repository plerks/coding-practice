/*
url: https://leetcode.cn/problems/longest-increasing-subsequence/
相关: https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
*/

public class Solution300 {
    public int lengthOfLIS(int[] nums) {
        int[] dp = new int[nums.length]; // dp[i]表示以nums[i]结尾的最长递增序列长度
        dp[0] = 1;
        int max = 1;
        for (int i = 1; i < nums.length; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                    max = Math.max(max, dp[i]);
                }
                else {
                    dp[i] = Math.max(1, dp[i]);
                }
            }
        }
        return max;
    }

    public static void main(String[] args) {
        Solution300 solu = new Solution300();
        System.out.println(solu.lengthOfLIS(new int[]{10,9,2,5,3,7,101,18}));
    }
}