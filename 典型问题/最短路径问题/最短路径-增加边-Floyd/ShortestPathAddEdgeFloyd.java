/*
描述: 此题为LeetCode2642. 设计可以求最短路径的图类，相比一般的查询点对间最短路径，增加了可能增加图中的边的需求
相关: LeetCode2642. 设计可以求最短路径的图类
*/

import java.util.*;

public class ShortestPathAddEdgeFloyd {
    int n;
    int[][] D;

    public ShortestPathAddEdgeFloyd(int n, int[][] edges) {
        this.n = n;
        this.D = new int[n][n];
        for (int[] arr : D) Arrays.fill(arr, Integer.MAX_VALUE);
        for (int[] edge : edges) {
            D[edge[0]][edge[1]] = edge[2];
        }
        for (int i = 0; i < n; i++) D[i][i] = 0;
        // Floyd算法
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // 用k做松弛
                    if (D[i][k] != Integer.MAX_VALUE && D[k][j] != Integer.MAX_VALUE && D[i][k] + D[k][j] < D[i][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }
    }

    /* 由于是任意点对间的最短路径，用Floyd算法，然后主要的点是如何在加边之后快速计算新的任意点对最短路径。
    i，j之间多了一条边，对于点对x，y，若增加这条边后能使x，y间的最短距离缩小，则说明简单路径x -> i -> j -> y的距离更小，
    而这里x -> i和y -> j都一定是旧边，因此只需O(n^2)时间就能计算出加边之后点对间的最小距离。

    这题如果还能删除边的话好像删边之后就没法O(n^2)时间计算点对最小距离，得O(n^3)重新算一遍。
    */
    public void addEdge(int[] edge) {
        int i = edge[0], j = edge[1], w = edge[2];
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                if (D[x][i] != Integer.MAX_VALUE && D[j][y] != Integer.MAX_VALUE && D[x][i] + w + D[j][y] < D[x][y]) {
                    D[x][y] = D[x][i] + w + D[j][y];
                }
            }
        }
    }

    public int shortestPath(int node1, int node2) {
        return D[node1][node2] == Integer.MAX_VALUE ? -1 : D[node1][node2];
    }

    /* LeetCode2642官方题解有个另外的用Dijkstra的解法，addEdge()时不重新计算最短路径，仅仅将边加入邻接表，然后shortestPath()查询时直接用
    Dijkstra算一遍node1到node2的最短距离。如果频繁shortedPath()查询而很少加边应该用Floyd，如果频繁加边而很少shortedPath()查询应该用Dijkstra
    */

    public static void main(String[] args) {
        ShortestPathAddEdgeFloyd spaef = new ShortestPathAddEdgeFloyd(4, new int[][]{{0, 2, 5}, {0, 1, 2}, {1, 2, 1}, {3, 0, 3}});
        System.out.println(spaef.shortestPath(3, 2));
        System.out.println(spaef.shortestPath(0, 3));
        spaef.addEdge(new int[]{1,3,4});
        System.out.println(spaef.shortestPath(0, 3));
    }
}
