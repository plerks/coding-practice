/* 仅仅针对所有边的权重全为1的图或者路径长度定义为经过的边数的图，可以用bfs求解最短路径。否则不行。以下以图按一个矩阵给出为例。
相关: LeetCode2258. 逃离火灾
*/

import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class ShortestPathBFS {
    int[][] DIRECTIONS = new int[][]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // 求解(0,0)到其它点的距离，grid[i][j]==0表示是空位，grid[i][j]==2表示是障碍，距离为正无穷大
    public int[][] shortestPath(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] distance = new int[m][n];
        for (int[] arr : distance) {
            Arrays.fill(arr, -1); // 用-1表示点未访问过，可以免去用一个visited矩阵记录
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    distance[i][j] = Integer.MAX_VALUE;
                }
            }
        }
        int N = Math.max(m, n) + 1; // 用进制表示法，用一个数来表示点
        Deque<Integer> q = new LinkedList<>();
        q.offer(0 * N + 0);
        distance[0][0] = 0;
        for (int t = 1; !q.isEmpty(); t++) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int coordinate = q.poll();
                int x = coordinate / N;
                int y = coordinate % N;
                for (int[] arr : DIRECTIONS) {
                    int xx = x + arr[0];
                    int yy = y + arr[1];
                    if (xx >= 0 && xx < m && yy >= 0 && yy < n && distance[xx][yy] == -1) {
                        distance[xx][yy] = t;
                        q.offer(xx * N + yy);
                    }
                }
            }
        }
        return distance;
    }

    public static void main(String[] args) {
        ShortestPathBFS solu = new ShortestPathBFS();
        System.out.println(Arrays.deepToString(solu.shortestPath(new int[][]{{0,0,0,0},{0,0,2,0},{0,2,0,0}})));
    }
}
