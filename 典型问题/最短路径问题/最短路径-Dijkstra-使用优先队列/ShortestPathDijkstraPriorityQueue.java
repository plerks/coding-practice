/*
描述: 使用优先队列实现Dijkstra算法
参考: https://oi-wiki.org/graph/shortest-path/#%E5%AE%9E%E7%8E%B0_2
相关: LeetCode1976. 到达目的地的方案数, LeetCode3123. 最短路径中的边, LeetCode1928. 规定时间内到达终点的最小花费, LeetCode787. K 站中转内最便宜的航班
*/

import java.util.*;

/* 参考[oi wiki]<https://oi-wiki.org/graph/shortest-path/#%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6>
n为节点数，e为边数，暴力法实现的Dijkstra算法时间复杂度为O(n^2)，使用优先队列实现的Dijkstra算法时间复杂度为O(nloge + eloge)。
因此优先队列实现的Dijkstra算法适用于稀疏图，暴力法实现的Dijkstra算法适用于稠密图。
*/
public class ShortestPathDijkstraPriorityQueue {
    public int[] shortestPath(int n, int[][] edges, int s) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        int[] dis = new int[n]; // 记录0到i的最短距离
        Arrays.fill(dis, Integer.MAX_VALUE);
        dis[s] = 0;
        // 这里的int[]记录[节点, 最短距离]
        PriorityQueue<int[]> q = new PriorityQueue<>((x, y) -> {
            return x[1] < y[1] ? -1 : 1;
        });
        q.offer(new int[]{s, 0});
        while (!q.isEmpty()) {
            int[] arr = q.poll();
            int node = arr[0];
            int distance = arr[1];
            /* 这行continue不要也能正确，若distance > dis[node]，说明q中前面已有distance更小的[node, distance]，q中的这个arr
            不需要使用进行计算。[oi wiki](https://oi-wiki.org/graph/shortest-path/#%E5%AE%9E%E7%8E%B0_2)上是用了个visited数组，这里是if (vis[u]) continue;
            不写这行continue会影响效率，但不致导致死循环，先看这行代码在何种情况下起作用，例如：
            开始是源点0，然后0把1，2入队，然后1先出队，把3入队，此时0到3的路径是0->1->3距离可能是1+4=5，
            然后2出队，也把3入队，此时0到3的路径是0->2->3距离可能是2+2=4，于是[dis=5, node=3]会比[dis=4, node=3]
            后出队，但是[dis=5, node=3]出队其实际不会导致任何更新，所以可以剪掉，所以说这里只是剪掉了注定无意义的尝试更新计算，
            并不导致外层while (!q.isEmpty())循环次数的变化，但是能把无意义的for (neighbor)循环剪掉，用完全图来想，是能优化时间复杂度的，
            加上这行，只有第一次出队时会跑一遍for (neighbor)；删去这行，会跑多遍无意义的for (neighbor)，只有第一次是有用的。
            算法其它部分保证了不会发生死循环，所以去掉这行continue也不会发生死循环。
            */
            if (distance > dis[node]) continue;
            for (int[] neighbor : graph.get(node)) {
                int next = neighbor[0];
                int w = neighbor[1];
                /* 要判断通过了才offer()，如果把`q.offer(new int[]{next, dis[next]});`放到if {}块后面，
                可能会发生死循环，比如1出队把2加入队列，2出队又把1加入，推进队列的距离都是最短距离，上面`if (distance > dis[node]) continue;`
                的判断挡不住。把上面改成if (distance >= dis[node])，又会导致根节点一出队算法直接就退出了。
                改成`q.offer(new int[]{next, distance + w});`倒是能放到if {}块后面，但是这样做只会增加往优先队列里丢垃圾的情况，没有意义。
                
                如果有负权环，例如无向图节点1 - 2之间有条权为-10000的边，即使有这个判断也会死循环。
                */
                if (distance + w < dis[next]) {
                    dis[next] = distance + w;
                    q.offer(new int[]{next, dis[next]});
                }
            }
        }
        return dis;
    }

    public static void main(String[] args) {
        ShortestPathDijkstraPriorityQueue spdpq = new ShortestPathDijkstraPriorityQueue();
        int s = 0;
        System.out.println("源节点" + s + "到其它节点的最短距离分别为: " + Arrays.toString(spdpq.shortestPath(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}, s)));
    }
}
