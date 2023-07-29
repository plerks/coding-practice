/*
url: https://leetcode.cn/problems/maximal-score-after-applying-k-operations/
相关: https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/
*/

import java.util.PriorityQueue;

public class Solution2530 {
    public long maxKelements(int[] nums, int k) {
        long ans = 0;
        PriorityQueue<Integer> pq = new PriorityQueue<>((x, y) -> {
            return y - x;
        });
        for (int i = 0; i < nums.length; i++) {
            pq.offer(nums[i]);
        }
        for (int i = 0; i < k; i++) {
            int temp = pq.poll();
            ans += temp;
            temp = (int)Math.ceil((double)temp / 3);
            pq.offer(temp);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2530 solu = new Solution2530();
        System.out.println(solu.maxKelements(new int[]{1,10,3,3,3}, 3));
    }
}