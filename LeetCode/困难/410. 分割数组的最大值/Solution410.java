/*
url: https://leetcode.cn/problems/split-array-largest-sum/description/?envType=daily-question&envId=2024-01-21
LeetCode参考: https://leetcode.cn/problems/split-array-largest-sum/solutions/345417/fen-ge-shu-zu-de-zui-da-zhi-by-leetcode-solution/
标签: 动态规划, 二分查找, 贪心
*/

import java.util.Arrays;

public class Solution410 {
    // 我的做法
    public int splitArray(int[] nums, int k) {
        int n = nums.length;
        // dp[i][j]表示用前i个元素分割出j个连续的非空子数组
        // dp[i][j] = min{max(dp[i-z][j-1], sum[i-z+1,i])}，z>=1（枚举最后一段的位置）
        int[][] dp = new int[n + 1][k + 1];
        for (int i = 0; i < n + 1; i++) Arrays.fill(dp[i], Integer.MAX_VALUE);
        int[] prefixSum = new int[n + 1];
        for (int i = 1; i < n + 1; i++) {
            prefixSum[i] = nums[i - 1] + prefixSum[i - 1];
        }
        for (int j = 0; j < k + 1; j++) {
            dp[0][j] = 0;
        }
        for (int i = 1; i < n + 1; i++) {
            dp[i][0] = 0;
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < k + 1; j++) {
                for (int z = 1; i - z >= j - 1; z++) { // i - z >= j - 1的原因是要分成j - 1段，由于每段非空，则至少要有i - z个元素
                    if (j == 1) {
                        dp[i][j] = prefixSum[i];
                    }
                    else dp[i][j] = Math.min(dp[i][j], Math.max(dp[i - z][j - 1], prefixSum[i] - prefixSum[i - z]));
                }
            }
        }
        return dp[n][k];
    }

    // 参考题解的做法，dp的逻辑比我更清晰
    public int splitArray_implementation2(int[] nums, int k) {
        int n = nums.length;
        int[][] dp = new int[n + 1][k + 1]; // dp[i][j]只会用i>=j的部分，因为每段非空，分割为j段则至少要有j个元素，即i>=j
        for (int i = 0; i < n + 1; i++) Arrays.fill(dp[i], Integer.MAX_VALUE);
        int[] prefixSum = new int[n + 1];
        for (int i = 1; i < n + 1; i++) {
            prefixSum[i] = nums[i - 1] + prefixSum[i - 1];
        }
        dp[0][0] = 0;
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j <= Math.min(i, k); j++) { // i个元素，由于每段非空，最多只能分为i段
                for (int z = 1; z <= i; z++) { // 枚举最后一段的开始是第几个元素，最后一段从第z个元素到第i个元素
                    dp[i][j] = Math.min(dp[i][j], Math.max(dp[z - 1][j - 1], prefixSum[i] - prefixSum[z - 1]));
                }
            }
        }
        return dp[n][k];
    }

    /* 参考题解的另一种做法，使用二分。
    对于值x，可以线性地验证是否存在一种k分割方式使得最大的分割子数组和<=x，从而可以二分x的范围，x的初始范围为nums的最大值~nums的和。
    验证方法使用贪心策略，从左到右遍历nums，在子数组和小于等于x时将nums[i]加入子数组，若大于x，则新起一个子数组，最后判断生成的子数组数量是否<=k
    */
    public int splitArray_implementation3(int[] nums, int k) {
        int left = 0, right = 0;
        for (int val : nums) {
            right += val;
            left = Math.max(left, val);
        }
        // 有序区间从否到是，二分搜索第一个'是'，即搜索最后一个'否'再加1
        while (left < right) {
            int mid = (left + right) / 2;
            if (!check(nums, mid, k)) {
                left = mid + 1;
            }
            else right = mid;
        }
        return left - 1 + 1;
    }

    public boolean check(int[] nums, int x, int k) {
        int sum = 0, count = 1;
        for (int i = 0; i < nums.length; i++) {
            if (sum + nums[i] > x) {
                sum = nums[i];
                count++;
            }
            else sum += nums[i];
        }
        return count <= k; // 若count<=k，则回答是'是'，否则为'否'
    }

    public static void main(String[] args) {
        Solution410 solu = new Solution410();
        System.out.println(solu.splitArray(new int[]{7,2,5,10,8}, 2));
        System.out.println(solu.splitArray_implementation2(new int[]{7,2,5,10,8}, 2));
        System.out.println(solu.splitArray_implementation3(new int[]{7,2,5,10,8}, 2));
    }
}
