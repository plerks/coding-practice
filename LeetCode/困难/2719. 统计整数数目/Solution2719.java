/*
url: https://leetcode.cn/problems/count-of-integers/description/?envType=daily-question&envId=2024-01-16
LeetCode参考: https://leetcode.cn/problems/count-of-integers/solutions/2601111/tong-ji-zheng-shu-shu-mu-by-leetcode-sol-qxqd/
              https://leetcode.cn/problems/count-of-integers/solutions/2296043/shu-wei-dp-tong-yong-mo-ban-pythonjavacg-9tuc/
标签: 数位dp问题, 记忆化搜索
相关: 典型问题/投n个骰子点数之和大于等于x的概率
*/

import java.util.Arrays;

public class Solution2719 {
    int mod = 1000000007;

    int min_sum;

    int max_sum;

    int[][] memo;

    int M = 23, N = 401;

    /* 这题和"典型问题/投n个骰子点数之和大于等于x的概率"有些相似，但是要在计算数位和的同时控制填出的数<=num，
    因此记忆化搜索的时候直接只记了limit为false的情况下的种数。
    */
    public int count(String num1, String num2, int min_sum, int max_sum) {
        this.min_sum = min_sum;
        this.max_sum = max_sum;
        int ans = ((getCount(num2) - getCount(num1)) + mod) % mod;
        // 现在ans是(num1, num2]范围内符合数位和在[min_sum, max_sum]的，单独判断num1，参考题解的方式是getCount(num2) - getCount(num1 - 1)，这里num1是字符串所以计算num1 - 1要麻烦一点
        int digitSum = 0;
        for (int i = 0; i < num1.length(); i++) {
            digitSum += num1.charAt(i) - '0';
        }
        if (digitSum >= min_sum && digitSum <= max_sum) ans++;
        return ans % mod;
    }

    // 求在[0, hi]之间，数位和[min_sum, max_sum]的元素个数
    private int getCount(String num) {
        this.memo = new int[M][N]; // memo[i][j]表示已填了i位的情况下，数位和为j的情况种数（limit为false的情况下）
        for (int i = 0; i < M; i++) {
            Arrays.fill(memo[i], -1);
        }
        return dfs(num, 0, 0, true);
    }

    // i表示已经填了的位数，j为当前数位和，limit表示未填的位是否可以任意取，当已填的前缀与num完全相同时，后续不能随便填0~9，否则会>num
    private int dfs(String num, int i, int j, boolean limit) {
        if (j > max_sum) {
            return 0;
        }
        if (i == num.length()) { // 所有位都填了，这时要看j是否在[min_sum, max_sum]决定填好的数是否可用
            return j >= min_sum ? 1 : 0;
        }
        if (!limit && memo[i][j] != -1) {
            return memo[i][j];
        }
        int up = limit ? num.charAt(i) - '0' : 9;
        int ans = 0;
        for (int x = 0; x <= up; x++) {
            ans = (ans + dfs(num, i + 1, j + x, limit && x == up)) % mod;
        }
        if (!limit) {
            memo[i][j] = ans;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2719 solu = new Solution2719();
        // System.out.println(solu.count("1", "12", 1, 8));
        // System.out.println(solu.count("4179205230", "7748704426", 8, 46));
        System.out.println(solu.count("4859473643", "30159981595", 58, 59));
    }
}
