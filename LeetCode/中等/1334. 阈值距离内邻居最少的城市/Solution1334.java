/*
url: https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/?envType=daily-question&envId=2023-11-14
LeetCode参考: https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/solutions/98401/yu-zhi-ju-chi-nei-lin-ju-zui-shao-de-cheng-shi-flo/
标签: 最短路径, Floyd算法
*/

import java.util.Arrays;

public class Solution1334 {
    public int findTheCity(int n, int[][] edges, int distanceThreshold) {
        int[][] D = new int[n][n];
        for (int[] arr : D) Arrays.fill(arr, Integer.MAX_VALUE);
        for (int i = 0; i < n; i++) D[i][i] = 0;
        for (int[] edge : edges) {
            D[edge[0]][edge[1]] = edge[2];
            D[edge[1]][edge[0]] = edge[2];
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // 用k节点做松弛
                    if (i != k && j != k && D[i][k] != Integer.MAX_VALUE && D[k][j] != Integer.MAX_VALUE) {
                        D[i][j] = Math.min(D[i][j], D[i][k] + D[k][j]);
                    }
                }
            }
        }
        int ans = -1;
        int minCount = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (D[i][j] <= distanceThreshold) {
                    count++;
                }
            }
            if (count <= minCount) {
                ans = i;
                minCount = count;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1334 solu = new Solution1334();
        System.out.println(solu.findTheCity(4, new int[][]{{0,1,3},{1,2,1},{1,3,4},{2,3,1}}, 4));
    }
}
