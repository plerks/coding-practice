/*
url: https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
相关: https://leetcode.cn/problems/longest-increasing-subsequence/
*/

public class Solution674 {
    public int findLengthOfLCIS(int[] nums) {
        int[] dp = new int[nums.length]; // dp[i]表示以nums[i]结尾的最大连续递增子序列长度
        dp[0] = 1;
        int max = 1;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] > nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            }
            else {
                dp[i] = 1;
            }
            max = Math.max(max, dp[i]);
        }
        return max;
    }

    public int findLengthOfLCIS_implementation2(int[] nums) {
        int predp = 1;
        int dp = 0;
        int max = 1;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] > nums[i - 1]) {
                dp = predp + 1;
                predp = dp;
            }
            else {
                dp = 1;
                predp = dp;
            }
            max = Math.max(max, dp);
        }
        return max;
    }

    public static void main(String[] args) {
        Solution674 solu = new Solution674();
        System.out.println(solu.findLengthOfLCIS(new int[]{1,3,5,4,7}));
        System.out.println(solu.findLengthOfLCIS_implementation2(new int[]{1,3,5,4,7}));
    }
}