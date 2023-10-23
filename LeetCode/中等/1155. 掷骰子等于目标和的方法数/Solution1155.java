/*
url: https://leetcode.cn/problems/number-of-dice-rolls-with-target-sum/?envType=daily-question&envId=2023-10-24
相关: /典型问题/投n个骰子点数之和大于等于x的概率
标签: 掷骰子, 点数之和
*/

public class Solution1155 {
    private int ans = 0;

    // 递归会超时
    public int numRollsToTarget_exceed_time_limit(int n, int k, int target) {
        if (n == 1) {
            if (1 <= target && target <= k) return 1;
            return 0;
        }
        for (int i = 1; i <= k; i++) {
            ans += numRollsToTarget(n - 1, k, target - i);
        }
        return ans % (int)(1e9 + 7);
    }

    public int numRollsToTarget(int n, int k, int target) {
        int mod = (int)(1e9 + 7);
        int[][] dp = new int[n + 1][target + 1];
        for (int j = 1; j <= target; j++) {
            if (j <= k) dp[1][j] = 1;
            else dp[1][j] = 0;
        }
        // 因为是等于，这里的循环相对`/典型问题/投n个骰子点数之和大于等于x的概率`中的循环有所不同
        for (int i = 2; i <= n; i++) {
            for (int j = i; j <= target; j++) {
                for (int z = 1; z <= k && j - z >= 1; z++) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - z]) % mod;
                }
                
            }
        }
        return dp[n][target];
    }

    public static void main(String[] args) {
        Solution1155 solu = new Solution1155();
        System.out.println(solu.numRollsToTarget(30, 30, 500));
    }
}
