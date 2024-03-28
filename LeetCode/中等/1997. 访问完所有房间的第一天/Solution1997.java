/*
url: https://leetcode.cn/problems/first-day-where-you-have-been-in-all-the-rooms/description/?envType=daily-question&envId=2024-03-28
LeetCode参考: https://leetcode.cn/problems/first-day-where-you-have-been-in-all-the-rooms/solutions/979221/qian-zhui-he-you-hua-dp-by-endlesscheng-j10b/
标签: 动态规划, 前缀和, 特殊动态规划
*/

// 这题的动态规划很特别，这题从0开始会怎么走是完全确定的，没有类似"从多种情况转移来"的选择这种特征，但是却可以用dp
public class Solution1997 {
    public int firstDayBeenInAllRooms(int[] nextVisit) {
        /* 这题我只能想到模拟，想了一下能不能像`LeetCode2258. 逃离火灾`一样二分，结论是不行，这里和那题不太一样，这题对t二分
        ，check()的代价完全就是t从0递增模拟，不如直接t从0递增模拟。看了一下题解的关键词是dp和前缀和才分析出来怎么做。 */

        /* 注意数据范围，0 <= nextVisit[i] <= i，到达i位置时，要么跳回到以前的位置，要么向右走一步，不会往右边跳
        一个关键的性质是，当到达i位置时，[0,i)的访问次数一定是偶数，这可以归纳证明，到达i位置时，由归纳假设，[0,i-1)的
        访问次数是偶数，下面只需证明i-1位置的访问次数是偶数：若i-1位置访问次数是奇数，当最后一次(奇数次)到达i-1时，说明
        这时候要回跳，若回跳到i-1位置，则i-1的访问次数为偶数，若跳到[0,i-1)的位置，由归纳假设[0,i-1)的访问次数是偶数，
        相当于初始一次都没访问过的状态，因此跳回去后一定会在跳回去的位置重复开启那个过程，最后会再走到i-1位置，因此i-1位置
        的访问次数是偶数。归纳完毕。
        这样一来，当在i位置跳回到x位置后，会重复x位置开启的路径，然后把i位置的访问次数变为偶数，这样一来，相当于走了前面路径的一部分，
        比如nextVisit = [0,0,2]，路径为0,0,1,0，这最后返回0时会重复之前的路径。于是就具备了前缀和的特征。
        */
        int n = nextVisit.length;
        final int MOD = 1_000_000_007;
        // dp[i][0]为第一次从0位置到达i位置1次的路径步数，dp[i][1]为第一次从0位置到达i位置2次的路径步数
        long[][] dp = new long[n][2];
        dp[0][0] = 1;
        dp[0][1] = 2;
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][1] + 1;
            // 这里+MOD要和题解写得一样，不然会出现负数
            dp[i][1] = (dp[i][0] + (dp[i][0] - dp[nextVisit[i]][0] + 1) + MOD) % MOD; // 第一次到达i位置会回退到nextVisit[i]位置，再走一遍那条路
        }
        return (int)dp[n - 1][0] - 1; // 最终答案为第一次到达n-1位置的步数，但是用第0天就可以访问完0号房间，所以要减1
    }

    // 参考灵茶山艾府题解，不需要用二维数组，一维就行了
    public int firstDayBeenInAllRooms_implementation2(int[] nextVisit) {
        int n = nextVisit.length;
        final int MOD = 1_000_000_007;
        long[] dp = new long[n]; // dp[i]表示第一次到i位置的天数
        for (int i = 1; i < n; i++) {
            // dp[i]等于：第一次到i-1位置，返回，然后再走到i-1位置（dp[i - 1] - dp[nextVisit[i - 1]] + 1，+1是因为闭区间），再走一步到i位置
            dp[i] = (dp[i - 1] + dp[i - 1] - dp[nextVisit[i - 1]] + 1 + 1 + MOD) % MOD; // +MOD防止算出负数
        }
        return (int)dp[n - 1];
    }
    public static void main(String[] args) {
        Solution1997 solu = new Solution1997();
        System.out.println(solu.firstDayBeenInAllRooms(new int[]{0,0,2}));
        System.out.println(solu.firstDayBeenInAllRooms_implementation2(new int[]{0,0,2}));
    }
}