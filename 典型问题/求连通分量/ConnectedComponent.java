/*
描述: 求图的连通分量个数，可以用并查集或者dfs
相关: LeetCode2316. 统计无向图中无法互相到达点对数, LeetCode2685. 统计完全连通分量的数量, /典型问题/并查集
标签: 连通分量, 并查集, dfs
*/

import java.util.*;

public class ConnectedComponent {
    public int getConnectedComponentCount(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        UnionFindMoreApi uf = new UnionFindMoreApi(n);
        for (int[] edge : edges) {
            uf.union(edge[0], edge[1]);
        }
        return uf.count();
    }

    public int getConnectedComponentCount_implementation2(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        boolean[] visited = new boolean[n];
        Arrays.fill(visited, false);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                ans++;
                dfs(i, graph, visited);
            }
        }
        return ans;
    }

    public void dfs(int i, List<List<Integer>> graph, boolean[] visited) {
        if (!visited[i]) {
            visited[i] = true;
            for (int j : graph.get(i)) {
                dfs(j, graph, visited);
            }
        }
    }

    public static void main(String[] args) {
        ConnectedComponent cc = new ConnectedComponent();
        System.out.println(cc.getConnectedComponentCount(6, new int[][]{{0,1},{0,2},{1,2},{3,4}}));
        System.out.println(cc.getConnectedComponentCount_implementation2(6, new int[][]{{0,1},{0,2},{1,2},{3,4}}));
    }
}

class UnionFindMoreApi {
    private int[] parents;

    private int[] sizes;

    private int count;

    public UnionFindMoreApi(int n) {
        this.parents = new int[n];
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
        this.sizes = new int[n];
        Arrays.fill(sizes, 1);
        this.count = n;
    }

    public void union(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (sizes[rx] < sizes[ry]) {
            parents[rx] = ry;
            sizes[ry] += sizes[rx];
        }
        else {
            parents[ry] = rx;
            sizes[rx] += sizes[ry];
        }
        count--;
    }

    public int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    public int getSize(int x) {
        return sizes[x];
    }

    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    public int count() {
        return this.count;
    }
}