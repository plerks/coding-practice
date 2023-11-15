// https://leetcode.cn/problems/longest-even-odd-subarray-with-threshold/?envType=daily-question&envId=2023-11-16

public class Solution2760 {
    public int longestAlternatingSubarray(int[] nums, int threshold) {
        int ans = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] % 2 == 1 || nums[i] > threshold) continue;
            int count = 1;
            ans = Math.max(ans, 1);
            while (i + 1 < nums.length && nums[i + 1] % 2 != nums[i]  % 2 && nums[i + 1] <= threshold) {
                count++;
                ans = Math.max(ans, count);
                i++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2760 solu = new Solution2760();
        System.out.println(solu.longestAlternatingSubarray(new int[]{2,3,3,10}, 18));
    }
}
