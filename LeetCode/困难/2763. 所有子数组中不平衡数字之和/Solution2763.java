/*
url: https://leetcode.cn/problems/sum-of-imbalance-numbers-of-all-subarrays/
LeetCode参考: https://leetcode.cn/problems/sum-of-imbalance-numbers-of-all-subarrays/solutions/2327213/onde-by-dengyun-yyl3/
              https://leetcode.cn/problems/sum-of-imbalance-numbers-of-all-subarrays/solutions/2327214/bao-li-mei-ju-pythonjavacgo-by-endlessch-2r7p/
标签: 向左向右查找位置
*/

import java.util.Arrays;

public class Solution2763 {
    public int sumImbalanceNumbers(int[] nums) {
        /* 要求满足sarr[i+1] - sarr[i] > 1的i，若左侧出现了num[i] + 1，则这个num[i] + 1会在sarr中排在num[i]的右边，i无法满足，
        若右侧出现了nums[i]或nums[i] + 1，则其会在sarr中排在num[i]的右边，i无法满足
        */
        int n = nums.length;
        int[] left = new int[n]; // left[i]为nums[i]左侧第一个num[i] + 1的位置，没有则为-1
        int[] right = new int[n]; // right[i]为nums[i]右侧第一个nums[i]或nums[i] + 1的位置，没有则为n
        int[] indexes = new int[n + 1]; // 1 <= nums[i] <= nums.length，用indexes当map，indexes[x]表示x + 1出现的位置
        Arrays.fill(indexes, -1);
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            left[i] = indexes[x];
            indexes[x - 1] = i;
        }
        Arrays.fill(indexes, n);
        for (int i = n - 1; i >= 0; i--) {
            int x = nums[i];
            right[i] = Math.min(indexes[x - 1], indexes[x]);
            indexes[x - 1] = i;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (i - left[i]) * (right[i] - i);
        }
        // 每个子数组的最大值右边没有数，但是会被认为是nums[i] + 1没有出现而计算贡献。而每个子数组都会有个最大值，因此上述过程多加了所有子数组的个数
        return ans - n * (n + 1) / 2;
    }

    public static void main(String[] args) {
        Solution2763 solu = new Solution2763();
        System.out.println(solu.sumImbalanceNumbers(new int[]{2,3,1,4}));
    }
}