/*
url: https://leetcode.cn/problems/reachable-nodes-with-restrictions/description/?envType=daily-question&envId=2024-03-02
标签: dfs, 树以节点边给出时的dfs
*/

import java.util.*;

public class Solution2368 {
    int ans = 0;

    public int reachableNodes(int n, int[][] edges, int[] restricted) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        Set<Integer> set = new HashSet<>();
        for (int node : restricted) set.add(node);
        dfs(0, graph, set, -1);
        return ans;
    }

    private void dfs(int root, List<List<Integer>> graph, Set<Integer> set, int pre) {
        ans++;
        for (int child : graph.get(root)) {
            if (child != pre && !set.contains(child)) {
                dfs(child, graph, set, root);
            }
        }
    }

    public static void main(String[] args) {
        Solution2368 solu = new Solution2368();
        System.out.println(solu.reachableNodes(7, new int[][]{{0,1},{1,2},{3,1},{4,0},{0,5},{5,6}}, new int[]{4,5}));
    }
}
