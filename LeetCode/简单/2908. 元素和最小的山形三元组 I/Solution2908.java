// https://leetcode.cn/problems/minimum-sum-of-mountain-triplets-i/description/?envType=daily-question&envId=2024-03-29

public class Solution2908 {
    public int minimumSum(int[] nums) {
        // 枚举j，找左边的最小值和右边的最小值
        int n = nums.length;
        int[] minL = new int[n];
        int[] minR = new int[n];
        int min = nums[0];
        minL[0] = Integer.MAX_VALUE;
        for (int i = 1; i < n; i++) {
            min = Math.min(min, nums[i]);
            minL[i] = min;
        }
        min = nums[n - 1];
        minR[n - 1] = Integer.MAX_VALUE;
        for (int i = n - 2; i >= 0; i--) {
            min = Math.min(min, nums[i]);
            minR[i] = min;
        }
        int ans = Integer.MAX_VALUE;
        for (int j = 1; j <= n - 2; j++) {
            if (minL[j] < nums[j] && nums[j] > minR[j]) {
                ans = Math.min(ans, minL[j] + nums[j] + minR[j]);
            }
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }

    public static void main(String[] args) {
        Solution2908 solu = new Solution2908();
        System.out.println(solu.minimumSum(new int[]{8,6,1,5,3}));
        System.out.println(solu.minimumSum(new int[]{5,4,8,7,10,2}));
    }
}
