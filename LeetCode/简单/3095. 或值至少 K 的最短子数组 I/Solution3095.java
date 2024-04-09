/*
url: https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-i/description/
相关: LeetCode3097. 或值至少为 K 的最短子数组 II
*/

public class Solution3095 {
    // 此题与`LeetCode3097. 或值至少为 K 的最短子数组 II`完全相同，不过这题被标记为简单题，因此暴力也能过用例
    public int minimumSubarrayLength(int[] nums, int k) {
        int n = nums.length;
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int orSum = 0;
            for (int j = i; j >= 0; j--) {
                orSum |= nums[j];
                if (orSum >= k) {
                    ans = Math.min(ans, i - j + 1);
                }
            }
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }
    
    public static void main(String[] args) {
        Solution3095 solu = new Solution3095();
        System.out.println(solu.minimumSubarrayLength(new int[]{2,1,8}, 10));
    }
}