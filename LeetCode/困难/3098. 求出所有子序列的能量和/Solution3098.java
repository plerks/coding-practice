/*
url: https://leetcode.cn/problems/find-the-sum-of-subsequence-powers/description/
LeetCode参考: https://www.bilibili.com/video/BV19t421g7Pd/
              https://leetcode.cn/problems/find-the-sum-of-subsequence-powers/solutions/2717262/ji-yi-hua-sou-suo-xuan-huo-bu-xuan-by-sp-hmc1/
相关: LeetCode2386. 找出数组的第 K 大和
标签: 子序列, 幂集递归, 记忆化搜索, 动态规划

*/

import java.util.*;

public class Solution3098 {
    final int MOD = (int)1e9 + 7;
    Map<String, Long> memo;

    // 参考灵茶山艾府视频题解和这篇[题解](https://leetcode.cn/problems/find-the-sum-of-subsequence-powers/solutions/2717262/ji-yi-hua-sou-suo-xuan-huo-bu-xuan-by-sp-hmc1/)
    public int sumOfPowers(int[] nums, int k) {
        Arrays.sort(nums); // 打乱顺序后选取仍然是子序列，只要将顺序恢复回原来的相对顺序即可，类似`LeetCode2386. 找出数组的第 K 大和`
        memo = new HashMap<>();
        /* 注意这里pre和min的初始值，除以2是为了防溢出，pre是Integer.MIN_VALUE / 2，这样当第一个元素加入后，此时本来不会有两个元素的差，
        因此这时第一个数-pre会极大，最终不会影响正确性 */
        return (int)dfs(0, k, Integer.MIN_VALUE / 2, Integer.MAX_VALUE, nums); // dfs()求出从0位置开始，选k个数的所有可能能量值之和
    }

    /* 幂集递归的类似方式，每个位置考虑选或不选，然后再从剩下的部分选够数，这里要dp求子序列能量，由于进行了排序，当新加入一个数时，
    只需将新加入的数与相邻数比较，再与之前的最小差比较即可。这会是指数级别的复杂度，但是子问题可以用记忆化搜索。
    */
    // i,count,pre,min分别表示当前要决定选或不选的位置，还要选的个数，上一个选的数，当前已选的数的最小差
    private long dfs(int i, int count, int pre, int min, int[] nums) {
        String key = i + "#" + count + "#" + pre + "#" + min;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        int n = nums.length;
        if (n - i < count) return 0;
        if (count <= 0) return min;
        long energy1 = dfs(i + 1, count - 1, nums[i], Math.min(min, nums[i] - pre), nums); // 选i
        long energy2 = dfs(i + 1, count, pre, min, nums); // 不选i
        memo.put(key, (energy1 + energy2) % MOD);
        return (energy1 + energy2) % MOD;
    }

    public static void main(String[] args) {
        Solution3098 solu = new Solution3098();
        // System.out.println(solu.sumOfPowers(new int[]{1,2,3,4}, 3));
        System.out.println(solu.sumOfPowers(new int[]{4,3,-1}, 2));
    }
}
