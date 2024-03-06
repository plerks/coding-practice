/*
url: https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/description/?envType=daily-question&envId=2024-03-05
LeetCode参考: https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/solutions/951921/dao-da-mu-de-di-de-fang-an-shu-by-leetco-5ptp/
其它参考: https://oi-wiki.org/graph/shortest-path/#%E5%AE%9E%E7%8E%B0_2
相关: LeetCode797. 所有可能的路径
标签: 最短路径数, Dijkstra算法, 优先队列实现的Dijkstra算法, Floyd算法, 动态规划
*/

import java.util.*;

public class Solution1976 {
    int min = Integer.MAX_VALUE;
    int count = 0;

    /* 4 / 55 个通过的测试用例，这样写想的是通过dfs遍历所有从节点0到n-1的路径，但是这题是无向图，只要0到n-1的路径有多条，就意味着
    图是有环的，且这题某些路口之间还可能有双向道路，这样写对
    18, new int[][]{{0,1,3972},{2,1,1762},{3,1,4374},{0,3,8346},{3,2,2612},{4,0,6786},{5,4,1420},{2,6,7459},{1,6,9221},
    {6,3,4847},{5,6,4987},{7,0,14609},{7,1,10637},{2,7,8875},{7,6,1416},{7,5,6403},{7,3,6263},{4,7,7823},{5,8,10184},
    {8,1,14418},{8,4,11604},{7,8,3781},{8,2,12656},{8,0,18390},{5,9,15094},{7,9,8691},{9,6,10107},{9,1,19328},{9,4,16514},
    {9,2,17566},{9,0,23300},{8,9,4910},{9,3,14954},{4,10,26060},{2,10,27112},{10,1,28874},{8,10,14456},{3,10,24500},{5,10,24640},
    {10,6,19653},{10,0,32846},{10,9,9546},{10,7,18237},{11,7,21726},{11,2,30601},{4,11,29549},{11,0,36335},{10,11,3489},
    {6,11,23142},{3,11,27989},{11,1,32363},{11,8,17945},{9,11,13035},{5,11,28129},{2,12,33902},{5,12,31430},{6,12,26443},
    {4,12,32850},{12,3,31290},{11,12,3301},{12,1,35664},{7,13,28087},{13,8,24306},{6,13,29503},{11,13,6361},{4,13,35910},
    {13,12,3060},{3,13,34350},{13,5,34490},{13,2,36962},{10,13,9850},{9,13,19396},{12,14,8882},{8,14,30128},{14,6,35325},
    {14,5,40312},{1,14,44546},{11,14,12183},{15,12,13581},{2,15,47483},{4,15,46431},{15,10,20371},{15,14,4699},{15,6,40024},
    {15,7,38608},{1,15,49245},{11,15,16882},{8,15,34827},{0,15,53217},{5,15,45011},{15,3,44871},{16,2,53419},{16,9,35853},
    {1,16,55181},{16,7,44544},{8,16,40763},{0,16,59153},{15,16,5936},{16,10,26307},{16,6,45960},{12,16,19517},{17,2,57606},
    {17,3,54994},{17,14,14822},{17,11,27005},{0,17,63340},{17,7,48731},{8,17,44950},{17,16,4187},{5,17,55134},{17,10,30494},
    {17,9,40040},{17,12,23704},{13,17,20644},{17,1,59368}}
    这个用例会超时，但是运行了一段时间没有stackoverflow，说明不是dfs()死递归了，更像是dfs()死循环了，看调用栈dfs()的帧也不是特别多。
    但是没想明白这个死循环是如何发生的，这个用例的图太复杂了，试了下4个节点的完全图又没发生死循环。
    待做: 这个死循环是如何发生的
    但是这样写可以用于有向无环图求两个节点间的所有路径，见LeetCode797. 所有可能的路径。
    */
    public int countPaths_wrong(int n, int[][] roads) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : roads) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        boolean[] visited = new boolean[n];
        dfs(0, graph, n, visited, 0);
        return count;
    }

    private void dfs(int root, List<List<int[]>> graph, int n, boolean[] visited, int distance) {
        if (!visited[root]) {
            visited[root] = true;
            if (root == n - 1) {
                if (distance < min) {
                    min = distance;
                    count = 1;
                }
                else if (distance == min) {
                    count++;
                }
                visited[root] = false;
                return;
            }
            for (int[] arr : graph.get(root)) {
                int v = arr[0];
                int weight = arr[1];
                dfs(v, graph, n, visited, distance + weight);
            }
            // 为了后续还可以通过其它路径到这个点
            visited[root] = false;
        }
    }

    // 官方题解的做法，这题虽然有环，但是边的权值非负，能使用Dijkstra算法，使用优先队列实现的Dijkstra算法的同时dp计算最短路径数
    public int countPaths(int n, int[][] roads) {
        final int MOD = (int)1e9 + 7;
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : roads) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        long[] dis = new long[n]; // 记录0到i的最短距离
        Arrays.fill(dis, Long.MAX_VALUE);
        dis[0] = 0;
        int[] count = new int[n]; // 记录0到i的最短路径数
        count[0] = 1;
        // 这里的int[]记录[节点, 最短距离]
        PriorityQueue<long[]> q = new PriorityQueue<>((x, y) -> {
            return x[1] < y[1] ? -1 : 1;
        });
        q.offer(new long[]{0, 0});
        while (!q.isEmpty()) {
            long[] arr = q.poll();
            int node = (int)arr[0];
            long distance = arr[1];
            /* 这行continue不要也能正确，若distance > dis[node]，说明q中前面已有distance更小的[node, distance]，q中的这个arr
            不需要使用进行计算。oi wiki上是用了个visited数组，这里是if (vis[u]) continue;
            */
            if (distance > dis[node]) continue;
            for (int[] neighbor : graph.get(node)) {
                int next = neighbor[0];
                int w = neighbor[1];
                if (distance + w < dis[next]) {
                    dis[next] = distance + w;
                    count[next] = count[node];
                    q.offer(new long[]{next, dis[next]});
                }
                else if (distance + w == dis[next]) {
                    count[next] = (count[next] + count[node]) % MOD;
                }
            }
        }
        return count[n - 1];
    }

    // 官方题解评论区有用Floyd算法做的，我也写一下
    public int countPaths_implementation2(int n, int[][] roads) {
        final int MOD = (int)1e9 + 7;
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : roads) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        long[][] dis = new long[n][n]; // 记录两点之间的最短距离
        int[][] count = new int[n][n]; // 记录两点之间的最短路径数
        for (long[] arr : dis) Arrays.fill(arr, Long.MAX_VALUE);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph.get(i).size(); j++) {
                int u = i, v = graph.get(i).get(j)[0], w = graph.get(i).get(j)[1];
                dis[u][v] =  w;
                count[u][v] = 1;
                dis[v][u] = w;
                count[v][u] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            dis[i][i] = 0;
            count[i][i] = 1;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != k && j != k) { // 这个判断必须加，不然i==k或者j==k时会走到dis[i][k] + dis[k][j] == dis[i][j]的情况里多加
                        if (dis[i][k] != Long.MAX_VALUE && dis[k][j] != Long.MAX_VALUE && dis[i][k] + dis[k][j] < dis[i][j]) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                            count[i][j] = count[i][k] * count[k][j];
                        }
                        else if (dis[i][k] + dis[k][j] == dis[i][j]) {
                            count[i][j] = (count[i][j] + count[i][k] * count[k][j]) % MOD;
                        }
                    }
                }
            }
        }
        return count[0][n - 1];
    }

    public static void main(String[] args) {
        Solution1976 solu = new Solution1976();
        // System.out.println(solu.countPaths_wrong(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));
        System.out.println(solu.countPaths_wrong(4, new int[][]{{0,1,1},{0,2,1},{0,3,1},{1,2,1},{1,3,1},{2,3,1}}));

        Solution1976 solu2 = new Solution1976();
        System.out.println(solu2.countPaths(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));

        Solution1976 solu3 = new Solution1976();
        System.out.println(solu3.countPaths_implementation2(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));
    }
}
