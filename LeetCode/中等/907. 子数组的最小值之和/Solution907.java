/*
url: https://leetcode.cn/problems/sum-of-subarray-minimums/?envType=daily-question&envId=2023-11-27
相关: LeetCode828. 统计子串中的唯一字符
标签: 单调栈, 子数组集
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution907 {
    public int sumSubarrayMins(int[] arr) {
        int n = arr.length;
        // posL[i]为arr[i]左侧第一个小于arr[i]的位置
        int[] posL = new int[n];
        Deque<Integer> stack = new LinkedList<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && arr[stack.peek()] >= arr[i]) {
                stack.pop();
            }
            posL[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }
        stack.clear();
        // posR[i]为arr[i]右侧第一个小于等于arr[i]的位置
        int[] posR = new int[n];
        for (int i = n - 1; i >= 0; i--) {
            /* 如果这里是arr[stack.peek()] >= arr[i]，则对于[3,3,2,4]，[3,3]就被记了两次，所以要让两个单调栈一个有等号，一个没等号
            */
            while (!stack.isEmpty() && arr[stack.peek()] > arr[i]) {
                stack.pop();
            }
            posR[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }
        long ans = 0;
        int mod = 1000_000_007;
        for (int i = 0; i < n; i++) {
            // nums[i]作为子数组的最小值有多少种情况？(i - posL[i]) * (posR[i] - i)
            ans = (ans + ((long)arr[i]) * (i - posL[i]) * (posR[i] - i)) % mod;
        }
        return (int)ans;
    }

    public static void main(String[] args) {
        Solution907 solu = new Solution907();
        System.out.println(solu.sumSubarrayMins(new int[]{3,1,2,4}));
    }
}
