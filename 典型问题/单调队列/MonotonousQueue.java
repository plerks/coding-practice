/*
描述: 单调队列，对于数组nums和窗口大小k，单调队列在O(n)时间内求出nums[0,k-1],nums[1,k],nums[2,k+1],...,nums[n-k,n-1]这些窗口内的最大(小)值
相关: LeetCode239. 滑动窗口最大值, LeetCode1696. 跳跃游戏 VI
*/

import java.util.*;

class MonotonousQueue {
    public static void main(String[] args) {
        int[] nums = new int[]{1,3,-1,-3,5,3,6,7};
        int n = nums.length;
        int k = 3; // 窗口大小
        int[] ans = new int[n - k + 1];
        // 这里用单调递减队列求出每个窗口内的最大值位置
        Deque<Integer> q = new LinkedList<>();
        for (int i = 0; i < n; i++) { // i为窗口右端点
            if (i < k - 1) { // 还没填充完第一个窗口，可以把这个初始化提出去单独做，代码好理解一点
                while (!q.isEmpty() && nums[q.peekLast()] < nums[i]) {
                    q.pollLast();
                }
                q.offerLast(i);
            }
            else {
                // 队尾已有的比nums[i]小的元素可以直接舍弃，因为nums[i]更大且nums[i]生存周期更长
                while (!q.isEmpty() && nums[q.peekLast()] < nums[i]) {
                    q.pollLast();
                }
                q.offerLast(i);
                while (q.peekFirst() < i - k + 1) { // 把队列内过时的元素全丢掉
                    q.pollFirst();
                }
                ans[i - k + 1] = q.peekFirst();
            }
        }
        System.out.println(Arrays.toString(ans));
    }
}
