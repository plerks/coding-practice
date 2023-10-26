/*
url: https://leetcode.cn/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/?envType=daily-question&envId=2023-10-27
相关: LeetCode695. 岛屿的最大面积
*/

import java.util.Arrays;

// 这题可以看作LeetCode695. 岛屿的最大面积的特殊情况，只是因为切的方式规则不需要dfs
public class Solution1465 {
    // 找出两个方向切出的最大间隔并相乘
    public int maxArea(int h, int w, int[] horizontalCuts, int[] verticalCuts) {
        int[] hGaps = new int[horizontalCuts.length + 1];
        int[] vGaps = new int[verticalCuts.length + 1];
        Arrays.sort(horizontalCuts);
        Arrays.sort(verticalCuts);
        int max1 = Integer.MIN_VALUE, max2 = Integer.MIN_VALUE;
        for (int i = 0; i < hGaps.length; i++) {
            int y1 = i - 1 < 0 ? 0 : horizontalCuts[i - 1];
            int y2 = i == horizontalCuts.length ? h : horizontalCuts[i];
            hGaps[i] = y2 - y1;
            max1 = Math.max(max1, hGaps[i]);
        }
        for (int i = 0; i < vGaps.length; i++) {
            int x1 = i - 1 < 0 ? 0 : verticalCuts[i - 1];
            int x2 = i == verticalCuts.length ? w : verticalCuts[i];
            vGaps[i] = x2 - x1;
            max2 = Math.max(max2, vGaps[i]);
        }
        int mod = (int)(1e9 + 7);
        return (int)(((long)max1 * max2) % mod);
    }

    // 优化空间使用
    public int maxArea_implementation2(int h, int w, int[] horizontalCuts, int[] verticalCuts) {
        Arrays.sort(horizontalCuts);
        Arrays.sort(verticalCuts);
        int max1 = Integer.MIN_VALUE, max2 = Integer.MIN_VALUE;
        for (int i = 1; i < horizontalCuts.length; i++) {
            max1 = Math.max(max1, horizontalCuts[i] - horizontalCuts[i - 1]);
        }
        max1 = Math.max(max1, horizontalCuts[0] - 0);
        max1 = Math.max(max1, h - horizontalCuts[horizontalCuts.length - 1]);
        for (int i = 1; i < verticalCuts.length; i++) {
            max2 = Math.max(max2, verticalCuts[i] - verticalCuts[i - 1]);
        }
        max2 = Math.max(max2, verticalCuts[0] - 0);
        max2 = Math.max(max2, w - verticalCuts[verticalCuts.length - 1]);
        int mod = (int)(1e9 + 7);
        return (int)(((long)max1 * max2) % mod);
    }

    public static void main(String[] args) {
        Solution1465 solu = new Solution1465();
        System.out.println(solu.maxArea(5, 4, new int[]{1,2,4}, new int[]{1,3}));
        System.out.println(solu.maxArea_implementation2(5, 4, new int[]{1,2,4}, new int[]{1,3}));
    }
}
