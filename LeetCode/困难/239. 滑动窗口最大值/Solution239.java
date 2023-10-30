/*
url: https://leetcode.cn/problems/sliding-window-maximum/
LeetCode参考: https://leetcode.cn/problems/sliding-window-maximum/solutions/543426/hua-dong-chuang-kou-zui-da-zhi-by-leetco-ki6m/
标签: 单调队列, 用单调队列求区间内最大值
*/

import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class Solution239 {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        int[] ans = new int[n - k + 1];
        Deque<Integer> q = new LinkedList<>(); // 单调(往队首递增)队列，用于求解区间内的最大值
        // 初始的队列
        for (int i = 0; i < k; i++) {
            // 新元素i入队，**注意**，由于i是目前最靠右的，也就是说是最后移除的，以下移除的元素<=nums[i]且比i更快出队，当不了最大值，因此可以放心移除
            while (!q.isEmpty() && nums[q.peekLast()] <= nums[i]) {
                q.pollLast();
            }
            q.offerLast(i);
        }
        ans[0] = nums[q.peek()];
        for (int i = k; i < n; i++) {
            while (!q.isEmpty() && nums[q.peekLast()] <= nums[i]) {
                q.pollLast();
            }
            q.offerLast(i);
            // 此时区间为[i - k + 1, i]，求最大值时，若不在区间范围内则全部移除
            while (q.peekFirst() < i - k + 1) {
                q.pollFirst();
            }
            ans[i - k + 1] = nums[q.peek()];
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution239 solu = new Solution239();
        System.out.println(Arrays.toString(solu.maxSlidingWindow(new int[]{7,2,4}, 2)));
    }
}
