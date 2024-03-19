/*
url: https://leetcode.cn/problems/largest-rectangle-in-histogram/description/
相关: LeetCode1793. 好子数组的最大分数, LeetCode42. 接雨水, LeetCode2334. 元素值大于变化阈值的子数组, LeetCode907. 子数组的最小值之和
标签: 单调栈, 子数组的最小值
*/

import java.util.*;

/* 这题和`LeetCode1793. 好子数组的最大分数`非常像，但是这里用双指针不能O(n)时间，LeetCode1793双指针能O(n)时间是因为
固定双指针从k开始，这题双指针还要枚举起点，得O(n^2)时间 */
public class Solution84 {
    public int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int[] left = new int[n]; // 用单调栈求出nums[i]左侧第一个小于nums[i]的位置
        int[] right = new int[n]; // 用单调栈求出nums[i]右侧第一个小于nums[i]的位置
        Deque<Integer> stack = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            left[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }
        stack.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
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
            ans = Math.max(ans, heights[i] * (high - 1 - (low + 1) + 1));
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution84 solu = new Solution84();
        System.out.println(solu.largestRectangleArea(new int[]{2,1,5,6,2,3}));
    }
}
