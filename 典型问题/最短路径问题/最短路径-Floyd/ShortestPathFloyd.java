/*
描述: Floyd-Warshall算法，解决所有结点对最短路径问题。负权重的边可以存在，但不能存在权重为负值的环路。
相关: LeetCode1334. 阈值距离内邻居最少的城市, LeetCode1462. 课程表 IV, LeetCode1976. 到达目的地的方案数
*/

import java.util.*;

public class ShortestPathFloyd {
    public int[][] shortestPath(int n, int[][] graph) {
        int[][] D = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                D[i][j] = graph[i][j];
            }
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
        return D;
    }

    public static void main(String[] args) {
        ShortestPathFloyd spf = new ShortestPathFloyd();
        int n = 5;
        int[][] graph = new int[n][n];
        for (int[] arr : graph) {
            Arrays.fill(arr, Integer.MAX_VALUE);
        }
        graph[0][1] = 4;
        graph[0][3] = 2;
        graph[1][2] = 4;
        graph[1][3] = 1;
        graph[2][3] = 1;
        graph[2][4] = 3;
        graph[3][4] = 7;
        graph[1][0] = 4;
        graph[3][0] = 2;
        graph[2][1] = 4;
        graph[3][1] = 1;
        graph[3][2] = 1;
        graph[4][2] = 3;
        graph[4][3] = 7;
        for (int i = 0; i < n; i++) graph[i][i] = 0;
        int[][] dis = spf.shortestPath(5, graph);
        System.out.println("0号节点到4号节点的最短路径长度: " + dis[0][4]);
    }
}
