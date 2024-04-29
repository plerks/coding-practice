/*
url: https://leetcode.cn/problems/find-the-median-of-the-uniqueness-array/description/
LeetCode参考: https://leetcode.cn/problems/find-the-median-of-the-uniqueness-array/solutions/2759114/er-fen-da-an-hua-dong-chuang-kou-pythonj-ykg9/
标签: LeetCode第395场周赛, 中位数, k选取, 二分查找, 滑动窗口, 子数组, 子数组个数
*/

import java.util.*;

// 这周周赛做出来三题，这题想不出来，暴力的话是枚举所有子数组然后算distinct值

public class Solution3134 {
    /* 灵茶山艾府题解，首先考虑如果能把所有子数组的distinct值算出来应该怎么做？
    排序，然后求中间那个数。这里就可以联想到二分答案，非空子数组的个数为C(n,2) + n(n是每个元素单独为一个子数组)，记为m，
    非空子数组个数也可以这样看，以nums[0]为左边界有n个，nums[1]为左边界有n - 1个, ... 一共n + ... + 1。相应的，一个数组的
    子序列(包含空子序列)有2^n个(每个位置选或不选)。

    中位数distinct值是第一个有k = ⌈m/2​⌉个distinct值<=x的值x。而这里的check()可以用滑动窗口。
    */
    public int medianOfUniquenessArray(int[] nums) {
        // 区间对于是否有k个distinct值个数<=x呈现[否 ... 是]变化，二分x，搜索第一个是
        int n = nums.length;
        long m = (long)n * (n + 1) / 2;
        long k = (m + 1) / 2;
        int left = 0, right = n;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (!check(nums, mid, k)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left;
    }

    // 求是否有k个子数组的distinct值<=x
    private boolean check(int[] nums, int x, long k) {
        long count = 0;
        // 移除的时候需要知道frequency，但是统计不同的数的个数只需知道map的size
        Map<Integer, Integer> freq = new HashMap<>();
        int lo = 0;
        for (int hi = 0; hi < nums.length; hi++) {
            freq.merge(nums[hi], 1, Integer::sum);
            while (freq.size() > x) {
                int out = nums[lo];
                if (freq.merge(out, -1, Integer::sum) == 0) {
                    freq.remove(out);
                }
                lo++;
            }
            count += hi - lo + 1; // 以hi为右边界，[lo, hi]任意一个位置为左边界的子数组都满足distinct值<=x
            if (count >= k) return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Solution3134 solu = new Solution3134();
        System.out.println(solu.medianOfUniquenessArray(new int[]{1, 2, 3}));
    }
}