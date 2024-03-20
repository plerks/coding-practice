/*
描述: 树上任意两节点之间最长的简单路径即为树的「直径」
参考: https://oi-wiki.org/graph/tree-diameter/
      https://leetcode.cn/problems/minimum-height-trees/solutions/1395249/zui-xiao-gao-du-shu-by-leetcode-solution-6v6f/
相关: LeetCode310. 最小高度树
标签: 树的直径, 树形dp, 两次dfs, 两次bfs
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class TreeDiameter {
    /*
    找相距最远节点对的方法是：
        1. 以任意节点p开始，利用广度优先搜索或者深度优先搜索找到以p为起点的最长路径的终点x
        2. 以节点x出发，找到以x为起点的最长路径的终点y
        3. x到y之间的路径即为图中的最长路径
    这样做的正确性大致如下:
    如果第一次到达的端点x为直径的一端，则第二次到达的端点y一定是直径的另一端(直径的定义)，于是，只需证明第一次一定会到达直径的一个端点。
    假设一条直径为路径δ(x,y)，第一次从u出发，到达的最远节点其中一个是v，若v是某条直径的端点，则证毕。若不是，则说明δ(u,v) >= δ(u,y)
    1. 若u在x，y这条路径上，则路径δ(x,v) = δ(x,u) + δ(u,v) >= δ(x,y) = δ(x,u) + δ(u,y)，由于δ(x,y)为直径，这里一定
        不能取到大于(否则δ(x,y)不是最长，同时也说明第一次出发到达的最远节点全为直径端点)，因此δ(x,v) == δ(x,y)，于是v也是直径端点，矛盾。因此v是某条直径的端点。
    2. 若u不在x，y这条路径上，则
        情况一：δ(u,v)与δ(x,y)有重叠节点m1,m2,...,mi(i>=1)，不妨设x与u在同一侧，y与v在同一侧，则δ(u,v) >= δ(u,y)，则δ(mi,v) >= δ(mi,y)，则δ(x,v) = δ(x,mi) + δ(mi,v) >= δ(x,y) = δ(x,mi) + δ(mi,y)，
                同样，这里只能取等号，因此v为直径端点。
        情况二：δ(u,v)与δ(x,y)无重叠，则由树的定义，δ(x,y)中间一定有一点m(m可能是x或y)，其能通过简单路径到达δ(u,v)的中间一点n(m != n，n可能是u或v)。则由
                δ(u,v) >= δ(u,y)可知δ(n,v) >= δ(n,m) + δ(m,y) >= δ(m,y)，则δ(x,v) = δ(x,m) + δ(m,n) + δ(n,v) >= δ(x,y) = δ(x,m) + δ(m,y)。
                同样，这里只能取等号，因此v为直径端点。
    综上，第一次到达的最远节点一定全部是某条直径的端点。
    上面2.情况二δ(n,m) + δ(m,y) >= δ(m,y)使用到了条件δ(n,m)>=0，因此：
    "上述证明过程建立在所有路径均不为负的前提下。如果树上存在负权边，则上述证明不成立。故若存在负权边，则无法使用两次DFS的方式求解直径"(oi wiki原话)
    上面2需要分情况一和情况二讨论，主要是如果这样想：若u不在x，y这条路径上，则由树的定义x可以到m，m再到u，u再到v，这样一条x到v的路径不一定是简单路径。
    要充分利用简单路径的局部也是简单路径，证明才是严谨的。
    */
    // 前提: 所有边均不为负。这里以两次dfs为例，还可以用bfs，参考LeetCode310
    private int treeDiameter(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        int[] dis = new int[n];
        int[] parent = new int[n];
        // dfs找相距最远节点
        int x = findLongestNode(0, parent, dis, graph);
        int y = findLongestNode(x, parent, dis, graph);
        int diameter = dis[y];
        List<Integer> path = new ArrayList<>();
        while (y != -1) {
            path.add(y);
            y = parent[y];
        }
        System.out.println("path: " + path);
        return diameter;
    }

    private int findLongestNode(int s, int[] parent, int[] dis, List<List<Integer>> graph) {
        int n = parent.length;
        parent[s] = -1;
        Arrays.fill(dis, -1);
        dis[s] = 0;
        dfs(s, parent, dis, graph);
        int maxDis = 0;
        int node = 0;
        for (int i = 0; i < n; i++) {
            if (dis[i] > maxDis) {
                maxDis = dis[i];
                node = i;
            }
        }
        return node;
    }

    private void dfs(int s, int[] parent, int[] dis, List<List<Integer>> graph) {
        for (int neighbor : graph.get(s)) {
            if (dis[neighbor] < 0) {
                dis[neighbor] = dis[s] + 1;
                parent[neighbor] = s;
                dfs(neighbor, parent, dis, graph);
            }
        }
    }

    /* 树形dp的解法，可以在存在负权边的情况下求解出树的直径。
    只需要记录以某一节点为根时，每个节点向下，在各子树中的最大长度和次大长度(非严格小于意义下的次大)，然后相加能取到的最大值即为直径长度。
    正确性：这样做一定不会错过直径，对于每个节点，算法考虑了其向下走的最长路径。虽然没考虑从这个
    节点往上走的路径，但是这样的路径会在那些上面节点往下时找出。
    或者说，若假定当前节点为路径中的最高节点，则最长路径应该是其往下走的最大长度和次大长度之和，算法
    考虑了所有节点成为最高节点的情况。这里要分子树是为了保证路径是简单路径，走同一颗子树前面的节点是重合的，
    剔除重合节点后，那条路径是更下层的子问题。

    要求直径上所有节点，则可以通过在往下的过程中，记录取到最大长度和次大长度的子树根节点即可
    */
    private int treeDiameter_implementation2(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        int[] dis1 = new int[n]; // 记录往下走的最大长度
        int[] dis2 = new int[n]; // 记录往下走的次大长度
        int[] sub1 = new int[n]; // 记录取最大值的子树根节点
        Arrays.fill(sub1, -1);
        int[] sub2 = new int[n]; // 记录取次大值的子树根节点
        Arrays.fill(sub2, -1);
        dfs(graph, 0, -1, dis1, dis2, sub1, sub2); // 选0号节点作为根
        int diameter = 0;
        int node = 0; // 在以0号节点为根的树中，最长路径的子树根
        for (int i = 0; i < n; i++) {
            if (dis1[i] + dis2[i] > diameter) {
                diameter = dis1[i] + dis2[i];
                node = i;
            }
        }
        List<Integer> path1 = new ArrayList<>();
        List<Integer> path2 = new ArrayList<>();
        int x = sub1[node];
        while (x != -1) {
            path1.add(x);
            x = sub1[x];
        }
        int y = sub2[node];
        while (y != -1) {
            path2.add(y);
            y = sub1[y]; // 注意这里是要用sub1往下走
        }
        List<Integer> path = new ArrayList<>();
        Collections.reverse(path1);
        for (int pathNode : path1) path.add(pathNode);
        path.add(node);
        for (int pathNode : path2) path.add(pathNode);
        System.out.println("path: " + path);
        return diameter;
    }

    private void dfs(List<List<Integer>> graph, int root, int fa, int[] dis1, int[] dis2, int[] sub1, int[] sub2) {
        for (int neighbor : graph.get(root)) {
            if (neighbor != fa) {
                dfs(graph, neighbor, root, dis1, dis2, sub1, sub2);
                int dis = 1 + dis1[neighbor];
                if (dis > dis1[root]) {
                    dis2[root] = dis1[root];
                    sub2[root] = sub1[root];
                    dis1[root] = dis;
                    sub1[root] = neighbor;
                }
                else if (dis > dis2[root]) {
                    dis2[root] = dis;
                    sub2[root] = neighbor;
                }
            }
        }
    }

    public static void main(String[] args) {
        TreeDiameter treeDiameter = new TreeDiameter();
        // 树以节点数和边给出，保证其为树。这里假设树边不带权，即树边权全为1
        System.out.println(treeDiameter.treeDiameter(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));
        TreeDiameter treeDiameter2 = new TreeDiameter();
        System.out.println(treeDiameter2.treeDiameter_implementation2(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));
    }
}
