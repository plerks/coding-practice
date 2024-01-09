/*
url: https://leetcode.cn/problems/extra-characters-in-a-string/description/?envType=daily-question&envId=2024-01-09
LeetCode参考: https://leetcode.cn/problems/extra-characters-in-a-string/solutions/2286613/dong-tai-gui-hua-cong-ji-yi-hua-sou-suo-wtd7a/
标签: 动态规划
*/

import java.util.HashSet;

public class Solution2707 {
    public int minExtraChar(String s, String[] dictionary) {
        HashSet<String> set = new HashSet<>();
        for (String word : dictionary) set.add(word);
        int n = s.length();
        int[] dp = new int[n]; // dp[i]表示考虑s[0...i]的情况下得出的最小值
        if (set.contains(String.valueOf(s.charAt(0)))) {
            dp[0] = 0;
        }
        else dp[0] = 1;
        for (int i = 1; i < n; i++) {
            dp[i] = dp[i - 1] + 1; // s.charAt(i)不被选
            // s.charAt(i)被选，枚举被选出来的是哪个word
            for (int j = 0; j <= i; j++) {
                if (set.contains(s.substring(j, i + 1))) {
                    dp[i] = Math.min(dp[i], j - 1 < 0 ? 0 : dp[j - 1]);
                }
            }
        }
        return dp[n - 1];
    }

    public static void main(String[] args) {
        Solution2707 solu = new Solution2707();
        System.out.println(solu.minExtraChar("leetscode", new String[]{"leet","code","leetcode"}));
    }
}
