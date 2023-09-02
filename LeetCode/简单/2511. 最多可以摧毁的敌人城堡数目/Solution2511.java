/*
url: https://leetcode.cn/problems/maximum-enemy-forts-that-can-be-captured/?envType=daily-question&envId=2023-09-02
LeetCode题解: https://leetcode.cn/problems/maximum-enemy-forts-that-can-be-captured/solutions/2393779/zui-duo-ke-yi-cui-hui-de-di-ren-cheng-ba-5qmc/
标签: 动态规划, 双动态规划, 连续数量
相关: https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
*/

public class Solution2511 {
    public int captureForts(int[] forts) {
        // dp1[i]表示从i-1往左连续的0的数量
        int[] dp1 = new int[forts.length];
        // dp2[i]表示从i+1往右连续的0的数量
        int[] dp2 = new int[forts.length];
        dp1[0] = 0;
        for (int i = 1; i < dp1.length; i++) {
            dp1[i] = forts[i - 1] == 0 ? dp1[i - 1] + 1 : 0;
        }
        dp2[dp2.length - 1] = 0;
        for (int i = dp2.length - 2; i >= 0; i--) {
            dp2[i] = forts[i + 1] == 0 ? dp2[i + 1] + 1 : 0;
        }
        int ans = 0;
        for (int i = 0; i < forts.length; i++) {
            if (forts[i] == 1) {
                if (dp1[i] > 0 && i - dp1[i] - 1 >= 0 && forts[i - dp1[i] - 1] == -1) {
                    ans = Math.max(ans, dp1[i]);
                }
                if (dp2[i] > 0 && i + dp2[i] + 1 < forts.length && forts[i + dp2[i] + 1] == -1) {
                    ans = Math.max(ans, dp2[i]);
                }
            }
        }
        return ans;
    }

    public int captureForts_implementation2(int[] forts) {
        int ans = 0;
        int pre = -1;
        // 可选的路是从1/-1走到-1/1，中间全是0
        for (int i = 0; i < forts.length; i++) {
            if (forts[i] == 1 || forts[i] == -1) {
                if (pre >= 0 && forts[i] != forts[pre]) {
                    ans = Math.max(ans, i - pre - 1);
                }
                pre = i;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2511 solu = new Solution2511();
        System.out.println(solu.captureForts(new int[]{1,0,0,-1,0,0,0,0,1}));
    }
}