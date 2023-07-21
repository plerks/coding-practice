/*
url: https://leetcode.cn/problems/maximum-subarray/
题目简述: 给你一个整数数组nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
相关: https://leetcode.cn/problems/maximum-sum-circular-subarray/
外部参考: https://zhuanlan.zhihu.com/p/144385162
*/

public class Solution53 {
    public int maxSubArray(int[] nums) {
        // dp[i]代表以nums[i]为结尾的子数组的最大和，dp[i] = Math.max(nums[i], nums[i] + dp[i - 1])，然后dp[]中最大的值为全局最大值
        int[] dp = new int[nums.length];
        dp[0] = nums[0]; // 最大子数组非空，所以初始值为nums[0]
        int max = nums[0];
        for (int i = 1; i < nums.length; i++) {
            dp[i] = Math.max(nums[i], nums[i] + dp[i - 1]);
            max = Math.max(dp[i], max);
        }
        return max;
    }

    // 另外一种实现，减小空间复杂度
    public int maxSubArray_Implementation2(int[] nums) {
        int currentMax = nums[0];
        int max = nums[0];
        for (int i = 1; i < nums.length; i++) {
            currentMax = Math.max(currentMax + nums[i], nums[i]);
            max = Math.max(max, currentMax);
        }
        return max;
    }

    public static void main(String[] args) {
        Solution53 solu = new Solution53();
        System.out.println(solu.maxSubArray(new int[]{1, 2, -1}));
    }
}