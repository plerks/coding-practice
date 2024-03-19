/*
url: https://leetcode.cn/problems/maximum-score-of-a-good-subarray/description/?envType=daily-question&envId=2024-03-19
LeetCode参考: https://leetcode.cn/problems/maximum-score-of-a-good-subarray/solutions/2695415/liang-chong-fang-fa-dan-diao-zhan-shuang-24zl/
相关: LeetCode42. 接雨水, LeetCode84. 柱状图中最大的矩形, LeetCode2334. 元素值大于变化阈值的子数组, LeetCode907. 子数组的最小值之和
标签: 单调栈, 双指针, 子数组的最小值
*/

import java.util.*;

public class Solution1793 {
    // 容易想到的单调栈解法，枚举最小值所在的位置，然后尽量向两边扩展
    public int maximumScore(int[] nums, int k) {
        int n = nums.length;
        int[] left = new int[n]; // 用单调栈求出nums[i]左侧第一个小于nums[i]的位置
        int[] right = new int[n]; // 用单调栈求出nums[i]右侧第一个小于nums[i]的位置
        Deque<Integer> stack = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && nums[stack.peek()] >= nums[i]) {
                stack.pop();
            }
            left[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }
        stack.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && nums[stack.peek()] >= nums[i]) {
                stack.pop();
            }
            right[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }
        int ans = 0;
        // 枚举nums[i]成为最小值，能左右扩展到的最大范围通过left, right求出
        for (int i = 0; i < n; i++) {
            int low = left[i];
            int high = right[i];
            if (low + 1 > k || high - 1 < k) continue;
            ans = Math.max(ans, nums[i] * (high - 1 - (low + 1) + 1));
        }
        return ans;
    }

    // 参考题解，用双指针，双指针移动有技巧，这题双指针从k往两边走，`LeetCode42. 接雨水`的双指针从两边往中间走
    public int maximumScore_implementation2(int[] nums, int k) {
        int n = nums.length;
        int minHeight = nums[k];
        int ans = nums[k] * 1;
        int lo = k, hi = k;
        for (int i = 0; i < n - 1; i++) { // 一共移动n - 1次
            /* 每次移动，谁大就移动谁，这样在尽力保持当前minHeight的同时让宽度尽可能大。
            参考题解，这样双指针的正确性在于，这样不会错过最优解。假设最优解的左右位置在L和R，
            假设lo先到达L，此时hi < R，由于[L, R]是最优解，则对[L, R]范围内，nums[i] >= min[L, R]，且
            nums[L - 1] < min[L, R]，则后续一定是hi连续移动到R，因此不会错过最优解[L, R]。hi先到达R同理。
            这样双指针移动只需O(n)时间而非枚举两个端点的O(n^2)，且每次按步移动也能O(1)时间求出最小值。

            这题的双指针还可以和`LeetCode2300. 咒语和药水的成功对数`结合起来看下，第一反应都不是双指针但是都可以用双指针
            来解，能用双指针的题目有时候也暗含一定的单调性。
            */
            if (hi == n - 1 || (lo > 0 && nums[lo - 1] > nums[hi + 1])) {
                minHeight = Math.min(minHeight, nums[lo - 1]);
                lo--;
            }
            else {
                minHeight = Math.min(minHeight, nums[hi + 1]);
                hi++;
            }
            ans = Math.max(ans, minHeight * (hi - lo + 1));
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1793 solu = new Solution1793();
        System.out.println(solu.maximumScore(new int[]{1,4,3,7,4,5}, 3));
        System.out.println(solu.maximumScore_implementation2(new int[]{1,4,3,7,4,5}, 3));
    }
}
