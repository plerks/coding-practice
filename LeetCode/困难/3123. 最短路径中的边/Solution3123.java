/*
url: https://leetcode.cn/problems/find-edges-in-shortest-paths/description/
LeetCode参考: https://leetcode.cn/problems/find-edges-in-shortest-paths/solutions/2749274/dijkstra-zui-duan-lu-dfsbfs-zhao-bian-py-yf48/
相关: 典型问题/最短路径问题/最短路径-Dijkstra-使用优先队列
标签: LeetCode第394场周赛, 所有最短路径, 最短路径数, Dijkstra算法, 进制表示法
*/

import java.util.*;

// 头一次做出LeetCode周赛全部4题
public class Solution3123 {
    /* 我的解法。因为之前总结过最短路径数所以知道这题怎么做，不过还是花了挺长时间。在用Dijkstra算法求最短路径的过程中记录parent，
    最后从n-1通过parent反向dfs求在最短路径上的边。一开始用的是`典型问题/最短路径问题/最短路径-Dijkstra`的暴力求解下一个
    优先级最高节点的Dijkstra算法版本，532 / 534 个通过的测试用例，超时。然后改用使用优先队列的版本，在最后只剩几分钟的时候通过。
    说明这题的用例的图偏稀疏图。
    */
    public boolean[] findAnswer(int n, int[][] edges) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        int[] distance = new int[n]; // 每个节点到0的最短距离
        Arrays.fill(distance, Integer.MAX_VALUE / 2);
        List<List<Integer>> parent = new ArrayList<>(); // 每个节点能由谁转移来
        for (int i = 0; i < n; i++) {
            parent.add(new ArrayList<>());
        }
        boolean[] discovered = new boolean[n];
        Arrays.fill(discovered, false);
        distance[0] = 0;
        PriorityQueue<int[]> q = new PriorityQueue<>((x, y) -> {
            return x[1] < y[1] ? -1 : 1;
        });
        q.offer(new int[]{0, 0});
        while (!q.isEmpty()) {
            int[] arr = q.poll();
            int node = arr[0];
            int dis = arr[1];
            if (dis > distance[node]) continue;
            for (int[] neighbor : graph.get(node)) {
                int next = neighbor[0];
                int w = neighbor[1];
                if (dis + w < distance[next]) {
                    distance[next] = dis + w;
                    parent.get(next).clear();
                    parent.get(next).add(node);
                    q.offer(new int[]{next, distance[next]});
                }
                else if (dis + w == distance[next]) {
                    parent.get(next).add(node);
                }
            }
        }
        boolean[] ans = new boolean[edges.length];
        // 从n-1反向dfs
        Map<Integer, Integer> map = new HashMap<>(); // 用进制表示法记录边的编号
        int N = 5 * (int)1e4 + 1;
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0], v = edges[i][1];
            map.put(u * N + v, i);
            map.put(v * N + u, i);
        }
        dfs(n - 1, ans, map, parent);
        return ans;
    }

    private void dfs(int r, boolean[] ans, Map<Integer, Integer> map, List<List<Integer>> parent) {
        if (r == 0) return;
        int N = 5 * (int)1e4 + 1;
        for (int node : parent.get(r)) {
            ans[map.get(r * N + node)] = true;
            dfs(node, ans, map, parent);
        }
    }

    // 532 / 534 个通过的测试用例，超时
    public boolean[] findAnswer_exceed_time_limit(int n, int[][] edges) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        int[] distance = new int[n]; // 每个节点到0的最短距离
        Arrays.fill(distance, Integer.MAX_VALUE / 2);
        List<List<Integer>> parent = new ArrayList<>(); // 每个节点能由谁转移来
        for (int i = 0; i < n; i++) {
            parent.add(new ArrayList<>());
        }
        boolean[] discovered = new boolean[n];
        Arrays.fill(discovered, false);
        distance[0] = 0;
        int discoveredNodeCount = 0;
        while (discoveredNodeCount < n) {
            // 找优先级最高的未发现节点，这个每次找最高优先级节点的过程可以优化
            int node = -1, min = Integer.MAX_VALUE;
            for (int i = 0; i < distance.length; i++) {
                if (!discovered[i]) {
                    if (distance[i] < min) {
                        node = i;
                        min = distance[i];
                    }
                }
            }
            int v = 0, w = 0;
            for (int j = 0; j < graph.get(node).size(); j++) { // 用node相关的边做松弛操作
                v = graph.get(node).get(j)[0];
                w = graph.get(node).get(j)[1];
                if (discovered[v]) continue;
                if (distance[node] + w < distance[v]) {
                    distance[v] = distance[node] + w;
                    parent.get(v).clear();
                    parent.get(v).add(node);
                }
                else if (distance[node] + w == distance[v]) {
                    parent.get(v).add(node);
                }
            }
            discovered[node] = true;
            discoveredNodeCount++;
        }
        boolean[] ans = new boolean[edges.length];
        // 从n-1反向dfs
        Map<Integer, Integer> map = new HashMap<>(); // 用进制表示法记录边的编号
        int N = 5 * (int)1e4 + 1;
        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0], v = edges[i][1];
            map.put(u * N + v, i);
            map.put(v * N + u, i);
        }
        dfs(n - 1, ans, map, parent);
        return ans;
    }

    /* 灵茶山艾府题解解法，没有记录parent，而是一遍Dijkstra之后，通过dis[x] + w == dis[y]判断(x,y)是否是最短
    路径上的边。这样有一个问题dis[x] + w == dis[y]，可能完全是往别的节点走的，不是到节点n-1的路。因此要从n-1反向
    dfs/bfs，这样才能保证是0到n-1的路径。上面我的解法也是必须从n-1反向dfs，这里源点0和目的点n-1地位不太相同。 */
    public boolean[] findAnswer_implementation2(int n, int[][] edges) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int i = 0; i < edges.length; i++) {
            int[] edge = edges[i];
            graph.get(edge[0]).add(new int[]{edge[1], edge[2], i});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2], i});
        }
        int[] distance = new int[n]; // 每个节点到0的最短距离
        Arrays.fill(distance, Integer.MAX_VALUE); // 这题没有用distance[i]加别的，不用fill为Integer.MAX_VALUE / 2防止加的时候溢出
        boolean[] discovered = new boolean[n];
        Arrays.fill(discovered, false);
        distance[0] = 0;
        PriorityQueue<int[]> q = new PriorityQueue<>((x, y) -> {
            return x[1] < y[1] ? -1 : 1;
        });
        q.offer(new int[]{0, 0});
        while (!q.isEmpty()) {
            int[] arr = q.poll();
            int node = arr[0];
            int dis = arr[1];
            if (dis > distance[node]) continue;
            for (int[] neighbor : graph.get(node)) {
                int next = neighbor[0];
                int w = neighbor[1];
                if (dis + w < distance[next]) {
                    distance[next] = dis + w;
                    q.offer(new int[]{next, distance[next]});
                }
            }
        }
        boolean[] ans = new boolean[edges.length];
        boolean[] visited = new boolean[n];
        // 用bfs或dfs都行，反向遍历一遍图即可，这里用bfs
        Deque<Integer> q2 = new LinkedList<>();
        q2.offer(n - 1);
        while (!q2.isEmpty()) {
            int v = q2.poll();
            for (int[] arr : graph.get(v)) {
                int u = arr[0];
                int w = arr[1];
                int index = arr[2];
                if (distance[u] + w == distance[v]) {
                    ans[index] = true;
                    /* 注意:
                    只能把最短路径上的节点加入队列，q2.offer(u)不能写到if外面，否则把非最短路径上的节点也加入了，
                    这样会导致: 例如3可以到n-1，但是走这条路不是最短路径，然后0可以到3，并且
                    0到3可以有distance[u] + w == distance[v]，这样会把(0,3)也认为是最短路径上的边。
                    也就是说这里算是个类dfs。
                    */
                    q2.offer(u);
                }
                visited[v] = true;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3123 solu = new Solution3123();
        System.out.println(Arrays.toString(solu.findAnswer(6, new int[][]{{0,1,4},{0,2,1},{1,3,2},{1,4,3},{1,5,1},{2,3,1},{3,5,3},{4,5,2}})));
        System.out.println(Arrays.toString(solu.findAnswer_exceed_time_limit(6, new int[][]{{0,1,4},{0,2,1},{1,3,2},{1,4,3},{1,5,1},{2,3,1},{3,5,3},{4,5,2}})));
        System.out.println(Arrays.toString(solu.findAnswer_implementation2(6, new int[][]{{0,1,4},{0,2,1},{1,3,2},{1,4,3},{1,5,1},{2,3,1},{3,5,3},{4,5,2}})));
    }
}