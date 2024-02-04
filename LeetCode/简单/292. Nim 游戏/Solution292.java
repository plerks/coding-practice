/*
url: https://leetcode.cn/problems/nim-game/?envType=daily-question&envId=2024-02-04
LeetCode参考: https://leetcode.cn/problems/nim-game/solutions/1003627/nim-you-xi-by-leetcode-solution-95g8/
相关: LeetCode1690. 石子游戏 VII
标签: 动态规划
*/

public class Solution292 {
    // 超出内存限制，n可能很大
    public boolean canWinNim_exceedMemeoryLimit(int n) {
        if (n <= 3) return true;
        // dp[i]表示一个人面对i规模的问题能否获胜
        boolean[] dp = new boolean[n + 1];
        dp[1] = true;
        dp[2] = true;
        dp[3] = true;
        for (int i = 4; i <= n; i++) {
            // 要赢的话，拿掉1，2，3块石头，对方能有一种的结果是输就行
            dp[i] = !dp[i - 1] || !dp[i - 2] || !dp[i - 3];
            // 或者想成对方要赢的话得在我方选择1，2，3的情况下都赢，否则我方选那种他不赢的就行，这样就是：
            // dp[i] = !(dp[i - 1] && dp[i - 2] && dp[i - 3]);
        }
        return dp[n];
    }

    // 观察n=20的dp结果，f(1-3) = f(13-15)，以12为周期循环(按参考题解其实最小正周期为4)。这里可以选择直接打表。
    public boolean canWinNim(int n) {
        n = (n - 1) % 12 + 1; // 映射为[1,12]的结果，(n - 1) % 12表示离1的距离对12的余数
        if (n <= 3) return true;
        // dp[i]表示一个人面对i规模的问题能否获胜
        boolean[] dp = new boolean[n + 1];
        dp[1] = true;
        dp[2] = true;
        dp[3] = true;
        for (int i = 4; i <= n; i++) {
            // 要赢的话，拿掉1，2，3块石头，对方能有一种的结果是输就行
            dp[i] = !dp[i - 1] || !dp[i - 2] || !dp[i - 3];
            // 或者想成对方要赢的话得在我方选择1，2，3的情况下都赢，否则我方选那种他不赢的就行，这样就是：
            // dp[i] = !(dp[i - 1] && dp[i - 2] && dp[i - 3]);
        }
        return dp[n];
    }

    /* 参考题解的做法，当剩1，2，3块石头时i，可以获胜，当剩4块石头时，一定会输。当剩5，6，7块石头时，己方可以拿1，2，3块石头，使
    剩4块石头，对方一定会输，当剩8块石头时，无论自己选1，2，3对方都能选3，2，1使自己要面对4块石头。因此，只需判断n是否为4的倍数。
    */
    public boolean canWinNim_implementation2(int n) {
        return n % 4 != 0;
    }

    public static void main(String[] args) {
        Solution292 solu = new Solution292();
        System.out.println(solu.canWinNim_exceedMemeoryLimit(12));
        System.out.println(solu.canWinNim(12));
        System.out.println(solu.canWinNim_implementation2(12));
    }
}
