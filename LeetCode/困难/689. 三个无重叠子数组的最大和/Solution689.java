/*
url: https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/?envType=daily-question&envId=2023-11-19
LeetCode参考: https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/solutions/1145000/san-ge-wu-zhong-die-zi-shu-zu-de-zui-da-4a8lb/
              https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/solutions/1145272/gong-shui-san-xie-jie-he-qian-zhui-he-de-ancx/
标签: 滑动窗口, 动态规划
*/

import java.util.Arrays;

public class Solution689 {

    // 暴力法，超时
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        int n = nums.length;
        int[] ans = new int[]{-1, -1, -1};
        int max = -1;
        int[] prefixSum = new int[n];
        prefixSum[0] = nums[0];
        for (int i = 1; i < n; i++) prefixSum[i] = prefixSum[i - 1] + nums[i];
        for (int i = 0; i + k - 1 < n; i++) {
            for (int j = i + k; j + k - 1 < n; j++) {
                for (int z = j + k; z + k - 1 < n; z++) {
                    int subSum1 = prefixSum[i + k - 1] - (i - 1 >= 0 ? prefixSum[i - 1] : 0);
                    int subSum2 = prefixSum[j + k - 1] - (j - 1 >= 0 ? prefixSum[j - 1] : 0);
                    int subSum3 = prefixSum[z + k - 1] - (z - 1 >= 0 ? prefixSum[z - 1] : 0);
                    if (subSum1 + subSum2 + subSum3 > max) {
                        max = subSum1 + subSum2 + subSum3;
                        ans[0] = i;
                        ans[1] = j;
                        ans[2] = z;
                    }
                }
            }
        }
        return ans;
    }

    // 用3个滑动窗口
    public int[] maxSumOfThreeSubarrays_implementation2(int[] nums, int k) {
        int n = nums.length;
        int sum1 = 0, maxSum1 = 0, maxSum1Index = 0;
        int sum2 = 0, maxSum12 = 0, maxSum12Index1 = 0, maxSum12Index2 = k;
        int sum3 = 0, maxSum123 = 0;
        for (int i = 0; i < k; i++) {
            sum1 += nums[i];
            sum2 += nums[i + k];
            sum3 += nums[i + 2 * k];
        }
        maxSum1 = sum1;
        maxSum12 = sum1 + sum2;
        maxSum123 = sum1 + sum2 + sum3;
        int[] ans = new int[]{0, k, 2 * k};
        for (int i = 3 * k; i < n; i++) {
            sum1 = sum1 + nums[i - 2 * k] - nums[i - 3 * k];
            sum2 = sum2 + nums[i - k] - nums[i - 2 * k];
            sum3 = sum3 + nums[i] - nums[i - k];
            if (sum1 > maxSum1) {
                maxSum1 = sum1;
                maxSum1Index = i - 3 * k + 1;
            }
            // 对sum2，maxSum1对应的子数组一定是在sum2左侧的子数组的最大值，可以用起来计算新的maxSum12
            if (maxSum1 + sum2 > maxSum12) {
                maxSum12 = maxSum1 + sum2;
                maxSum12Index1 = maxSum1Index;
                maxSum12Index2 = i - 2 * k + 1;
            }
            if (maxSum12 + sum3 > maxSum123) {
                maxSum123 = maxSum12 + sum3;
                ans[0] = maxSum12Index1;
                ans[1] = maxSum12Index2;
                ans[2] = i - k + 1;
            }
        }
        return ans;
    }

    // [官方题解](https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/solutions/1145000/san-ge-wu-zhong-die-zi-shu-zu-de-zui-da-4a8lb/)的写法
    public int[] maxSumOfThreeSubarrays_implementation3(int[] nums, int k) {
        int n = nums.length;
        int sum1 = 0, maxSum1 = 0, maxSum1Index = 0;
        int sum2 = 0, maxSum12 = 0, maxSum12Index1 = 0, maxSum12Index2 = 0;
        int sum3 = 0, maxSum123 = 0;
        int[] ans = new int[3];
        for (int i = 2 * k; i < n; i++) {
            sum1 = sum1 + nums[i - 2 * k];
            sum2 = sum2 + nums[i - k];
            sum3 = sum3 + nums[i];
            if (i >= 3 * k - 1) {
                if (sum1 > maxSum1) {
                    maxSum1 = sum1;
                    maxSum1Index = i - 3 * k + 1;
                }
                if (maxSum1 + sum2 > maxSum12) {
                    maxSum12 = maxSum1 + sum2;
                    maxSum12Index1 = maxSum1Index;
                    maxSum12Index2 = i - 2 * k + 1;
                }
                if (maxSum12 + sum3 > maxSum123) {
                    maxSum123 = maxSum12 + sum3;
                    ans[0] = maxSum12Index1;
                    ans[1] = maxSum12Index2;
                    ans[2] = i - k + 1;
                }
                sum1 = sum1 - nums[i - 3 * k + 1];
                sum2 = sum2 - nums[i - 2 * k + 1];
                sum3 = sum3 - nums[i - k + 1];
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution689 solu = new Solution689();
        System.out.println(Arrays.toString(solu.maxSumOfThreeSubarrays(new int[]{1,2,1,2,6,7,5,1}, 2)));
        System.out.println(Arrays.toString(solu.maxSumOfThreeSubarrays_implementation2(new int[]{1,2,1,2,6,7,5,1}, 2)));
        System.out.println(Arrays.toString(solu.maxSumOfThreeSubarrays_implementation3(new int[]{1,2,1,2,6,7,5,1}, 2)));
    }
}
