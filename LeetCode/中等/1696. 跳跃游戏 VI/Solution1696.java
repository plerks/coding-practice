/*
url: https://leetcode.cn/problems/jump-game-vi/description/?envType=daily-question&envId=2024-02-05
相关: LeetCode239. 滑动窗口最大值
标签: 单调队列, 最大队列, 滑动窗口, 跳跃游戏
*/

import java.util.*;

public class Solution1696 {
    // 58 / 72 个通过的测试用例，超时
    public int maxResult_exceedTimeLimit(int[] nums, int k) {
        int n = nums.length;
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MIN_VALUE);
        dp[0] = nums[0];
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k && i - j >= 0; j++) {
                dp[i] = Math.max(dp[i], dp[i - j] + nums[i]);
            }
        }
        return dp[n - 1];
    }

    // 计算dp[i]时需要前k个元素的最大值，因此想到最大队列或单调队列
    public int maxResult(int[] nums, int k) {
        int n = nums.length;
        Deque<Integer> q = new LinkedList<>();
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MIN_VALUE);
        dp[0] = nums[0];
        q.offer(0);
        for (int i = 1; i < n; i++) {
            while (q.peekFirst() < i - k) q.pollFirst();
            dp[i] = Math.max(dp[i], dp[q.peekFirst()] + nums[i]);
            while (!q.isEmpty() && dp[q.peekLast()] <= dp[i]) {
                q.pollLast();
            }
            q.offerLast(i);
        }
        return dp[n - 1];
    }

    // 用的典型问题/最大队列，57 / 72 个通过的测试用例，也是会超时
    public int maxResult_exceedTimeLimit2(int[] nums, int k) {
        int n = nums.length;
        MaxQueue q = new MaxQueue();
        q.enqueue(nums[0]);
        // 用最大队列求前k个元素的最大值，队列里最多存k个元素
        /* 这里不能直接for (int i = 1; i < n; i++)然后函数末尾return q.getMax()，这样搞最后返回的是dp[n-k]到dp[n-1]的
        最大值而非dp[n-1]，有可能最后一个窗口dp[n-2]最大，而nums[n-1]为负（从而dp[n-2]>dp[n-1]），最后返回的会是dp[n-2]而非dp[n-1]
        */
        for (int i = 1; i < n - 1; i++) {
            q.enqueue(q.getMax() + nums[i]); // 相当于dp[i]入队
            if (i >= k) {
                q.dequeue();
            }
        }
        return q.getMax() + nums[n - 1];
    }

    public static void main(String[] args) {
        Solution1696 solu = new Solution1696();
        System.out.println(solu.maxResult(new int[]{1,-1,-2,4,-7,3}, 2));
        System.out.println(solu.maxResult_exceedTimeLimit(new int[]{1,-1,-2,4,-7,3}, 2));
        System.out.println(solu.maxResult_exceedTimeLimit2(new int[]{1,-1,-2,4,-7,3}, 2));
    }
}

// 典型问题/最大队列
class MaxQueue {
    public Deque<Integer> Q;
    public LinkedList<Integer> P;

    public MaxQueue() {
        this.Q = new LinkedList<>();
        this.P = new LinkedList<>();
    }

    public void dequeue() {
        Q.pollFirst();
        P.pollFirst();
    }

    public void enqueue(int e) {
        Q.offerLast(e);
        for (ListIterator<Integer> it = P.listIterator(P.size()); it.hasPrevious() && it.previous() < e;) {
            it.set(e);
        }
        P.offerLast(e);
    }

    public int getMax() {
        return P.peekFirst();
    }
}