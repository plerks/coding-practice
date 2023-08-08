/*
url: https://leetcode.cn/problems/maximum-absolute-sum-of-any-subarray/
相关: https://leetcode.cn/problems/maximum-subarray/
LeetCode参考: https://leetcode.cn/problems/maximum-absolute-sum-of-any-subarray/solutions/2372374/ren-yi-zi-shu-zu-he-de-jue-dui-zhi-de-zu-qerr/
*/

public class Solution1749 {
    public int maxAbsoluteSum(int[] nums) {
        int max= nums[0], min = nums[0];
        int currentMax = nums[0], currentMin = nums[0];
        for (int i = 1; i < nums.length; i++) {
            currentMax = Math.max(currentMax + nums[i], nums[i]);
            max = Math.max(currentMax, max);
            currentMin = Math.min(currentMin + nums[i], nums[i]);
            min = Math.min(currentMin, min);
        }
        return Math.max(Math.abs(max), Math.abs(min));
    }

    // 绝对值最大的子数组会导致前缀和出现最大的变化，而前缀和最大值和最小值的差值最大
    public int maxAbsoluteSum_implementation2(int[] nums) {
        int max = 0, min = 0; // 初值为0，可能nums全正全负
        int sum = 0;
        for (int i = 0; i < nums.length; i++) {
            sum += nums[i];
            max = Math.max(max, sum);
            min = Math.min(min, sum);
        }
        return Math.abs(max - min);
    }

    public static void main(String[] args) {
        Solution1749 solu = new Solution1749();
        System.out.println(solu.maxAbsoluteSum(new int[]{1, -5, 6}));
        System.out.println(solu.maxAbsoluteSum_implementation2(new int[]{1, -5, 6}));
    }
}