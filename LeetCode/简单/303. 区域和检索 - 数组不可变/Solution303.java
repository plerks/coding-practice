/*
url: https://leetcode.cn/problems/range-sum-query-immutable/description/?envType=daily-question&envId=2024-03-18
相关: LeetCode304. 二维区域和检索 - 矩阵不可变, LeetCode2132. 用邮票贴满网格图
标签: 前缀和
*/

public class Solution303 {
    int[] prefixSum;
    int[] nums;

    // 粘贴到LeetCode上把这个方法名改为NumArray
    public Solution303(int[] nums) {
        int n = nums.length;
        this.nums = nums;
        this.prefixSum = new int[n];
        for (int i = 0; i < n; i++) {
            prefixSum[i] = (i == 0) ? nums[i] : nums[i] + prefixSum[i - 1];
        }
    }
    
    public int sumRange(int left, int right) {
        return prefixSum[right] - prefixSum[left] + nums[left];
    }

    public static void main(String[] args) {
        Solution303 solu = new Solution303(new int[]{-2, 0, 3, -5, 2, -1});
        System.out.println(solu.sumRange(0, 2));
    }
}
