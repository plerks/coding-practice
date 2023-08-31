/*
url: https://leetcode.cn/problems/minimum-degree-of-a-connected-trio-in-a-graph/
LeetCode参考: https://leetcode.cn/problems/minimum-degree-of-a-connected-trio-in-a-graph/solutions/2417898/yi-ge-tu-zhong-lian-tong-san-yuan-zu-de-wuv8o/
*/

public class Solution1761 {
    public int minTrioDegree(int n, int[][] edges) {
        int[] degrees = new int[n];
        int[][] matrix = new int[n][n];
        for (int i = 0; i < edges.length; i++) {
            degrees[edges[i][0] - 1]++;
            degrees[edges[i][1] - 1]++;
            matrix[edges[i][0] - 1][edges[i][1] - 1] = 1;
            matrix[edges[i][1] - 1][edges[i][0] - 1] = 1;
        }
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrix[i][j] == 1) {
                    for (int k = j + 1; k < n; k++) {
                        if (matrix[i][k] == 1 && matrix[j][k] == 1) {
                            ans = Math.min(ans, degrees[i] + degrees[j] + degrees[k] - 6);
                        }
                    }
                }
            }
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }

    public static void main(String[] args) {
        Solution1761 solu = new Solution1761();
        System.out.println(solu.minTrioDegree(6, new int[][]{{1,2},{1,3},{3,2},{4,1},{5,2},{3,6}}));
    }
}