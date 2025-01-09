/*
url: https://leetcode.cn/problems/maximum-subarray/
题目简述: 给你一个整数数组nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
相关: https://leetcode.cn/problems/maximum-sum-circular-subarray/
      如果改成子数组不需要连续，应该和[最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)解法类似
      https://leetcode.cn/problems/house-robber/
      LeetCode3410. 删除所有值为某个元素后的最大子数组和
其它参考: https://zhuanlan.zhihu.com/p/144385162
*/

public class Solution53 {
    public int maxSubArray(int[] nums) {
        // dp[i]代表以nums[i]为结尾的子数组的最大和，dp[i] = Math.max(nums[i], nums[i] + dp[i - 1])，然后dp[]中最大的值为全局最大值
        // dp需要这样设是因为子数组要求连续，如果将dp设为nums[0..i]中的最大子数组和，在递推时无法保证子数组连续
        int[] dp = new int[nums.length];
        dp[0] = nums[0]; // 最大子数组非空，所以初始值为nums[0]
        int max = nums[0];
        for (int i = 1; i < nums.length; i++) {
            dp[i] = Math.max(nums[i], nums[i] + dp[i - 1]);
            max = Math.max(dp[i], max);
        }
        return max;
    }

    // 另外一种实现，减小空间复杂度
    public int maxSubArray_Implementation2(int[] nums) {
        int currentMax = nums[0];
        int max = nums[0];
        for (int i = 1; i < nums.length; i++) {
            currentMax = Math.max(currentMax + nums[i], nums[i]);
            max = Math.max(max, currentMax);
        }
        return max;
    }

    public int maxSubArray_implementation3(int[] nums) {
        int max = nums[0];
        int sum = 0;
        for (int i = 0; i < nums.length; i++) {
            sum += nums[i];
            /* sum <= 0，找到了一个最短的非正的前缀部分，则最大和的连续子数组一定与其无交。
            即，对nums[0, n - 1]，若发现其前缀nums[0, i] <= 0，则nums的最大连续子数组一定与这个前缀sum无交，
            否则:sum
                  ------（代表最大连续子数组）
            交的这部分一定和为正，否则后半部分才是最大子数组，这样一来，sum的前半段一定为负，但这与sum是最短的非正前缀违背。从而无交。
            因此，刚找到一个非正的前缀部分，就将其立刻丢掉，然后问题变为求丢掉前缀后的nums'的最大连续子数组。
            具体可参考邓俊辉老师2023Fall-all版数据结构讲义第87页，<https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/>。
            */
            if (sum > max) max = sum;
            if (sum <= 0) sum = 0;
        }
        return max;
    }

    // 分治版本，最大子数组要么在左半，要么在右半，要么跨中间，从mid位置往两边延伸。复杂度O(n^2)不过可以一看，会超时。
    // 原因在于没有充分利用子递归得到的信息来更新自己，而是自己暴力从中间往两边延伸，实际从子递归得到的信息足以O(1)更新自己
    public int maxSubArray_tle(int[] nums) {
        return maxSubArray_divideAndConquer(nums, 0, nums.length);
    }

    private int maxSubArray_divideAndConquer(int[] nums, int lo, int hi) {
        if (hi - lo < 2) return nums[lo];
        int mi = (lo + hi) / 2;
        // hi - lo >= 2，mi - 1和mi都不越界
        int maxL = nums[mi - 1], sumL = 0;
        for (int i = mi - 1; i >= 0; i--) {
            if (maxL < (sumL += nums[i])) maxL = sumL;
        }
        int maxR = nums[mi], sumR = 0;
        for (int i = mi; i < hi; i++) {
            if (maxR < (sumR += nums[i])) maxR = sumR;
        }
        return Math.max(maxL + maxR, Math.max(maxSubArray_divideAndConquer(nums, lo, mi), maxSubArray_divideAndConquer(nums, mi, hi)));
    }

    /* 线段树的分治，更多内容见`LeetCode3410. 删除所有值为某个元素后的最大子数组和`，这里相当于只把线段树build出来就完了，不需要更新
    为了知道当前区间的最大子数组和ans，若不跨中点，则在左/右子区间之一，若跨中点，则为左子区间的最大suf + 右子区间的最大pre，
    为了求pre和suf，同样分治，以pre为例，为max(左子区间pre, 左子区间sum + 右子区间pre)，因此还需要维护一个sum
    */
    class Info {
        int ans, pre, suf, sum; // 分别表示当前区间的最大子数组和, 最大前缀子数组和, 最大后缀子数组和, 区间总和

        public Info(int ans, int pre, int suf, int sum) {
            this.ans = ans;
            this.pre = pre;
            this.suf = suf;
            this.sum = sum;
        }
    }

    public int maxSubArray_implementation4(int[] nums) {
        return build(nums, 0, nums.length - 1).ans;
    }

    public Info build(int[] nums, int s, int t) {
        if (s == t) return new Info(nums[s], nums[s], nums[s], nums[s]);
        int m = (s + t) / 2;
        Info a = build(nums, s, m);
        Info b = build(nums, m + 1, t);
        Info info = new Info(
            Math.max(Math.max(a.ans, b.ans), a.suf + b.pre),
            Math.max(a.pre, a.sum + b.pre),
            Math.max(b.suf, b.sum + a.suf),
            a.sum + b.sum
        );
        return info;
    }

    public static void main(String[] args) {
        Solution53 solu = new Solution53();
        System.out.println(solu.maxSubArray(new int[]{1, 2, -1}));
        System.out.println(solu.maxSubArray_implementation3(new int[]{1, 2, -1}));
        System.out.println(solu.maxSubArray_implementation4(new int[]{1, 2, -1}));
    }
}