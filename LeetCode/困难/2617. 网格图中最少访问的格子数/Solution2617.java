/*
url: https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/description/?envType=daily-question&envId=2024-03-22
LeetCode参考: https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/solutions/2216329/dan-diao-zhan-you-hua-dp-by-endlesscheng-mc50/
              https://leetcode.cn/problems/minimum-number-of-visited-cells-in-a-grid/solutions/2693762/wang-ge-tu-zhong-zui-shao-fang-wen-de-ge-944f/
标签: 单调栈, 二分查找, 动态规划, 优先队列, 走格子
*/

import java.util.*;

public class Solution2617 {
    // 直接思路，1052 / 1069 个通过的测试用例，超时。
    public int minimumVisitedCells_exceed_time_limit(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] dp = new int[m][n];
        for (int[] arr : dp) Arrays.fill(arr, Integer.MAX_VALUE); // dp[i][j]表示从(0,0)到(i,j)的步数
        dp[0][0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 1; k <= grid[i][j] && j + k < n; k++) {
                    if (dp[i][j] == Integer.MAX_VALUE) break;
                    dp[i][j + k] = Math.min(dp[i][j + k], dp[i][j] + 1);
                }
                for (int k = 1; k <= grid[i][j] && i + k < m; k++) {
                    if (dp[i][j] == Integer.MAX_VALUE) break;
                    dp[i + k][j] = Math.min(dp[i + k][j], dp[i][j] + 1);
                }
            }
        }
        return dp[m - 1][n - 1] == Integer.MAX_VALUE ? -1 : dp[m - 1][n - 1];
    }

    /* 参考官方题解，用优先队列。题解的考虑方式是反过来的，不是考虑(i,j)能到达哪些点，而是(i,j)能从哪些点到达，
    依次尝试当前行列步数最少的，若其到达不了目前位置，则可以直接去掉这种点，因为其一定也到达不了更后面的点。
    */
    public int minimumVisitedCells(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] dp = new int[m][n];
        for (int[] arr : dp) Arrays.fill(arr, Integer.MAX_VALUE);  // dp[i][j]表示从(0,0)到(i,j)的步数
        List<PriorityQueue<int[]>> row = new ArrayList<>();
        List<PriorityQueue<int[]>> col = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            row.add(new PriorityQueue<>((x, y) -> x[0] - y[0]));
        }
        for (int j = 0; j < n; j++) {
            col.add(new PriorityQueue<>((x, y) -> x[0] - y[0]));
        }
        dp[0][0] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                PriorityQueue<int[]> q = row.get(i);
                // 丢掉不可达当前位置(及更右位置的)
                while (!q.isEmpty() && q.peek()[1] + grid[i][q.peek()[1]] < j) {
                    q.poll();
                }
                if (!q.isEmpty()) {
                    dp[i][j] = Math.min(dp[i][j], dp[i][q.peek()[1]] + 1);
                }
                q = col.get(j);
                while (!q.isEmpty() && q.peek()[1] + grid[q.peek()[1]][j] < i) {
                    q.poll();
                }
                if (!q.isEmpty()) {
                    dp[i][j] = Math.min(dp[i][j], dp[q.peek()[1]][j] + 1);
                }
                if (dp[i][j] != Integer.MAX_VALUE) {
                    row.get(i).offer(new int[]{dp[i][j], j});
                    col.get(j).offer(new int[]{dp[i][j], i});
                }
            }
        }
        return dp[m - 1][n - 1] == Integer.MAX_VALUE ? -1 : dp[m - 1][n - 1];
    }

    /* 参考灵茶山艾府的题解，使用单调栈+二分。这个解法非常奇妙。设f[i][j]为从(i,j)到达(m-1,n-1)的步数，
    则f[i][j]的下一步要么向右走，要么向下走，然后就相当于成为了求递归中更深的子问题。逆向遍历i，j(相当于递归的返回过程)，当轮到
    求f[i][j]时，其可以通过已经计算出的右侧和下侧的f值得出，而当f[i][j]一旦得知，在计算f[i][j]左边的值f[i-x][j]时，
    f[i][j]右边的>=f[i][j]的元素f[i+y][j]就没有用了，因为若(i-x,j)通过到达(y,j)再到终点，其一定能以更小或相等的步数到达(i,j)再
    到终点(注意，这里f[i][j]的定义是从(i,j)到终点的步数)。因此对于步数来说，行列的f是有单调栈的特性的，且对计算f[i][j]，
    只需查找其右和其下单调栈里在grid[i][j]范围内步数最小的来更新自己即可，而由于维护的是步数单调栈，可以使用二分查找，只需
    在list里查找index最小的在grid[i][j]范围内的，即是范围内步数最小的。若不把栈维护成单调栈，则查找范围内步数最小的得线性查找。

    这个解法的奇妙性在于，若正向遍历i,j并考虑dp计算步数，则完全无法使用上述单增栈和二分查找来优化运行时间，关键点应该是在于
    将f[i][j]设为从(i,j)到达(m-1,n-1)的步数，这个设法的性质比设dp[i][j]为从(0,0)到(i,j)的步数的性质更好。

    也正是因为将f[i][j]设为了从(i,j)到达(m-1,n-1)的步数，对i,j的遍历自然是反向的，相当于递归基是最先计算出来的。
    若考虑去设dp[i][j]为从(0,0)到(i,j)的步数，则无论是从dp[i][j]计算右边和下面的dp值，还是从左边和上面计算dp[i][j]，
    都需要线性的枚举(不使用优先队列优化的话)，导致时间复杂度在O(mn(m+n))。
    */
    public int minimumVisitedCells_implementation2(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        ArrayList<int[]> rowStack = new ArrayList<>();
        ArrayList<ArrayList<int[]>> colStacks = new ArrayList<>();
        for (int j = 0; j < n; j++) {
            colStacks.add(new ArrayList<>());
        }
        int step = 0; // step表示f[i][j]
        for (int i = m - 1; i >= 0; i--) {
            rowStack.clear();
            for (int j = n - 1; j >= 0; j--) {
                step = (i == m - 1 && j == n - 1) ? 1 : Integer.MAX_VALUE;
                int g = grid[i][j];
                // 通过行计算f[i][j]，搜索rowStack里在g步内的f里最小的(由于单调栈是往List里add，找index最小的范围内(列号<=j+g)的，即是范围内步数最小的)
                int index = binSearch(rowStack, j + g);
                if (index != rowStack.size()) {
                    step = Math.min(step, rowStack.get(index)[0] + 1); // 这行可以直接写成step = rowStack.get(rowStack.size() - 1)[0] + 1;
                }
                // 通过列计算f[i][j]
                ArrayList<int[]> colStack = colStacks.get(j);
                index = binSearch(colStack, i + g);
                if (index != colStack.size()) {
                    step = Math.min(step, colStack.get(index)[0] + 1);
                }
                // (i,j)可达才加入单调栈中，避免后续从栈中提出来用于计算时再加1会溢出
                if (step != Integer.MAX_VALUE) {
                    // 步数>=f[i][j]，但又比f[i][j]远的，全部需要丢掉，维护成单调栈才能二分查找
                    while (!rowStack.isEmpty() && rowStack.get(rowStack.size() - 1)[0] >= step) {
                        rowStack.remove(rowStack.size() - 1);
                    }
                    rowStack.add(new int[]{step, j});
                    while (!colStack.isEmpty() && colStack.get(colStack.size() - 1)[0] >= step) {
                        colStack.remove(colStack.size() - 1);
                    }
                    colStack.add(new int[]{step, i});
                }
            }
        }
        return step == Integer.MAX_VALUE ? -1 : step; // 最后step会是f[0][0]
    }

    private int binSearch(ArrayList<int[]> stack, int x) {
        // 闭区间写法，区间元素对列号<=j+g从否到是，搜索第一个是
        int left = 0, right = stack.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (stack.get(mid)[1] > x) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left;
    }

    public static void main(String[] args) {
        Solution2617 solu = new Solution2617();
        System.out.println(solu.minimumVisitedCells(new int[][]{{3,4,2,1},{4,2,3,1},{2,1,0,0},{2,4,0,0}}));
        System.out.println(solu.minimumVisitedCells(new int[][]{{3,4,2,1},{4,2,1,1},{2,1,1,0},{3,4,1,0}}));
        System.out.println(solu.minimumVisitedCells(new int[][]{{2,1,0},{1,0,0}}));
        System.out.println(solu.minimumVisitedCells_implementation2(new int[][]{{3,4,2,1},{4,2,3,1},{2,1,0,0},{2,4,0,0}}));
        System.out.println(solu.minimumVisitedCells_implementation2(new int[][]{{3,4,2,1},{4,2,1,1},{2,1,1,0},{3,4,1,0}}));
        System.out.println(solu.minimumVisitedCells_implementation2(new int[][]{{2,1,0},{1,0,0}}));
    }
}
