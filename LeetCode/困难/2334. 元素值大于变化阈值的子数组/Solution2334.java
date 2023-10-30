/*
url: https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/
LeetCode参考: https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/solutions/1658410/by-endlesscheng-j6pp/
标签: 单调栈, 用单调栈寻找左侧第一个比当前元素小的元素, 用单调栈寻找右侧第一个比当前元素小的元素
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution2334 {
    /* 子数组越长，threshold/k越大，越容易满足要求，假设候选子数组包含nums[i]，向左右延伸到第一个<nums[i]的位置，记为(left,right)，则:
    1. (left, right)的子数组不会比(left, right)更容易符合要求，因为最小的数没变，但threshold/k变小
    2. 有无可能多包含一个右侧更小的数(nums[right])，虽然最小值变小但是threshold/k变小使之符合要求？这种情况在从nums[right]向左右延伸时会考虑到
    */
    public int validSubarraySize(int[] nums, int threshold) {
        Deque<Integer> stack1 = new LinkedList<>(); // 单调栈
        int[] table1 = new int[nums.length]; // table1[i]为左侧第一个小于nums[i]的位置
        for (int i = 0; i < nums.length; i++) {
            /* 将所有大于等于nums[i]的元素出栈，这不会影响后续对nums[i+1...]的求解。若nums[i+1] > nums[i]，则table1[i+1]=i，
            若nums[i+1] <= nums[i]，则大于等于nums[i]的元素也不会小于nums[i+1] */
            while (!stack1.isEmpty() && nums[stack1.peek()] >= nums[i]) stack1.pop();
            table1[i] = stack1.isEmpty() ? -1 : stack1.peek();
            stack1.push(i);
        }

        Deque<Integer> stack2 = new LinkedList<>();
        int[] table2 = new int[nums.length]; // table2[i]为右侧第一个小于nums[i]的位置
        for (int i = nums.length - 1; i >= 0; i--) {
            while (!stack2.isEmpty() && nums[stack2.peek()] >= nums[i]) stack2.pop();
            table2[i] = stack2.isEmpty() ? nums.length : stack2.peek();
            stack2.push(i);
        }

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > threshold / (table2[i] - table1[i] - 1)) return table2[i] - table1[i] - 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution2334 solu = new Solution2334();
        System.out.println(solu.validSubarraySize(new int[]{1,3,4,3,1}, 6));
    }
}