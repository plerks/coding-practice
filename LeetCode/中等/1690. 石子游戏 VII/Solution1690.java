/*
url: https://leetcode.cn/problems/stone-game-vii/description/?envType=daily-question&envId=2024-02-03
LeetCode参考: https://leetcode.cn/problems/stone-game-vii/solutions/2626699/shi-zi-you-xi-vii-by-leetcode-solution-8wqc/
              https://leetcode.cn/problems/stone-game-vii/solutions/2629582/jiao-ni-yi-bu-bu-si-kao-dong-tai-gui-hua-zktx/
相关: LeetCode1686. 石子游戏 VI, LeetCode2029. 石子游戏 IX
标签: 石子游戏, 记忆化搜索, 动态规划, 二维动态规划, 前缀和
*/

public class Solution1690 {
    // 我的想法，结果是错的，过不了[721,979,690,84,742,873,31,323,819,22,928,866,118,843,169,818,908,832,852,480,763,715,875,629]这个用例。思考策略没起效的话，应该是需要一定的枚举，从而往dp上想。
    /* 对Alice，她选一个石子并不能得到这个石子的分，而是得到剩余石子的分，对Bob也是同理。选哪颗石子，就得不到哪颗石子的分，
    若一个人选择这颗石子得不到这颗石子的分，另一个人后面也不会得到。因此选的那颗石子对得分没有影响，但是会对露出的石子有影响，Alice选择
    一颗石子后会露出2颗石子，这两颗的分都已经被Alice得到，而Bob需要在其中二选一从而得不到这两颗之一的分，因此，Alice的选择要露出尽量大的石子，
    让Bob得不到分。轮到Bob时，他的策略也相同。
    关于为什么Bob一定会输，因为Alice和Bob相继选一次，Alice的得分一定更高，而Alice先手，选的次数和Bob相等或者大1。
    */
    public int stoneGameVII_wrong(int[] stones) {
        int n = stones.length;
        int left = 0, right = stones.length - 1;
        int lr = left + 1, rl = right - 1; // lr保持为left + 1, rl保持为right - 1
        int aliceScore = 0, bobScore = 0;
        int[] prefixSum = new int[n];
        for (int i = 0; i < n; i++) prefixSum[i] = (i == 0) ? stones[0] : prefixSum[i - 1] + stones[i];
        while (left <= right) {
            if (left == right) {
                aliceScore += 0;
                break;
            }
            // 露出尽量大的给Bob，让他只能选个大的石子，无法得到这个大石子的分
            if (Math.min(stones[lr], stones[right]) > Math.min(stones[left], stones[rl])) { // 选left位置的石子,求和(left,right]
                aliceScore += prefixSum[right] - prefixSum[left];
                left++;
                lr = left + 1;
            }
            else if (Math.min(stones[lr], stones[right]) < Math.min(stones[left], stones[rl])) { // 选right位置的石子，求和[left,right)
                aliceScore += prefixSum[right] - prefixSum[left] - stones[right] + stones[left];
                right--;
                rl = right - 1;
            }
            else { // 相等，留大的，让自己得分，将大的留在边缘让对方更容易不得不选
                if (stones[left] > stones[right]) { // 选right
                    aliceScore += prefixSum[right] - prefixSum[left] - stones[right] + stones[left];
                    right--;
                    rl = right - 1;
                }
                else {
                    aliceScore += prefixSum[right] - prefixSum[left];
                    left++;
                    lr = left + 1;
                }
            }
            // 轮到Bob，他会变成Alice同样的处境
            if (left <= right) {
                if (left == right) {
                    bobScore += 0;
                    break;
                }
                if (Math.min(stones[lr], stones[right]) > Math.min(stones[left], stones[rl])) { // 选left位置的石子,求和(left,right]
                    bobScore += prefixSum[right] - prefixSum[left];
                    left++;
                    lr = left + 1;
                }
                else if (Math.min(stones[lr], stones[right]) < Math.min(stones[left], stones[rl])) { // 选right位置的石子，求和[left,right)
                    bobScore += prefixSum[right] - prefixSum[left] - stones[right] + stones[left];
                    right--;
                    rl = right - 1;
                }
                else { // 相等，留大的
                    if (stones[left] > stones[right]) { // 选right
                        bobScore += prefixSum[right] - prefixSum[left] - stones[right] + stones[left];
                        right--;
                        rl = right - 1;
                    }
                    else {
                        bobScore += prefixSum[right] - prefixSum[left];
                        left++;
                        lr = left + 1;
                    }
                }
            }
        }
        return aliceScore - bobScore;
    }

