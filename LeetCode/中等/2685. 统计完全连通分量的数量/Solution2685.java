/*
url: https://leetcode.cn/problems/count-the-number-of-complete-components/
LeetCode参考: https://leetcode.cn/problems/count-the-number-of-complete-components/solutions/2269255/dfs-qiu-mei-ge-lian-tong-kuai-de-dian-sh-opg4/
相关: LeetCode2316. 统计无向图中无法互相到达点对数, /典型问题/求连通分量, /典型问题/并查集
我的题解: https://leetcode.cn/problems/count-the-number-of-complete-components/solutions/2491899/bing-cha-ji-qiu-lian-tong-fen-liang-bian-y9co/
标签: 完全连通分量个数, 并查集, dfs
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Solution2685 {
    public int countCompleteComponents(int n, int[][] edges) {
        /* 使用并查集能很容易地找出连通分量，但是题目要求完全连通分量，考虑将边数信息统计到每个子集合的根节点上，然后判断是否完全。
        在并查集构建过程中每个子集的根可能会变化，不方便统计边数到根上，但是构建完成后并查集结构不再变化，这时再遍历一遍边即可方便统计每个连通
        分量的边数，从而判断是否完全。
        */
        UnionFind uf = new UnionFind(n);
        for (int[] edge : edges) {
            uf.union(edge[0], edge[1]);
        }
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            if (uf.find(i) == i) { // 连通分量的根节点
                map.put(i, 0);
            }
        }
        for (int[] edge : edges) {
            int root = uf.find(edge[0]);
            map.put(root, map.get(root) + 1); // 将边数统计到根节点上
        }
        int ans = 0;
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            int size = uf.getSize(entry.getKey()); // 这个分量有多少节点
            if (entry.getValue() == size * (size - 1) / 2) { // 判断是否完全
                ans++;
            }
        }
        return ans;
    }

    /* 参考https://leetcode.cn/problems/count-the-number-of-complete-components/solutions/2269255/dfs-qiu-mei-ge-lian-tong-kuai-de-dian-sh-opg4/，
    dfs也能做，但是用并查集会清晰很多。
    */
    public int countCompleteComponents_implementation2(int n, int[][] edges) {
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
        int[] ve = new int[2]; // 这次dfs搜索到的连通分量的节点和边数
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, ve, graph, visited);
                if (ve[1] / 2 == ve[0] * (ve[0] - 1) / 2) {
                    ans++;
                }
                ve[0] = 0;
                ve[1] = 0;
            }
        }
        return ans;
    }

    public void dfs(int i, int[] ve, List<List<Integer>> graph, boolean[] visited) {
        if (!visited[i]) {
            ve[0]++;
            ve[1] += graph.get(i).size(); // 这样连通分量内的边会被统计2次
            visited[i] = true;
            for (int j : graph.get(i)) {
                if (!visited[j]) {
                    dfs(j, ve, graph, visited);
                }
            }
        }
    }

    // 优化并查集实现，支持直接查询子集合边数
    public int countCompleteComponents_implementation3(int n, int[][] edges) {
        UnionFindWithEdgeCount uf = new UnionFindWithEdgeCount(n);
        for (int[] edge : edges) {
            uf.union(edge[0], edge[1]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (uf.find(i) == i && uf.getEdgeCount(i) == uf.getSize(i) * (uf.getSize(i) - 1) / 2) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2685 solu = new Solution2685();
        System.out.println(solu.countCompleteComponents(6, new int[][]{{0,1},{0,2},{1,2},{3,4}}));
        System.out.println(solu.countCompleteComponents_implementation2(6, new int[][]{{0,1},{0,2},{1,2},{3,4}}));
        System.out.println(solu.countCompleteComponents_implementation3(6, new int[][]{{0,1},{0,2},{1,2},{3,4}}));
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

class UnionFindWithEdgeCount {
    private int[] parents;

    private int[] sizes;

    private int[] edgeCount;

    public UnionFindWithEdgeCount(int n) {
        this.parents = new int[n];
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
        this.sizes = new int[n];
        Arrays.fill(sizes, 1);
        this.edgeCount = new int[n];
    }

    public void union(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            edgeCount[rx]++;
            return;
        }
        if (sizes[rx] < sizes[ry]) {
            parents[rx] = ry;
            sizes[ry] += sizes[rx];
            edgeCount[ry] += edgeCount[rx] + 1;
        }
        else {
            parents[ry] = rx;
            sizes[rx] += sizes[ry];
            edgeCount[rx] += edgeCount[ry] + 1;
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

    public int getEdgeCount(int x) {
        return edgeCount[x];
    }
}