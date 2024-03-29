/*
描述: 使用Floyd算法求最短路径条数，这里求出0号节点到n-1号节点的最短路径的条数
相关: LeetCode1976. 到达目的地的方案数
*/

import java.util.*;

public class ShortestPathCountFloyd {
    public int shortestPathCount(int n, int[][] edges) {
        if (0 == n - 1) return 1; // 单独判断一次，LeetCode1976有个用例n==1，roads=[]，要求返回1，这里也这样来，不过感觉返回0更合适
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        int[][] dis = new int[n][n]; // 记录两点之间的最短距离
        int[][] count = new int[n][n]; // 记录两点之间的最短路径数
        for (int[] arr : dis) Arrays.fill(arr, Integer.MAX_VALUE);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph.get(i).size(); j++) {
                int u = i, v = graph.get(i).get(j)[0], w = graph.get(i).get(j)[1];
                dis[u][v] =  w;
                count[u][v] = 1;
                dis[v][u] = w;
                count[v][u] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            dis[i][i] = 0;
            /* 这里假定没有自环，不过就算有自环，只要自环权重为正，这里让count[i][i]=0也不影响结果，因为最短路径不会走自环。
            若自环权重为0，则这里单纯让count[i][i]=0会影响结果，因为无限走自环路径权重不变。 */
            count[i][i] = 0;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dis[i][k] != Integer.MAX_VALUE && dis[k][j] != Integer.MAX_VALUE && dis[i][k] + dis[k][j] < dis[i][j]) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                        count[i][j] = count[i][k] * count[k][j];
                    }
                    else if (dis[i][k] + dis[k][j] == dis[i][j]) {
                        count[i][j] = count[i][j] + count[i][k] * count[k][j];
                    }
                }
            }
        }
        return count[0][n - 1];
    }
    public static void main(String[] args) {
        ShortestPathCountFloyd spcf = new ShortestPathCountFloyd();
        System.out.println("0到n-1的最短路径条数: " + spcf.shortestPathCount(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));
    }
}
