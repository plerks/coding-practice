/*
url: https://leetcode.cn/problems/minimum-number-of-operations-to-satisfy-conditions/description/
LeetCode参考: https://leetcode.cn/problems/minimum-number-of-operations-to-satisfy-conditions/solutions/2749283/ji-yi-hua-sou-suo-pythonjavacgo-by-endle-8i0e/
标签: LeetCode第394场周赛, 动态规划, 二维动态规划, 最优次优
*/

public class Solution3122 {
    // 我的解法
    public int minimumOperations(int[][] grid) {
        // 每一列值都相等
        int m = grid.length, n = grid[0].length;
        int[][] count = new int[n][10]; // count[i][j]记录将第i列全修改为j所需次数
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= 9; k++) {
                int cnt = 0;
                for (int i = 0; i < m; i++) {
                    if (grid[i][j] != k) {
                        cnt++;
                    }
                }
                count[j][k] = cnt;
            }
        }
        /* 周赛时写到这里本来是想的要类似八皇后那样递归回溯，然后开始写的时候发现第j列只会被第j-1列影响，
        再前面的不影响，于是有dp的特征，于是反应过来是dp */
        // dp[j][k]记录把[0, j]列变为相符合的情况，且第j列的值为k的情况的最小次数
        int[][] dp = new int[n][10];
        for (int k = 0; k <= 9; k++) {
            dp[0][k] = count[0][k];
        }
        for (int j = 1; j < n; j++) {
            for (int k = 0; k <= 9; k++) {
                int min = Integer.MAX_VALUE;
                for (int pre = 0; pre <= 9; pre++) {
                    if (pre == k) continue;
                    min = Math.min(min, dp[j - 1][pre] + count[j][k]);
                }
                dp[j][k] = min;
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int k = 0; k <= 9; k++) {
            ans = Math.min(ans, dp[n - 1][k]);
        }
        return ans;
    }

    /* 灵茶山艾府题解解法。遍历过程中记录最优次优和最优取的值，这样比dp空间使用更少。
    观察dp的解法，当dp到了第j列时，要求[0,j]列的最优解，需要枚举j和j-1列的取值，
    但是实际只需枚举第j列的取值，若枚举的第j列取值k和第j-1列的最优相等，则第j列取k时
    的最优解是第j-1列取次优，若不等，则第j列取k时的最优解是第j-1列取最优。因此只需在
    遍历过程中记录最优次优和最优取的值就可以了。

    此外灵茶山艾府视频题解中提到了个点，周赛时我默认了变的值一定取0-9，但是这题没说不能变到
    其它值，不过最优解每一列变到的值一定会是取的0-9，这很容易证明。将某一列变到0-9外的其它值
    所需次数一定是行数m，但是变到0-9的某一值次数<=m。若某个最优解需要把某一列变为0-9外的某一
    个数，则将那列变为0-9的某一数(保证和左右列不等即可)一定不会更差，因此只需考虑变为0-9即可。
    */
    public int minimumOperations_implementation2(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        // 这里count[i][j]记录第i列j的出现次数，然后把第i列全变为j所需次数只需用行数m-次数即可，相比上一种解法，循环可以少一层
        int[][] count = new int[n][10];
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                count[j][grid[i][j]]++;
            }
        }
        int min = 0; // [0,j]列所需最小次数
        int subMin = 0; // [0,j]列所需次小次数
        int minVal = -1; // 局部最优解的最右边一列取的值
        for (int j = 0; j < n; j++) {
            // 这一列的3个值
            int tempMin = Integer.MAX_VALUE;
            int tempSubMin = Integer.MAX_VALUE;
            int tempMinVal = -1;
            for (int k = 0; k <= 9; k++) {
                // 第j列取k所需最小次数
                int cnt = k == minVal ? subMin + m - count[j][k] : min + m - count[j][k];
                if (cnt < tempMin) {
                    tempSubMin = tempMin;
                    tempMin = cnt;
                    tempMinVal = k;
                }
                else if (cnt < tempSubMin) {
                    tempSubMin = cnt;
                }
            }
            min = tempMin;
            subMin = tempSubMin;
            minVal = tempMinVal;
        }
        return min;
    }

    public static void main(String[] args) {
        Solution3122 solu = new Solution3122();
        System.out.println(solu.minimumOperations(new int[][]{{1,1,1},{0,0,0}}));
        System.out.println(solu.minimumOperations_implementation2(new int[][]{{1,1,1},{0,0,0}}));
    }
}
