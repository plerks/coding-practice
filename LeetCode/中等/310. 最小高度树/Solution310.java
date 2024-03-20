/*
url: https://leetcode.cn/problems/minimum-height-trees/description/?envType=daily-question&envId=2024-03-17
LeetCode参考: https://leetcode.cn/problems/minimum-height-trees/solutions/1397905/by-ac_oier-7xio/
              https://leetcode.cn/problems/minimum-height-trees/solutions/1395249/zui-xiao-gao-du-shu-by-leetcode-solution-6v6f/
其它参考: https://oi-wiki.org/graph/tree-basic/
          https://oi-wiki.org/graph/tree-diameter/
          https://oi-wiki.org/dp/tree/
我的题解: https://leetcode.cn/problems/minimum-height-trees/solutions/2699018/shu-xing-dp-shi-yong-oi-wikizhong-qiu-sh-k5qf/
相关: 典型问题/树的直径
标签: 树动态规划, 换根动态规划, 树形dp, 树的定义, 树的直径, bfs, dfs, 拓扑排序
*/

import java.util.*;

// 这题难度上应该是困难题的难度，再加上解法也多，内容很多
public class Solution310 {
    // 暴力枚举根节点，67 / 71 个通过的测试用例, 超时，由于在反复读树，由此想到类似LeetCode2581的树根dp
    /* List<Integer> ans = new ArrayList<>();
    int minHeight = Integer.MAX_VALUE;
    
    public List<Integer> findMinHeightTrees_exceed_time_limit(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        for (int i = 0; i < n; i++) {
            int height = dfs(i, graph, -1); // dfs返回树高
            if (height == minHeight) ans.add(i);
            else if (height < minHeight) {
                minHeight = height;
                ans.clear();
                ans.add(i);
            }
        }
        return ans;
    }

    // 这里如同LeetCode2368, LeetCode2581, LeetCode2867，树以节点和边形式给出时，树的dfs不用visited数组，只需记录父节点即可
    private int dfs(int root, List<List<Integer>> graph, int parent) {
        int height = 0; // 若root为叶节点，则不会进下面的循环，则高度为0
        for (int child : graph.get(root)) {
            if (child != parent) {
                height = Math.max(height, 1 + dfs(child, graph, root));
            }
        }
        return height;
    } */


    /* 参考宫水三叶的题解的解法，虽然感觉要用树换根dp，但是当树根从当前的根u切到儿子v时，根v会多出一棵子树u，这个子树u走的方向是相反的，
    仅仅知道u的高度不行，因为之前求出的height[u]是把v当儿子的，但此时v是根，u的高度还包含v是子树的情况，不知道怎么求这一支的高度。
    */
    int[] height1;
    int[] height2;
    int[] upMaxDis;

