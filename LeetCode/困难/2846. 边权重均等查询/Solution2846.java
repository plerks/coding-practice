/*
url: https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/description/?envType=daily-question&envId=2024-01-26
LeetCode参考: https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/solutions/2620281/python3javacgo-yi-ti-yi-jie-bei-zeng-fa-p8u67/
              https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/solutions/2614609/bian-quan-zhong-jun-deng-cha-xun-by-leet-yunc/
其它参考: https://www.bilibili.com/video/BV1N7411G7JD/
          https://oi.wiki/graph/lca/
相关: LeetCode236. 二叉树的最近公共祖先
标签: 最近公共祖先, 倍增法, Tarjan算法
*/

import java.util.*;

public class Solution2846 {
    // 我的暴力解法，709 / 733 个通过的测试用例，最后超时
    /* public int[] minOperationsQueries(int n, int[][] edges, int[][] queries) {
        List<List<int[]>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            graph.get(u).add(new int[]{v, edge[2]});
            graph.get(v).add(new int[]{u, edge[2]});
        }
        int[] ans = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            ans[i] = calc(n, queries[i][0], queries[i][1], graph);
        }
        return ans;
    }

    private int calc(int n, int u, int v, List<List<int[]>> graph){
        Map<Integer, Integer> map = new HashMap<>(); // 记录u到v的路径各个权值的边各有几条
        Map<Integer, Integer> temp = new HashMap<>(); // dfs过程中记录路径
        boolean[] visited = new boolean[n];
        dfs(u, v, graph, temp, map, visited);
        int maxTime = 0;
        int totalTime = 0;
        for (int value : map.values()) {
            maxTime = Math.max(value, maxTime);
            totalTime += value;
        }
        return totalTime - maxTime; // 出现次数最多的是maxTime，把其它边都变成出现maxTime次的权值
    }

    private void dfs(int u, int v, List<List<int[]>> graph, Map<Integer, Integer> temp, Map<Integer, Integer> map, boolean[] visited) {
        if (u == v) {
            for (Map.Entry<Integer, Integer> e : temp.entrySet()) {
                map.put(e.getKey(), map.getOrDefault(e.getKey(), 0) + e.getValue());
            }
        }
        else if (!visited[u]) {
            visited[u] = true;
            for (int i = 0; i < graph.get(u).size(); i++) {
                int[] neighbor = graph.get(u).get(i);
                int neibor = neighbor[0];
                int weight = neighbor[1];
                temp.put(weight, temp.getOrDefault(weight, 0) + 1);
                dfs(neibor, v, graph, temp, map, visited);
                temp.put(weight, temp.get(weight) - 1);
            }
        }
    } */

    /* 倍增法，由于这里要query多次，不是像LeetCode236. 二叉树的最近公共祖先那样只查询一次，因此可以预处理出f[i][j]表示i节点的第2^j个父节点，
    进而实现每次可以跳多步，而不是像LeetCode236. 二叉树的最近公共祖先那样一步步往上跳，从而实现对多次query的优化。此外由于往上跳的过程可以每次只跳一步，
    不会存在跳过或者跳不到最近公共祖先的情况。

    待做: 还有个Tarjan算法，一时半会看不明白，以后再说。
    */
    public int[] minOperationsQueries(int n, int[][] edges, int[][] queries) {
        final int W = 26;
        List<List<int[]>> graph = new ArrayList<>(n);
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            graph.get(u).add(new int[]{v, edge[2]});
            graph.get(v).add(new int[]{u, edge[2]});
        }
        int[] parent = new int[n];
        int m = 32 - Integer.numberOfLeadingZeros(n);
        // f[i][j]表示i节点的第2^j个父节点
        int[][] f = new int[n][m]; // 一共n个节点，则一个节点最多n-1个祖先，2^m > n，够记录一个节点的所有2^i位置的祖先节点
        int[][] count = new int[n][]; // 以0号节点为根，count[i][j]记录i号节点到根节点权值为j的边有多少条
        count[0] = new int[W + 1];
        int[] depth = new int[n];
        // bfs计算每个节点的depth和count，用dfs也行
        Deque<Integer> q = new LinkedList<>();
        q.offer(0);
        parent[0] = 0;
        while (!q.isEmpty()) {
            int i = q.poll();
            f[i][0] = parent[i]; // 除了根节点，其它节点在入队时已填充好了parent[i]
            for (int j = 1; j < m; j++) { // 有些节点的祖先没那么多个，统一会记为根节点0，最终跳跃时会判断depth，不会有问题
                f[i][j] = f[f[i][j - 1]][j - 1]; // 关键关系，i的第2^1个祖先f[i][j]等于i的第2^(i-1)个祖先f[i][j - 1]的第2^(i-1)个祖先
            }
            List<int[]> neighbors = graph.get(i);
            for (int[] neighbor : neighbors) {
                int j = neighbor[0], w = neighbor[1];
                if (j != parent[i]) { // 由于是无向图，防止u,v和v,u死循环添加，应该也可以用visited[]来记录是否访问
                    parent[j] = i;
                    count[j] = count[i].clone();
                    count[j][w]++;
                    depth[j] = depth[i] + 1;
                    q.offer(j);
                }
            }
        }
        int len = queries.length;
        int[] ans = new int[len];
        for (int i = 0; i < len; i++) {
            int u = queries[i][0], v = queries[i][1];
            int x = u, y = v;
            // 交换，让x在下
            if (depth[x] < depth[y]) {
                int temp = x;
                x = y;
                y = temp;
            }
            // 让x上升到与y同层，至少可以反复每次只上跳1步，一定能跳到同层
            for (int j = m - 1; j >= 0; j--) {
                if (depth[f[x][j]] >= depth[y]) {
                    x = f[x][j]; // 若这里循环结束后x==y，最近公共祖先就是x
                }
            }
            int lca = -1;
            if (x == y) lca = x;
            else {
                // x,y一起往上跳，但是不能跳成相等，否则可能一步跳多直接跳成最近公共祖先的祖先节点
                for (int j = m - 1; j >= 0; j--) {
                    if (f[x][j] != f[y][j]) {
                        x = f[x][j];
                        y = f[y][j];
                    }
                }
                lca = parent[x];
            }
            int max = 0;
            for (int j = 1; j <= W; j++) { // 枚举边的权值范围，找出出现次数最多的权值
                // count[u][j] + count[v][j] - 2 * count[lca][j]为u到v的路径，权值为j的边的出现次数
                max = Math.max(max, count[u][j] + count[v][j] - 2 * count[lca][j]);
            }
            // depth[u] + depth[v] - 2 * depth[lca]为u到v的边数
            ans[i] = depth[u] + depth[v] - 2 * depth[lca] - max;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2846 solu = new Solution2846();
        System.out.println(Arrays.toString(solu.minOperationsQueries(8, new int[][]{{1,2,6},{1,3,4},{2,4,6},{2,5,3},{3,6,6},{3,0,8},{7,0,2}}, new int[][]{{4,6},{0,4},{6,5},{7,4}})));
    }
}
