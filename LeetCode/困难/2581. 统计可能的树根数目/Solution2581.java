/*
url: https://leetcode.cn/problems/count-number-of-possible-root-nodes/description/?envType=daily-question&envId=2024-02-29
LeetCode参考: https://leetcode.cn/problems/count-number-of-possible-root-nodes/solutions/2654312/tong-ji-ke-neng-de-shu-gen-shu-mu-by-lee-3gzg/
              https://leetcode.cn/problems/count-number-of-possible-root-nodes/solutions/2147714/huan-gen-dppythonjavacgo-by-endlesscheng-ccwy/
标签: 动态规划, 树动态规划, 换根动态规划, 树形dp, 树以节点边给出时的dfs, 树的dfs, 进制表示法
*/

import java.util.*;

public class Solution2581 {
    // 我的解法，37 / 51 个通过的测试用例，超时
    public int rootCount(int[][] edges, int[][] guesses, int k) {
        int n = edges.length + 1;
        int ans = 0;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] arr : edges) {
            graph.get(arr[0]).add(arr[1]);
            graph.get(arr[1]).add(arr[0]);
        }
        for (int i = 0; i < n; i++) {
            if (isPossibleRoot(i, graph, guesses, k)) {
                ans++;
            }
        }
        return ans;
    }

    private boolean isPossibleRoot(int root, List<List<Integer>> graph, int[][] guesses, int k) {
        int n = graph.size();
        int[] parent = new int[n];
        Arrays.fill(parent, -1);
        dfs(root, graph, parent, -1);
        int count = 0; // 正确猜测数量
        for (int[] edge : guesses) {
            int u = edge[0];
            int v = edge[1];
            if (parent[v] == u) count++;
            if (count >= k) return true;
        }
        return count >= k;
    }

    // 树以节点边的形式给出，用pre即可防止返回去访问，不需要用visited[]记录，LeetCode2867. 统计树中的合法路径数目有用到这个技巧
    private void dfs(int root, List<List<Integer>> graph, int[] parent, int pre) {
        for (int child : graph.get(root)) {
            if (child != pre) {
                parent[child] = root;
                dfs(child, graph, parent, root);
            }
        }
    }

    /* 参考题解的解法，上面解法的问题明显是反复dfs开销太大。优化的关键点在于，若根的尝试顺序按dfs来，当根从x切换到x的子节点y时，只有
    (x, y)这条边的方向会变化，其它的不会，因此可以进行树的换根dp，按dfs的顺序，child的猜测正确数可由root的猜测正确数dp计算
    */
    int ans = 0;
    public int rootCount_implementation2(int[][] edges, int[][] guesses, int k) {
        int n = edges.length + 1;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] arr : edges) {
            graph.get(arr[0]).add(arr[1]);
            graph.get(arr[1]).add(arr[0]);
        }
        int[] parent = new int[n]; // 可以不需要parent数组，dfs的过程中直接就可以计算出count
        Arrays.fill(parent, -1);
        dfs(0, graph, parent, -1);
        HashSet<Integer> set = new HashSet<>();
        for (int[] edge : guesses) {
            int u = edge[0];
            int v = edge[1];
            set.add(u * n + v);
        }
        int count = 0;
        for (int i = 1; i < n; i++) {
            if (set.contains(parent[i] * n + i)) {
                count++;
            }
        }
        redfs(0, graph, set, -1, k, count);
        return ans;
    }

    // 按dfs的顺序切换根
    private void redfs(int root, List<List<Integer>> graph, Set<Integer> set, int pre, int k, int count) {
        if (count >= k) {
            ans++;
        }
        int n = graph.size();
        for (int child : graph.get(root)) {
            if (child != pre) {
                // 根从root切换到root的子节点，会变一条边的方向，(root, child)会变为(child, root)
                // 这里注意不要直接把count的值给-1+1了，这里root有多个分支，每个分支的count都用root的count dp计算出来，不能把count作为全局的数改，而是要通过参数传递
                redfs(child, graph, set, root, k, count - (set.contains(root * n + child) ? 1 : 0) + (set.contains(child * n + root) ? 1 : 0));
            }
        }
    }

    public static void main(String[] args) {
        Solution2581 solu = new Solution2581();
        System.out.println(solu.rootCount(new int[][]{{0,1},{1,2},{1,3},{4,2}}, new int[][]{{1,3},{0,1},{1,0},{2,4}}, 3));
        System.out.println(solu.rootCount_implementation2(new int[][]{{0,1},{1,2},{1,3},{4,2}}, new int[][]{{1,3},{0,1},{1,0},{2,4}}, 3));
        solu.ans = 0;
        System.out.println(solu.rootCount_implementation2(new int[][]{{0,1},{2,0},{0,3},{4,2},{3,5},{6,0},{1,7},{2,8},{2,9},{4,10},{9,11},{3,12},{13,8},{14,9},{15,9},{10,16}}, new int[][]{{8,2},{12,3},{0,1},{16,10}}, 2));
    }
}
