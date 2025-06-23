/*
url: https://leetcode.cn/problems/largest-rectangle-in-histogram/description/
LeetCode参考: https://leetcode.cn/problems/largest-rectangle-in-histogram/solutions/266844/zhu-zhuang-tu-zhong-zui-da-de-ju-xing-by-leetcode-/
相关: LeetCode1793. 好子数组的最大分数, LeetCode42. 接雨水, LeetCode2334. 元素值大于变化阈值的子数组, LeetCode907. 子数组的最小值之和, LeetCode2454. 下一个更大元素 IV
      LeetCode85. 最大矩形
标签: 单调栈, 子数组的最小值, 单调栈出栈元素性质
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

    /* 参考官方题解，将两次单调栈合并为一次，但是要做一点妥协。考虑从左到右求左侧第一个小于heights[i]的那次循环，当i使得单调栈中元素x出栈时，
    此时有heights[x] >= heights[i]，且(x,i)中间的元素都是大于heights[x]的，否则x应该早已经在这些元素的循环轮中被弹出，因此此时i是出栈元素x
    右侧第一个**小于等于**height[x]的位置。虽然这里是小于等于，但是整体并不会导致错误，因为当多个等高的柱子并排时，最大的矩形面积会在最右边那
    个柱子那里算出来。
    */
    public int largestRectangleArea_implementation2(int[] heights) {
        int n = heights.length;
        int[] left = new int[n]; // 用单调栈求出nums[i]左侧第一个**小于**nums[i]的位置
        int[] right = new int[n]; // 顺便求出nums[i]右侧第一个**小于等于**nums[i]的位置
        Arrays.fill(right, n);
        Deque<Integer> stack = new LinkedList<>();
        // 单次循环即可
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                int x = stack.pop();
                right[x] = i;
            }
            left[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }
        int ans = 0;
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
        System.out.println(solu.largestRectangleArea_implementation2(new int[]{2,1,5,6,2,3}));
    }
}
