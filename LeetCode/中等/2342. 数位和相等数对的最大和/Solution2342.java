/*
url: https://leetcode.cn/problems/max-sum-of-a-pair-with-equal-sum-of-digits/?envType=daily-question&envId=2023-11-18
相关: 典型问题/求前k大
*/

import java.util.*;

public class Solution2342 {
    public int maximumSum(int[] nums) {
        Map<Integer, PriorityQueue<Integer>> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int digitSum = getDigitSum(nums[i]);
            if (map.get(digitSum) == null) {
                PriorityQueue<Integer> q = new PriorityQueue<>((x, y) -> x - y);
                map.put(digitSum, q);
                q.offer(nums[i]);
            }
            // 数位和为digitSum的数，存两个最大的就行，其它的不用保存
            else {
                PriorityQueue<Integer> q = map.get(digitSum);
                if (q.size() < 2) q.offer(nums[i]);
                else if (q.peek() < nums[i]) {
                    q.poll();
                    q.offer(nums[i]);
                }
            }
        }
        int ans = -1;
        for (Map.Entry<Integer, PriorityQueue<Integer>> entry : map.entrySet()) {
            PriorityQueue<Integer> q = entry.getValue();
            if (q != null && q.size() == 2) {
                ans = Math.max(ans, q.poll() + q.poll());
            }
        }
        return ans;
    }

    private int getDigitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    public static void main(String[] args) {
        Solution2342 solu = new Solution2342();
        System.out.println(solu.maximumSum(new int[]{18,43,36,13,7}));
    }
}
