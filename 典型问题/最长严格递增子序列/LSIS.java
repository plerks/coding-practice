/*
描述: 求数组的最长严格递增子序列的长度
参考: https://leetcode.cn/problems/longest-increasing-subsequence/solutions/147667/zui-chang-shang-sheng-zi-xu-lie-by-leetcode-soluti/
      https://leetcode.cn/problems/longest-increasing-subsequence/solutions/2147040/jiao-ni-yi-bu-bu-si-kao-dpfu-o1-kong-jia-4zma/
      https://www.bilibili.com/video/BV1ub411Q7sB/
相关: LeetCode300. 最长递增子序列, LeetCode1671. 得到山形数组的最少删除次数, LeetCode2407. 最长递增子序列 II
*/

import java.util.*;

// 此问题与`LeetCode300. 最长递增子序列`完全相同，LeetCode300虽然题目名字是最长递增子序列，但是实际描述是求最长严格递增子序列

public class LSIS { // Longest Strict Increasing Subsequence
    // 动态规划，时间复杂度O(n^2)
    public int lengthOfLIS(int[] nums) {
        int[] dp = new int[nums.length]; // dp[i]表示以nums[i]结尾的最长严格递增子序列长度
        dp[0] = 1;
        int max = 1;
        for (int i = 1; i < nums.length; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                    max = Math.max(max, dp[i]);
                }
                else {
                    dp[i] = Math.max(1, dp[i]);
                }
            }
        }
        return max;
    }

    // 参考题解，贪心 + 二分查找，时间复杂度O(nlogn)，非常奇妙
    // 这里d的定义与上面解法的dp数组定义是反过来的，dp[i]是以nums[i]结尾的长度，d[i]是长度为i的最小末尾nums值
    public int lengthOfLIS_implementation2(int[] nums) {
        /* 如果要让某一长度的递增子序列尽量还能扩展，对于使用nums某一局部的数来构成递增子序列，那么应该贪心地让其增长得尽量缓慢。
        使用d[i]表示递增子序列长度为i的情况下的末尾的最小值，遍历nums，当遍历到nums[0 ... x]时，若发现nums[x]可以让某一长度的递增子序列
        的末尾值变小，则更新它。
        两个关键点:
        1. d[i]是关于i严格单增的，否则，若有i < j且d[i] >= d[j]，则长度为j对应的严格递增子序列的前缀有一个长度为i的严格递增子序列，
        且分出的子序列(长度为i)的末尾值一定能更小，与d[j]的定义矛盾。
        2. 每个遍历一个nums[i]，最多只会修改一个d的元素。若修改了多个位置，会导致d不是严格单调递增的。
        由d的单调性，可以对其二分，找到会修改的那个位置(最多一个)。
        */
        int n = nums.length;
        List<Integer> d = new ArrayList<>();
        // 考虑的子数组范围从局部到整体，这个解法有点像在dp数组前缀范围
        for (int i = 0; i < n; i++) {
            /* 找到d中第一个>=x的值，其由nums[0, i)的元素构成，把那个序列的最后一个元素改成x，在保持了长度相等的情况下把末尾元素变小了。
            其它>=x的值不能这样改，这些子序列也由nums[0, i)的元素构成，但是其中一定不止一个>=x的值，把末尾值替换为x会导致子序列非严格递增子序列。
            */
            int x = nums[i];
            int index = lower_bound(d, x);
            if (index != d.size()) { // 如果d中存在>=x的值，则最长递增子序列的长度不会增长
                d.set(index, x);
            }
            else d.add(x); // 否则，d中最长的那个子序列的末尾<x，拼上x可以构成一个长度+1的严格递增子序列
        }
        return d.size();
    }

    private int lower_bound(List<Integer> d, int x) {
        // 搜索第一个>=x，转为搜索最后一个<x再加1
        int left = 0, right = d.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (d.get(mid) < x) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left - 1 + 1;
    }

    /* 待做: 问题如果改成求最长非严格递增子序列会怎么样？
    动态规划的解法自然没有问题，但是如果是贪心 + 二分的解法，
    至少d的性质会改变，不一定是"严格"单增的了(仍然是单增的)，当遍历到nums[i](记为x)时，把d分<x, ==x, >x三段来考虑(每段可能为空)。
    新加入的x可以与<=x的d元素拼起来变成长度+1的递增子序列，这时理应检查所有<=x的d[j]，让d[j+1]=min(d[j+1], x)，
    但是这些d[j]都<=x，不会有改变，不用检查，只需考虑第一个>x的d元素(最后一个==x的d元素的右边元素d[j+1])，
    若j+1超出d的长度(没有>x的d元素)，则直接add(x)，否则将d[j+1]更新为x，再右边的d元素若有，则不用变。
    
    大概是这样分析，有心思的时候写下代码就知道了。
    */

    public static void main(String[] args) {
        LSIS solu = new LSIS();
        System.out.println(solu.lengthOfLIS(new int[]{10,9,2,5,3,7,101,18}));
        System.out.println(solu.lengthOfLIS_implementation2(new int[]{10,9,2,5,3,7,101,18}));
    }
}
