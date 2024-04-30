/*
url: https://leetcode.cn/problems/climbing-stairs/
LeetCode参考: https://leetcode.cn/problems/climbing-stairs/solutions/286022/pa-lou-ti-by-leetcode-solution/
相关: LeetCode746. 使用最小花费爬楼梯
标签: 动态规划, 转为矩阵乘, 矩阵快速幂
*/

public class Solution70 {
    public int climbStairs(int n) {
        int[] dp = new int[n + 1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    public int climbStairs_implementation2(int n) {
        int prev = 1, prevPrev = 1, current = 1; // current初值为1，因为可能n==1进不了下面的for循环
        for (int i = 2; i <= n; i++) {
            current = prevPrev + prev;
            prevPrev = prev;
            prev = current;
        }
        return current;
    }

    /* 参考LeetCode题解，还可以像求fibonacci(n)一样改成矩阵形式，然后用矩阵快速幂。这里f(x) = f(x - 1) + f(x - 2),
    则[f(x), f(x - 1)] = A[f(x - 1), f(x - 2)]，其中A为{{1, 1}, {1, 0}}，实际上，f(x) = f(x - 1) + f(x - 2)正是fibonacci的递推式
    */

    public static void main(String[] args) {
        Solution70 solu = new Solution70();
        System.out.println(solu.climbStairs_implementation2(3));
    }
}
