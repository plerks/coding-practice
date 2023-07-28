// https://leetcode.cn/problems/parallel-courses-iii/

import java.util.*;

public class Solution2050 {
    public int minimumTime(int n, int[][] relations, int[] time) {
        List<List<Integer>> graph = buildGraph(n, relations);
        int[] inDegrees = new int[n];
        Queue<Integer> q = new LinkedList<>();
        int[] cost = new int[n];
        for (int i = 0; i < relations.length; i++) {
            inDegrees[relations[i][1] - 1]++;
        }
        for (int i = 0; i < graph.size(); i++) {
            if (inDegrees[i] == 0) {
                q.offer(i);
                cost[i] = time[i];
            }
        }
        // BFS
        while (!q.isEmpty()) {
            int node = q.poll();
            for (int i = 0; i < graph.get(node).size(); i++) {
                int child = graph.get(node).get(i);
                cost[child] = Math.max(cost[child], cost[node] + time[child]);
                inDegrees[child]--;
                if (inDegrees[child] == 0) {
                    q.offer(child);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < cost.length; i++) {
            ans = Math.max(ans, cost[i]);
        }
        return ans;
    }

    private List<List<Integer>> buildGraph(int n, int[][] relations) {
        List<List<Integer>> graph = new ArrayList<List<Integer>>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<Integer>());
        }
        for (int[] edge : relations) {
            graph.get(edge[0] - 1).add(edge[1] - 1);
        }
        return graph;
    }

    public static void main(String[] args) {
        Solution2050 solu = new Solution2050();
        System.out.println(solu.minimumTime(3, new int[][]{{1,3},{2,3}}, new int[]{3,2,5}));
    }
}