    public List<Integer> findMinHeightTrees(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        this.height1 = new int[n]; // 记录子树高度
        this.height2 = new int[n]; // 记录子树次高度(非严格小于下的次高)
        /* 当树根从当前的根u切到儿子v时，根v会多出一棵子树u，v可以到u然后尽量走远，这支很不好求，但是妙就妙在这支可以dp算，
        因为这个的最大距离要么是v到u然后加上upMaxDis[u]，要么是v到u再算上u往下走的子树高度(不能考虑以v为根的子树，只能走其它的) */
        this.upMaxDis = new int[n];
        // 以0号节点为根，dfs预处理求出height1和height2
        dfs(0, graph, -1);
        redfs(0, graph, -1);
        List<Integer> ans = new ArrayList<>();
        int minHeight = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int height = Math.max(height1[i], upMaxDis[i]); // 以i为根时的树高
            if (height < minHeight) {
                minHeight = height;
                ans.clear();
                ans.add(i);
            }
            else if (height == minHeight) {
                ans.add(i);
            }
        }
        return ans;
    }

    private int dfs(int root, List<List<Integer>> graph, int parent) {
        for (int child : graph.get(root)) {
            if (child != parent) {
                int height = 1 + dfs(child, graph, root);
                if (height > height1[root]) {
                    int temp = height1[root];
                    height1[root] = height;
                    height2[root] = temp;
                }
                else if (height > height2[root]) {
                    height2[root] = height;
                }
            }
        }
        return height1[root];
    }

    // 再dfs一遍求出upMaxDis
    // 这个递归过程一开始的根是不需要求upMaxDis的，所以递归实例的行为设置成根去更新儿子，而非儿子用根更新自己(这种需要判断parent!=-1)
    private void redfs(int root, List<List<Integer>> graph, int parent) {
        for (int child : graph.get(root)) {
            if (child != parent) {
                upMaxDis[child] = Math.max(upMaxDis[child], 1 + upMaxDis[root]); // 往上走到父亲，然后父亲往上走的情况
                
                /* 这里按照宫水三叶题解评论区的[评论](https://leetcode.cn/problems/minimum-height-trees/solutions/1397905/by-ac_oier-7xio/comments/1926604/)提示，
                对于考虑往上走到父亲u然后再往下走到非子树v的情况，不需要记录u的最高子树的根节点是谁。
                因为除开子树v的最大子树高度一定是最大值和次大值之一，只需判断是否height[u]==heigth[v]+1然后决定取最大还是次大即可
                */
                // 往上走到父亲u然后再往下走到非v的子树的情况
                upMaxDis[child] = Math.max(upMaxDis[child], height1[child] + 1 == height1[root] ? 1 + height2[root] : 1 + height1[root]);
                redfs(child, graph, root);
            }
        }
    }

    /* 官方题解解法一，找相距最远的两个节点x,y。x,y正中的一个或两个节点为根时树的高度最小。
    找相距最远节点对的方法是：
        1. 以任意节点p开始，利用广度优先搜索或者深度优先搜索找到以p为起点的最长路径的终点x
        2. 以节点x出发，找到以x为起点的最长路径的终点y
        3. x到y之间的路径即为图中的最长路径
    题解并没有考虑所有相距最远节点对，只考虑了一对就可以。原因应该是这样：
    假设存在u，v，其与x，y同为相距最远节点对，则u，v路径的正中节点(一个或两个)一定与x，y的正中节点相同。
    证明：
    考虑以x，y正中节点为根的树，树中任意两点u，v的唯一那条简单路径应该是从u到二者的最近公共祖先lca(u,v)再到v，即u - lca(u,v) - v。
    由[树的定义](https://oi-wiki.org/graph/tree-basic/)，任意两点之间的简单路径只有一条，以某一节点为根时，能找出一条路径u - lca(u,v) - v，那么以任意节点为根时的路径u - lca(u,v) - v都是相同的(路径相同，但不同根时lca不同)。
    现在只以x，y只有一个正中节点r的情况为例，考虑以r为根的树，类似题解的第二个结论的证明过程：u，v的路径必须经过r(也就说明在树r中lca(u,v)是r)，否则u，v之间的距离不够。
    现在证明u，v的正中节点也一定是r，由于u，v的路径经过r，则说明u，v位于r的两侧，同时x，y也位于r的两侧，不妨设u与x在同一侧。
    则x,y和u,v的路径为x...r...y和u...r...v，这里设路径x...r和u...r分别为p1，p2，r...y和r...v分别为q1，q2。则有|p1|=|p2|，|q1|=|q2|，
    若不然，则p1，p2中的较大者p和q1，q2中的较大者q构成的路径pq将会是更长的路径，与x，y和u，v同为最长路径矛盾。
    综上，即便有多条最长路径，其正中节点一定相同，只用考虑一条即可，同时也有结论，ans的size只会是1或2。
    */
    // 树中相距最远的节点是[树的直径](https://oi-wiki.org/graph/tree-diameter/)问题
    public List<Integer> findMinHeightTrees_implementation2(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        int[] parent = new int[n];
        // bfs找相距最远节点
        int x = findLongestNode(0, parent, graph);
        int y = findLongestNode(x, parent, graph);
        // x, y是距离最远的一对节点
        List<Integer> path = new ArrayList<>();
        while (y != -1) {
            path.add(y);
            y = parent[y];
        }
        List<Integer> ans = new ArrayList<>();
        int size = path.size();
        if (size % 2 == 0) {
            ans.add(path.get(size / 2 - 1));
            ans.add(path.get(size / 2));
        }
        else ans.add(path.get(size / 2));
        return ans;
    }

    private int findLongestNode(int s, int[] parent, List<List<Integer>> graph) {
        int n = parent.length;
        Deque<Integer> q = new LinkedList<>();
        q.offer(s);
        parent[s] = -1;
        boolean[] visited = new boolean[n];
        int d = 0;
        while (!q.isEmpty()) {
            int node = q.poll();
            visited[node] = true;
            for (int neighbor : graph.get(node)) {
                if (!visited[neighbor]) {
                    d = neighbor;
                    parent[neighbor] = node;
                    q.offer(neighbor);
                }
            }
        }
        return d;
    }

    // 官方题解解法二，dfs找相距最远节点
    public List<Integer> findMinHeightTrees_implementation3(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        int[] parent = new int[n];
        // dfs找相距最远节点
        int x = findLongestNode_2(0, parent, graph);
        int y = findLongestNode_2(x, parent, graph);
        // x, y是距离最远的一对节点
        List<Integer> path = new ArrayList<>();
        while (y != -1) {
            path.add(y);
            y = parent[y];
        }
        List<Integer> ans = new ArrayList<>();
        int size = path.size();
        if (size % 2 == 0) {
            ans.add(path.get(size / 2 - 1));
            ans.add(path.get(size / 2));
        }
        else ans.add(path.get(size / 2));
        return ans;
    }

    private int findLongestNode_2(int s, int[] parent, List<List<Integer>> graph) {
        int n = parent.length;
        parent[s] = -1;
        // 这里也可以用一个类属性maxDis和maxNode来做，优化掉dis数组的使用，但是这题实现方式太多了，少弄点类属性免得太混乱
        int[] dis = new int[n];
        Arrays.fill(dis, -1);
        dis[s] = 0;
        dfs(s, graph, dis, parent);
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

    private void dfs(int root, List<List<Integer>> graph, int[] dis, int[] parent) {
        for (int neighbor : graph.get(root)) {
            if (dis[neighbor] == -1) { // 避免dfs返回去
                dis[neighbor] = dis[root] + 1;
                parent[neighbor] = root;
                dfs(neighbor, graph, dis, parent);
            }
        }
    }

    // 官方题解解法三，反复按轮除去所有叶子节点，直到剩下的节点数<=2，剩下的就是最长路径的正中节点
    public List<Integer> findMinHeightTrees_implementation4(int n, int[][] edges) {
        if (n == 1) return Arrays.asList(0);
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        int[] degrees = new int[n];
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
            degrees[edge[0]]++;
            degrees[edge[1]]++;
        }
        int remain = n;
        Deque<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            if (degrees[i] == 1) {
                q.offer(i);
            }
        }
        while (remain > 2) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int node = q.poll();
                for (int neighbor : graph.get(node)) {
                    degrees[neighbor]--;
                    if (degrees[neighbor] == 1) {
                        q.offer(neighbor);
                    }
                }
            }
            remain -= size;
        }
        List<Integer> ans = new ArrayList<>();
        while (!q.isEmpty()) {
            ans.add(q.poll());
        }
        return ans;
    }

    // oi wiki上求树的直径的思路，dp时不用考虑往上走，只用考虑向下，具体原因见`典型问题/树的直径`和`我的题解.md`中的说明
    public List<Integer> findMinHeightTrees_implementation5(int n, int[][] edges) {
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
        int node = 0; // 在以0号节点为根的树中，最长路径对应的子树根
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
        List<Integer> ans = new ArrayList<>();
        int size = path.size();
        if (size % 2 == 0) {
            ans.add(path.get(size / 2 - 1));
            ans.add(path.get(size / 2));
        }
        else ans.add(path.get(size / 2));
        return ans;
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
        Solution310 solu = new Solution310();
        System.out.println(solu.findMinHeightTrees(4, new int[][]{{1,0},{1,2},{1,3}}));
        Solution310 solu2 = new Solution310();
        System.out.println(solu2.findMinHeightTrees(2, new int[][]{{0,1}}));
        Solution310 solu3 = new Solution310();
        System.out.println(solu3.findMinHeightTrees(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));

        Solution310 solu4 = new Solution310();
        System.out.println(solu4.findMinHeightTrees_implementation2(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));
        System.out.println(solu4.findMinHeightTrees_implementation3(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));
        System.out.println(solu4.findMinHeightTrees_implementation4(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));

        Solution310 solu5 = new Solution310();
        System.out.println(solu5.findMinHeightTrees_implementation5(6, new int[][]{{3,0},{3,1},{3,2},{3,4},{5,4}}));
        System.out.println(solu5.findMinHeightTrees_implementation5(10, new int[][]{{0,1},{0,2},{0,3},{2,4},{0,5},{5,6},{6,7},{2,8},{7,9}}));
    }
}
