/*
url: https://leetcode.cn/problems/5TxKeK/description/?envType=daily-question&envId=2024-02-01
LeetCode参考: https://leetcode.cn/problems/5TxKeK/solutions/2623535/shu-zi-you-xi-by-leetcode-solution-xvte/
相关: LeetCode462. 最小操作次数使数组元素相等 II, LeetCode295. 数据流的中位数, 典型问题/k选取, LeetCode215. 数组中的第K个最大元素
标签: 双优先队列, 中位数, 求流的中位数
*/

import java.util.Arrays;
import java.util.PriorityQueue;

public class SolutionLCP24 {
    /* 我能想到的: 假设求将nums[0,i]的数全变为x的开销最小，则x一定不会小于nums[0,i]的最小值，不大于nums[0,i]的最大值，因为开销为Σ|nums[i] -x|，
    而这表示数轴上nums[i]到x的距离之和，因此最小值一定在某个nums[i]处可以取到(但比如只有两个点，则两个点中的任意点都可以取到最小值)。然后可以遍历
    枚举x为nums[i]中的任意一个值求出对[0,i]的最小开销。但是对于dp[i+1]，又没有从dp[i]转移来的办法（记录dp[i]是变成哪个x也不行）。且这题不是要全变为x，是要变为逐1单增。然后就没想法了。
    */
    public int[] numsGame(int[] nums) {
        // 将nums[0,i]变为逐1单增，等价于把nums[j]-j，0<=j<=i变为相同的值
        int n = nums.length;
        final int MOD = 1_000_000_007;
        // 将[0,i]范围内的数字操作成相同的值的最小次数，在相同值取中位数时取到。参考题目LeetCode462. 最小操作次数使数组元素相等 II

        // 用双优先队列来在遍历nums的过程中求中位数，lower保存的元素<=upper的元素，且所含元素数量关系保持n_upper<=n_lower<=n_upper+1，即lower元素数量比upper大1或相等，应该也可以选择让upper元素数量比lower大1或相等
        PriorityQueue<Integer> lower = new PriorityQueue<>((x,y) -> y - x);
        PriorityQueue<Integer> upper = new PriorityQueue<>((x,y) -> x - y);
        long lowerSum = 0;
        long upperSum = 0;
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            int val = nums[i] - i;
            if (lower.isEmpty() || val <= lower.peek()) { // nums[i]<=lower的最大值
                lower.offer(val);
                lowerSum += val;
            }
            else {
                upper.offer(val);
                upperSum += val;
            }
            // lower的size过大
            if (lower.size() == upper.size() + 2) {
                int temp = lower.poll();
                lowerSum -= temp;
                upper.offer(temp);
                upperSum += temp;
            }
            // upper的size过大
            else if (upper.size() == lower.size() + 1) {
                int temp = upper.poll();
                upperSum -= temp;
                lower.offer(temp);
                lowerSum += temp;
            }
            if ((i + 1) % 2 == 0) { // 一共有偶数个元素，把值全变为[max(lower), min(upper)]中的任一值都可以
                ans[i] = (int)((upperSum - lowerSum) % MOD);
            }
            else { // 一共奇数个元素，中位数为max(lower)
                ans[i] = (int)((upperSum - lowerSum + lower.peek()) % MOD);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        SolutionLCP24 solu = new SolutionLCP24();
        System.out.println(Arrays.toString(solu.numsGame(new int[]{3,4,5,1,6,7})));
    }
}
