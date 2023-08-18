/*
url: https://leetcode.cn/problems/pizza-with-3n-slices/
LeetCode参考: https://leetcode.cn/problems/pizza-with-3n-slices/solutions/177086/3n-kuai-pi-sa-by-leetcode-solution/
相关: https://leetcode.cn/problems/house-robber-ii/
标签: 动态规划, 不相邻取数
*/

import java.util.*;

public class Solution1388 {
    // 递归的解法会超时
    public int maxSizeSlices(int[] slices) {
        int ans = 0;
        for (int i = 0; i < slices.length; i++) {
            ans = Math.max(ans, calculate(slices, i));
        }
        return ans;
    }

    private int calculate(int[] slices, int start) {
        if (slices[start] == -1) return 0;
        int sliceStart = 0, sliceAlice = 0, sliceBob = 0;
        int ans = slices[start];
        sliceStart = slices[start];
        slices[start] = -1;
        // Alice选披萨
        int aliceI = (start - 1 + slices.length) % slices.length;
        for (; aliceI != start; aliceI = (aliceI - 1 + slices.length) % slices.length) {
            if (slices[aliceI] != -1) {
                sliceAlice = slices[aliceI];
                slices[aliceI] = -1;
                break;
            }
        }
        if (aliceI == start) {
            slices[start] = sliceStart;
            return ans;
        }
        // Bob选披萨
        int bobI = (start + 1) % slices.length;
        for (; bobI != start; bobI = (bobI - 1 + slices.length) % slices.length) {
            if (slices[bobI] != -1) {
                sliceBob = slices[bobI];
                slices[bobI] = -1;
                break;
            }
        }
        if (bobI == start) {
            slices[start] = sliceStart;
            slices[aliceI] = sliceAlice;
            return ans;
        }
        int max = 0;
        for (int i = 0; i < slices.length; i++) {
            max = Math.max(max, calculate(slices, i));
        }
        slices[start] = sliceStart;
        slices[aliceI] = sliceAlice;
        slices[bobI] = sliceBob;
        return ans + max;
    }

    public int maxSizeSlices_implementation2(int[] slices) {
        int[] s1 = new int[slices.length - 1];
        int[] s2 = new int[slices.length - 1];
        for (int i = 0; i < slices.length - 1; i++) {
            s1[i] = slices[i + 1];
        }
        for (int i = 0; i < slices.length - 1; i++) {
            s2[i] = slices[i];
        }
        return Math.max(doDp(s1), doDp(s2));
    }

    private int doDp(int[] slices) {
        // dp[i][j]表示从[0..i]中选j个不相邻的，所得的最大值
        int[][] dp = new int[slices.length][(slices.length + 1) / 3 + 1]; // slices.length + 1是题上的3n
        for (int i = 0; i < dp.length; i++){
            // 便于区分dp初值
            Arrays.fill(dp[i], Integer.MIN_VALUE);
        }
        dp[0][0] = 0;
        dp[0][1] = slices[0];
        dp[1][0] = 0;
        dp[1][1] = Math.max(slices[0], slices[1]);
        for (int i = 2; i < dp.length; i++) {
            dp[i][0] = 0;
            for (int j = 1; j < dp[0].length; j++) {
                dp[i][j] = Math.max(dp[i - 1][j], dp[i - 2][j - 1] + slices[i]);
            }
        }
        return dp[slices.length - 1][(slices.length + 1) / 3];
    }

    public static void main(String[] args) {
        Solution1388 solu = new Solution1388();
        System.out.println(solu.maxSizeSlices_implementation2(new int[]{1,2,3,4,5,6}));
    }
}