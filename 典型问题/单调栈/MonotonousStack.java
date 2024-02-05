/*
描述: 单调栈，可以在时间复杂度为O(n)情况下，求解出某个元素左边或者右边第一个比它大或者小的元素
相关: LeetCode2487. 从链表中移除节点, LeetCode2865. 美丽塔 I, LeetCode901. 股票价格跨度, LeetCode907. 子数组的最小值之和, LeetCode1944. 队列中可以看到的人数
      LeetCode2334. 元素值大于变化阈值的子数组, LeetCode2736. 最大和查询
参考: https://algo.itcharge.cn/03.Stack/02.Monotone-Stack/01.Monotone-Stack/
*/

import java.util.*;

class MonotonousStack {
    public static void main(String[] args) {
        Deque<Integer> stack = new LinkedList<>();
        int[] nums = new int[]{5,1,3,2,4};
        int n = nums.length;
        int[] ans = new int[n];
        // 这里用单调递减栈求nums[i]左侧第一个大于自己的位置
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && nums[stack.peek()] <= nums[i]) {
                /* 这里pop了一些比nums[i]小的元素，若后续的元素比nums[i]小，
                则其左侧第一个大于自己的元素就是nums[i]，若比nums[i]大，这些pop的元素也不会是解，因此pop掉不会有问题
                */
                stack.pop();
            }
            ans[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }
        System.out.println(Arrays.toString(ans));
    }
}
