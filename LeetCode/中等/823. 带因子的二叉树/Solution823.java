/*
url: https://leetcode.cn/problems/binary-trees-with-factors/
LeetCode参考: https://leetcode.cn/problems/binary-trees-with-factors/solutions/2414616/dai-yin-zi-de-er-cha-shu-by-leetcode-sol-0082/
标签: 动态规划
*/

import java.util.Arrays;

public class Solution823 {
    public int numFactoredBinaryTrees(int[] arr) {
        long[] dp = new long[arr.length];
        int mod = 1000000007;
        long ans = 0;
        Arrays.sort(arr);
        Arrays.fill(dp, 1);
        for (int i = 0; i < arr.length; i++) {
            int left = 0, right = i - 1;
            while (left <= right) {
                if ((long)arr[left] * arr[right] < arr[i]) {
                    left++;
                }
                else if ((long)arr[left] * arr[right] > arr[i]) {
                    right--;
                }
                else {
                    if (left == right) {
                        dp[i] = (dp[i] + (dp[left] * dp[right])) % mod;
                    }
                    else {
                        dp[i] = (dp[i] + (dp[left] * dp[right]) * 2) % mod;
                    }
                    left++;
                }
            }
            ans = (ans + dp[i]) % mod;
        }
        return (int)ans;
    }

    public static void main(String[] args) {
        Solution823 solu = new Solution823();
        System.out.println(solu.numFactoredBinaryTrees(new int[]{18865777,36451879,36878647}));
    }
}