    // 自顶向下，用记忆化搜索优化递归
    public int stoneGameVII(int[] stones) {
        int n = stones.length;
        int[] prefixSum = new int[n];
        for (int i = 0; i < n; i++) prefixSum[i] = (i == 0) ? stones[0] : prefixSum[i - 1] + stones[i];
        int[][] memo = new int[n][n];
        return dfs(0, n - 1, prefixSum, memo, stones);
    }

    /* dfs()表示面对当前情况时当前人所能达到的最大得分差，Alice和Bob二人都会采取最佳策略，因此dfs()不需要额外参数记录当前轮到了谁。
    若无记忆化搜索，时间复杂度为O(2^n)，有记忆化搜索，一共有O(n^2)个子状态需要计算，时间复杂度为O(n^2)。
    */
    private int dfs(int i, int j, int[] prefixSum, int[][] memo, int[] stones) {
        if (i == j) return 0;
        if (memo[i][j] != 0) { // 1 <= stones[i]，得分差一定为正，可以用0表示初始状态
            return memo[i][j];
        }
        // 当前的人选i或者选j
        // 这里本来需要写prefixSum[j - 1] - prefixSum[i - 1]，需要判断是否下标为-1，参考题解让prefixSum数组长为n+1，prefixSum[0]额外存了个0，这样就不用额外判断。这里采用prefixSum[j] - prefixSum[i] -stones[j] + stones[i]的写法，可以让下标不产生减1
        int max = Math.max(prefixSum[j] - prefixSum[i] - dfs(i + 1, j, prefixSum, memo, stones), prefixSum[j] - prefixSum[i] -stones[j] + stones[i] - dfs(i, j - 1, prefixSum, memo, stones));
        memo[i][j] = max;
        return max;
    }

    // 自底向上，dp
    public int stoneGameVII_implementation2(int[] stones) {
        int n = stones.length;
        int[][] dp = new int[n][n]; // dp[i][j]表示一个人面对stones[i, j]时能实现的最大得分差
        int[] prefixSum = new int[n + 1]; // 在prefixSum[0]多填一个0，减少后续下标边界情况的判断，但是注意使用prefixSum时下标要偏移1，感觉prefixSum[j] - prefixSum[i] -stones[j] + stones[i]的写法更好想
        for (int i = 1; i < n + 1; i++) prefixSum[i] = prefixSum[i - 1] + stones[i - 1];
        // dp[i][j] = max(sum[i + 1,j] - dp[i + 1][j], sum[i,j - 1] - dp[i][j - 1])
        // 根据这个递推关系，要让i从大到小，j从小到大，且j>i
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j <= n - 1; j++) {
                dp[i][j] = Math.max(prefixSum[j + 1] - prefixSum[i + 1] - dp[i + 1][j], prefixSum[j] - prefixSum[i] - dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }

    public static void main(String[] args) {
        Solution1690 solu = new Solution1690();
        // System.out.println(solu.stoneGameVII(new int[]{5,3,1,4,2}));
        System.out.println(solu.stoneGameVII(new int[]{1,1,1,1,1,1,1,7,1,1,1,1,1,1,1}));
        System.out.println(solu.stoneGameVII_implementation2(new int[]{1,1,1,1,1,1,1,7,1,1,1,1,1,1,1}));
    }
}
