/*
url: https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/
相关: https://leetcode.cn/problems/maximal-score-after-applying-k-operations/
*/

import java.util.PriorityQueue;

class Solution2208 {
    public int halveArray(int[] nums) {
        int ans = 0;
        double sum = 0;
        PriorityQueue<Double> pq = new PriorityQueue<>((x, y) -> {
            return y - x > 0 ? 1 : -1;
            // 不能return (int) (y - x);比如0.1转为int变为0，会认为相等
        });
        for (int i = 0; i < nums.length; i++) {
            pq.offer((double)nums[i]);
            sum += nums[i];
        }
        double currentSum = sum;
        while (sum - currentSum < sum / 2) {
            double max = pq.poll();
            pq.offer(max / 2);
            currentSum = currentSum - (max - max / 2);
            ans++;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2208 solu = new Solution2208();
        System.out.println(solu.halveArray(new int[]{3, 8, 20}));
    }
}