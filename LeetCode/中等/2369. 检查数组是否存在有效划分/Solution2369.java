/*
url: https://leetcode.cn/problems/check-if-there-is-a-valid-partition-for-the-array/description/?envType=daily-question&envId=2024-03-01
标签: 动态规划
*/

public class Solution2369 {
    public boolean validPartition(int[] nums) {
        int n = nums.length;
        // dp[i]表示是否能以i作为最后一个段的结尾，有效划分nums[0,i]
        boolean[] dp = new boolean[n];
        // 2 <= nums.length <= 10^5
        if (n == 2) return nums[0] == nums[1];
        dp[0] = false;
        dp[1] = nums[0] == nums[1];
        dp[2] = nums[0] == nums[1] && nums[1] == nums[2] || nums[2] == nums[1] + 1 && nums[1] == nums[0] + 1;
        for (int i = 3; i < n; i++) {
            if (nums[i] == nums[i - 1] && dp[i - 2] == true || nums[i] == nums[i - 1] && nums[i - 1] == nums[i - 2] && dp[i - 3] == true) {
                dp[i] = true;
            }
            else if (nums[i] == nums[i - 1] + 1 && nums[i - 1] == nums[i - 2] + 1 && dp[i - 3] == true) {
                dp[i] = true;
            }
            else dp[i] = false;
        }
        return dp[n - 1];
    }

    public static void main(String[] args) {
        Solution2369 solu = new Solution2369();
        // System.out.println(solu.validPartition(new int[]{4,4,4,5,6}));
        // System.out.println(solu.validPartition(new int[]{579611,579611,579611,731172,731172,496074,496074,496074,151416,151416,151416}));
        System.out.println(solu.validPartition(new int[]{1,2}));
    }
}
