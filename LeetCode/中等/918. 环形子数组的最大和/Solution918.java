/*
url: https://leetcode.cn/problems/maximum-sum-circular-subarray/
题目简述: 给定一个长度为n的环形整数数组nums，返回nums的非空子数组的最大可能和
相关: https://leetcode.cn/problems/maximum-subarray/
*/

public class Solution918 {
    public int maxSubarraySumCircular(int[] nums) {
        // 分别求最大子数组和（非空）和最小子数组和（可以为空），这两种情况都不会跨越数组末尾，对跨越的情况用总和-最小子数组和即可
        int currentMax = nums[0], max = nums[0]; // 最大子数组和非空，所以初值是nums[0]
        int currentMin = 0, min = 0; // 最小子数组可以为空，所以初值为0。还有一个限制是最小子数组不可为满（后面处理），否则最大子数组为空了
        int sum = nums[0];
        for (int i = 1; i < nums.length; i++) {
            currentMax = Math.max(nums[i], currentMax + nums[i]);
            max = Math.max(currentMax, max);

            currentMin = Math.min(nums[i], currentMin + nums[i]);
            min = Math.min(currentMin, min);

            sum += nums[i];
        }
        if (sum == min) { // 这种情况是nums全为负值，Math.max(max, sum - min)会返回0，选出的可跨越最大子数组为空，不符合非空限制，额外处理
            return max;
        }
        else return Math.max(max, sum - min);
    }

    public static void main(String[] args) {
        Solution918 solu = new Solution918();
        System.out.println(solu.maxSubarraySumCircular(new int[]{5,-3,5}));
    }
}