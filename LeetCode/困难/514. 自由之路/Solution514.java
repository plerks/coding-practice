/*
url: https://leetcode.cn/problems/freedom-trail/description/?envType=daily-question&envId=2024-01-29
LeetCode参考: https://leetcode.cn/problems/freedom-trail/solutions/480315/zi-you-zhi-lu-by-leetcode-solution/
标签: 动态规划
*/

import java.util.*;

public class Solution514 {
    // 我的做法，递归枚举每步的可能情况，时间复杂度O(2^key.length())，用例超时，而且里面用的贪心策略不一定对
    public int findRotateSteps(String ring, String key) {
        int n = ring.length();
        int[][] disL = new int[n][26]; // disL[i][c]记录i号位置往左走(逆时针)到达字母c的最短距离
        for (int[] arr : disL) Arrays.fill(arr, 10000);
        disL[0][ring.charAt(0) - 'a'] = 0;
        for (int i = n - 1; i > 0; i--) {
            char c = ring.charAt(i);
            disL[0][c - 'a'] = Math.min(disL[0][c - 'a'], n - 1 - i + 1);
        }
        for (int i = 1; i < n; i++) {
            disL[i][ring.charAt(i) - 'a'] = 0;
            for (int j = 0; j < 26; j++) {
                disL[i][j] = Math.min(disL[i][j], disL[i - 1][j] + 1); // 先向左走到i - 1的位置，i到某个字符的最短距离为disL[i - 1][j]再加1
            }
        }
        int[][] disR = new int[n][26];
        for (int[] arr : disR) Arrays.fill(arr, 10000);
        disR[n - 1][ring.charAt(n - 1) - 'a'] = 0;
        for (int i = 0; i < n - 1; i++) {
            char c = ring.charAt(i);
            disR[n - 1][c - 'a'] = Math.min(disR[n - 1][c - 'a'], i + 1);
        }
        for (int i = n - 2; i >= 0; i--) {
            disR[i][ring.charAt(i) - 'a'] = 0;
            for (int j = 0; j < 26; j++) {
                disR[i][j] = Math.min(disR[i][j], disR[i + 1][j] + 1); // 先向右走到i + 1的位置，i到某个字符的最短距离为disL[i + 1][j]再加1
            }
        }
        // 每次可以选择往左或者往右拨，但是一定是拨动到相距最近的字符位置，否则，拨动到相距最近的字符位置的方案一定不会比最优解差，因为可以先拨动到最近再拨动到最优解想要的位置
        // 又想了下，这样贪心可能不一定对，虽然这一步相对最优解的步数更小或者相等，但是这一轮走完之后贪心和最优解达到的状态不一样，应该还是要进行规划
        return dfs(0, disL, disR, ring, key, 0);
    }

    private int dfs(int pos, int[][] disL, int[][] disR, String ring, String key, int step) {
        if (key.length() == 0) return step;
        int n = ring.length();
        char c = key.charAt(0);

        int newPos1 = (pos - disL[pos][c - 'a'] + n) % n;
        int total1 = dfs(newPos1, disL, disR, ring, key.substring(1), step + disL[pos][c - 'a'] + 1);

        int newPos2 = (pos + disR[pos][c - 'a']) % n;
        int total2 = dfs(newPos2, disL, disR, ring, key.substring(1), step + disR[pos][c - 'a'] + 1);

        return Math.min(total1, total2);
    }

    public int findRotateSteps_implementation2(String ring, String key) {
        int n = ring.length(), m = key.length();
        int[][] dp = new int[m][n]; // dp[i][j]表示对好key的[0,i]范围的字符，ring的位置在j位置的最小步数
        for (int[] arr : dp) Arrays.fill(arr, 10000); // 1 <= ring.length, key.length <= 100，10000当无穷用 
        List<List<Integer>> pos = new ArrayList<>(26); // pos用来记录ring中每个字符出现的位置
        for (int i = 0; i < 26; i++) pos.add(new ArrayList<>());
        for (int i = 0; i < n; i++) {
            pos.get(ring.charAt(i) - 'a').add(i);
        }
        for (int j : pos.get(key.charAt(0) - 'a')) {
            dp[0][j] = Math.min(j, n - j) + 1;
        }
        // dp[i][j]转移方式: 找key[i-1]所在的位置和key[i]所在的位置，从key[i-1]所在的位置跳到key[i]所在的位置，再算上按按钮的步数
        for (int i = 1; i < m; i++) {
            for (int j : pos.get(key.charAt(i) - 'a')) {
                for (int k : pos.get(key.charAt(i - 1) - 'a')) {
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][k] + Math.min(Math.abs(k - j), n - Math.abs(k - j)) + 1);
                }
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int j = 0; j < n; j++) {
            ans = Math.min(ans, dp[m - 1][j]);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution514 solu = new Solution514();
        // System.out.println(solu.findRotateSteps("godding", "gd"));

        // 这个用例会超时
        // System.out.println(solu.findRotateSteps("xrrakuulnczywjs", "jrlucwzakzussrlckyjjsuwkuarnaluxnyzcnrxxwruyr"));
        
        System.out.println(solu.findRotateSteps_implementation2("godding", "gd"));
    }
}
