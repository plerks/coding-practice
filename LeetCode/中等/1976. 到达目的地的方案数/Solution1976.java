/*
url: https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/description/?envType=daily-question&envId=2024-03-05
LeetCode参考: https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/solutions/951921/dao-da-mu-de-di-de-fang-an-shu-by-leetco-5ptp/
其它参考: https://oi-wiki.org/graph/shortest-path/#%E5%AE%9E%E7%8E%B0_2
相关: LeetCode797. 所有可能的路径, LeetCode1631. 最小体力消耗路径
标签: 最短路径数, Dijkstra算法, 优先队列实现的Dijkstra算法, Floyd算法, 动态规划
*/

import java.util.*;

public class Solution1976 {
    int min = Integer.MAX_VALUE;
    int count = 0;

    /* 4 / 55 个通过的测试用例，这样写想的是通过dfs遍历所有从节点0到n-1的路径，但是这题是无向图，只要0到n-1的路径有多条，就意味着
    图是有环的，这题题目上说某些路口之间有双向道路，但是又说了任意两个路口之间最多有一条路，按理说这意思是两点之间至多一条边，不知道这个双向道路是什么意思。
    这样写对
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
    这个用例会超时，之前看运行一段时间之后调用栈的帧不多，没有stackoverflow，还以为是以某种我想不出来的方式死循环了，
    但是在`LeetCode1631. 最小体力消耗路径`中也写了这样的代码，且那题对一个看起来不算太长的用例也超时了，说明这里
    应该不是以某种方式死循环了，而是单纯超时了。

    关于这里的dfs为什么一定能结束，可以这样思考：dfs(root)是否能结束取决于dfs root的neighbor是否能结束，dfs一个neighbor
    是否能结束又取决于dfs neighbor的neighbor是否能结束。以dfs(root.neighbor1)这个递归实例为例，由于有visited数组，若其需要
    产生新的递归实例，则dfs过程中未被访问的节点的个数严格单减，最终一定能结束，若其不需要产生新的递归实例，则其直接结束。
    综上，这里的dfs虽然在一个节点访问完成后重新把其visited状态置成了false，但是算法不会有无法结束的风险。

    分析下时间复杂度，以n个节点的完全图为例，以0到n-1的路径为例，中间路径可用n-2个节点，每个节点可选可不选，于是中间路径所用点是这n-2个节点的集合
    的幂集，每个子集内部还可以全排构成不同路径。选2个节点作为起点和终点有A(n,2)种情况，即使忽略掉子集内部的全排，路径总数也有A(n,2) * 2^(n - 2)。
    是指数级，所以很容易超时。
    这题节点数规模1 <= n <= 200。

    这里的代码是求有向无环图求两个节点间的所有路径的解法，见LeetCode797. 所有可能的路径（节点数规模2 <= n <= 15）。
    */
    public int countPaths_exceed_time_limit(int n, int[][] roads) {
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

    // 这里让count[i][i] = 0感觉更合理，也让count符合邻接矩阵的定义
    public int countPaths_implementation3(int n, int[][] roads) {
        /* 若不这样单独判断一次，则后面count[i][i] = 0;要改成count[i][i] = 1;因为有个用例n==1，roads=[]，要求返回1，不过感觉返回0更合适。
        若后面改成count[i][i] = 1;则循环里需要判断if (i != k && j != k)，不然i==k或者j==k时会走到dis[i][k] + dis[k][j] == dis[i][j]的情况里多加
        */
        if (0 == n - 1) return 1;
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
            count[i][i] = 0; // 题意应该没有自环
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
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
        return count[0][n - 1];
    }

    public static void main(String[] args) {
        Solution1976 solu = new Solution1976();
        // System.out.println(solu.countPaths_exceed_time_limit(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));
        System.out.println(solu.countPaths_exceed_time_limit(4, new int[][]{{0,1,1},{0,2,1},{0,3,1},{1,2,1},{1,3,1},{2,3,1}}));

        Solution1976 solu2 = new Solution1976();
        System.out.println(solu2.countPaths(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));

        Solution1976 solu3 = new Solution1976();
        System.out.println(solu3.countPaths_implementation2(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));

        Solution1976 solu4 = new Solution1976();
        System.out.println(solu4.countPaths_implementation3(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}));
    }
}
