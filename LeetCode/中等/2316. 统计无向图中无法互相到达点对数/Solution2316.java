/*
url: https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/?envType=daily-question&envId=2023-10-21
LeetCode参考: https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/solutions/1625315/by-endlesscheng-7l50/
              https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/solutions/1624997/by-lfool-6rtm/
              https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/solutions/2487673/tong-ji-wu-xiang-tu-zhong-wu-fa-hu-xiang-q5eh/
相关: LeetCode2685. 统计完全连通分量的数量, /典型问题/求连通分量, /典型问题/并查集
标签: dfs, 连通分量, 可达, 并查集
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution2316 {
    public long countPairs(int n, int[][] edges) {
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
        int total = 0; // 前面的连通块的节点数
        long ans = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) { // 新的连通块
                int visitCount = dfs(i, graph, visited); // 新发现的连通块大小
                ans += (long)visitCount * total;
                total += visitCount;
            }
        }
        return ans;
    }

    public int dfs(int i, List<List<Integer>> graph, boolean[] visited) {
        int visitCount = 0;
        if (!visited[i]) {
            visitCount++;
            visited[i] = true;
            for (int j : graph.get(i)) {
                if (!visited[j]) {
                    visitCount += dfs(j, graph, visited);
                }
            }
        }
        return visitCount;
    }

    public long countPairs_implementation2(int n, int[][] edges) {
        UnionFind uf = new UnionFind(n);
        for (int[] edge : edges) {
            uf.union(edge[0], edge[1]);
        }
        long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += n - uf.getSize(uf.find(i)); // n - uf.getSize(uf.find(i));为不与i连通的节点数。不用找出所有连通分量及其规模然后乘。
        }
        return ans / 2;
    }

    public static void main(String[] args) {
        Solution2316 solu = new Solution2316();
        System.out.println(solu.countPairs(7, new int[][]{{0,2},{0,5},{2,4},{1,6},{5,4}}));
        System.out.println(solu.countPairs_implementation2(7, new int[][]{{0,2},{0,5},{2,4},{1,6},{5,4}}));
    }
}

class UnionFind {
    private int[] parents;

    private int[] sizes;

    public UnionFind(int n) {
        this.parents = new int[n];
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
        this.sizes = new int[n];
        Arrays.fill(sizes, 1);
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
}