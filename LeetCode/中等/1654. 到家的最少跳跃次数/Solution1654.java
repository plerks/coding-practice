/*
url: https://leetcode.cn/problems/minimum-jumps-to-reach-home/
LeetCode参考: https://leetcode.cn/problems/minimum-jumps-to-reach-home/solutions/2414842/dao-jia-de-zui-shao-tiao-yue-ci-shu-by-l-sza1/
标签: 跳跃, 步数
*/

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashSet;
import java.util.Set;

public class Solution1654 {

    /* 这个dp的解法能过一些用例（60 / 96 个通过的测试用例），但是是错的。原因在于，以a << b为例，
    可能存在... a a b a的跳跃情况能够到达某个位置，但是下面代码的循环里i已经大于了这个位置，因此会认为这个位置不可达，实际是可达的。
    */
    public int minimumJumps_incorrect(int[] forbidden, int a, int b, int x) {
        int[] dp = new int[x + 2 * b];
        // -10000是为了在+1时不要溢出为负，避免比较大小时出现错误
        Arrays.fill(dp, Integer.MAX_VALUE - 10000);
        dp[0] = 0;
        HashSet<Integer> set = new HashSet<>();
        for (int val : forbidden) set.add(val);
        for (int i = 1; i < dp.length; i++) {
            if (set.contains(i)) continue;
            if (i - a >= 0) dp[i] = Math.min(dp[i], dp[i - a] + 1);
            if (i + b < dp.length) dp[i] = Math.min(dp[i], dp[i + b] + 1);
            if (i + a < dp.length) dp[i + a] = Math.min(dp[i + a], dp[i] + 1);
            if (i - b >= 0) dp[i - b] = Math.min(dp[i - b], dp[i] + 1);
        }
        return dp[x] >= Integer.MAX_VALUE - 10000 ? -1 : dp[x];
    }

    // bfs
    public int minimumJumps(int[] forbidden, int a, int b, int x) {
        Deque<int []> q = new ArrayDeque<>();
        q.add(new int[]{0, 1, 0});
        // upper = max(max(forbidden)+a,x)+b 
        int upper = 0;
        for (int val : forbidden) {
            upper = Math.max(upper, val);
        }
        upper = Math.max(upper + a, x) + b;
        Set<Integer> visited = new HashSet<>();
        visited.add(0);
        Set<Integer> forbiddenSet = new HashSet<>();
        for (int val : forbidden) {
            forbiddenSet.add(val);
        }
        while (!q.isEmpty()) {
            int[] arr = q.poll();
            int position = arr[0], direction = arr[1], step = arr[2];
            if (position == x) {
                return step;
            }
            // 会优先尝试以前进的方式到达目标位置（步数小）
            if (!visited.contains(position + a) && position + a <= upper && !forbiddenSet.contains(position + a)) {
                visited.add(position + a);
                q.offer(new int[]{position + a, 1, step + 1});
            }
            // 不能连退2次
            if (direction != -1) {
                if (!visited.contains(- (position - b)) && position - b >= 0 && !forbiddenSet.contains(position - b)) {
                    // 表示是后退到的position - b这个点
                    visited.add(- (position - b));
                    q.offer(new int[]{position - b, -1, step + 1});
                }
            }
        }
        return -1;
    }

    // dfs
    public int minimumJumps_implementation2(int[] forbidden, int a, int b, int x) {
        int upper = 0;
        for (int val : forbidden) {
            upper = Math.max(upper, val);
        }
        upper = Math.max(upper + a, x) + b;
        Set<Integer> visited = new HashSet<>();
        visited.add(0);
        Set<Integer> forbiddenSet = new HashSet<>();
        for (int val : forbidden) {
            forbiddenSet.add(val);
        }
        myMinimumJumps_implementation2(forbidden, a, b, x, 0, 0, 0, upper, visited, forbiddenSet);
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }

    private int ans = Integer.MAX_VALUE;

    private void myMinimumJumps_implementation2(int[] forbidden, int a, int b, int x, int position, int direction, int step, int upper, Set<Integer> visited, Set<Integer> forbiddenSet) {
        /* if (position == x) {
            ans = Math.min(ans, step);
            return;
        } */
        if (position == x) {
            if (ans == Integer.MAX_VALUE) {
                // 第一次成功到达x位置就是最短步数，因为递归是先尝试往前走
                ans = step;
            }
            return;
        }
        if (position + a <= upper && !visited.contains(position + a) && !forbiddenSet.contains(position + a)) {
            visited.add(position + a);
            myMinimumJumps_implementation2(forbidden, a, b, x, position + a, 1, step + 1, upper, visited, forbiddenSet);
        }
        if (direction != -1 && position - b >= 0 && !visited.contains(- (position - b)) && !forbiddenSet.contains(position - b)) {
            visited.add(- (position - b));
            myMinimumJumps_implementation2(forbidden, a, b, x, position - b, -1, step + 1, upper, visited, forbiddenSet);
        }
    }

    public static void main(String[] args) {
        Solution1654 solu = new Solution1654();
        System.out.println(solu.minimumJumps_implementation2(new int[]{14,4,18,1,15}, 3, 15, 9));
        Solution1654 solu2 = new Solution1654();
        System.out.println(solu2.minimumJumps_implementation2(new int[]{15}, 1, 1, 5));
    }
}