/*
描述: 投掷n个骰子，点数随机1~6，求最终点数之和>=x的概率
参考: https://kriszhang.com/shaizi_google/
*/

public class RollDiceLargerOrEqualX {
    public double rollDicePossibility(int n, int x) {
        return rollDiceCount(n, x) / Math.pow(6, n);
    }

    public int rollDiceCount(int n, int x) {
        if (n == 1) {
            if (x <= 0) return 6;
            else if (x <= 6) return 6 - x + 1;
            return 0;
        }
        int ans = 0;
        for (int i = 1; i <= 6; i++) {
            // 当前骰子投出6种情况，然后递归为n - 1规模的子问题
            ans += rollDiceCount(n - 1, x - i);
        }
        return ans;
    }

    public double rollDicePossibility_implementation2(int n, int x) {
        return rollDiceCount_implementation2(n, x) / Math.pow(6, n);
    }

    public int rollDiceCount_implementation2(int n, int x) {
        if (x <= 0) return (int)Math.pow(6, n);
        // 多加了个1，免得对n个骰子的结果在n - 1行。当x较大时dp矩阵会比较大，可以考虑让每个行向量的长度dp[i].length == 6 * i (i个骰子最多投出总和为6i)，不过会麻烦一些。
        int[][] dp = new int[n + 1][x + 1];
        for (int j = 1; j <= x; j++) {
            if (j <= 6) {
                dp[1][j] = 6 - j + 1;
            }
            else dp[1][j] = 0;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= x; j++) {
                for (int k = 1; k <= 6; k++) {
                    if (j - k <= 1) {
                        dp[i][j] += dp[i - 1][1];
                    }
                    else dp[i][j] += dp[i - 1][j - k];
                }
            }
        }
        return dp[n][x];
    }

    public static void main(String[] args) {
        RollDiceLargerOrEqualX rollDiceLargerOrEqualX = new RollDiceLargerOrEqualX();
        System.out.println(rollDiceLargerOrEqualX.rollDicePossibility(2, 11));
        System.out.println(rollDiceLargerOrEqualX.rollDicePossibility_implementation2(2, 11));
    }
}
