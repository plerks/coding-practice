/*
url: https://leetcode.cn/problems/minimum-score-of-a-path-between-two-cities/description/
标签: dfs
*/

import java.util.*;

public class Solution2492 {
    int ans = Integer.MAX_VALUE;

    // 用并查集应该也可以
    public int minScore(int n, int[][] roads) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : roads) {
            graph.get(edge[0] - 1).add(new int[]{edge[1] - 1, edge[2]});
            graph.get(edge[1] - 1).add(new int[]{edge[0] - 1, edge[2]});
        }
        boolean[] visited = new boolean[n];
        Arrays.fill(visited, false);
        dfs(0, graph, visited);
        return ans;
    }

    public void dfs(int i, List<List<int[]>> graph, boolean[] visited) {
        if (!visited[i]) {
            visited[i] = true;
            for (int[] neighbor : graph.get(i)) {
                int v = neighbor[0], w = neighbor[1];
                ans = Math.min(ans, w);
                if (!visited[v]) {
                    dfs(v, graph, visited);
                }
            }
        }
    }

    public static void main(String[] args) {
        Solution2492 solu = new Solution2492();
        System.out.println(solu.minScore(4, new int[][]{{1,2,9},{2,3,6},{2,4,5},{1,4,7}}));
    }
}
