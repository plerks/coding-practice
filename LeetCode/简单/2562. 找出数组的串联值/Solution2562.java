// https://leetcode.cn/problems/find-the-array-concatenation-value/?envType=daily-question&envId=2023-10-12

public class Solution2562 {
    public long findTheArrayConcVal(int[] nums) {
        long ans = 0;
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            if (left == right) ans += nums[left];
            else {
                ans += nums[left] * Math.pow(10, String.valueOf(nums[right]).length());
                ans += nums[right];
            }
            left += 1;
            right -= 1;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2562 solu = new Solution2562();
        System.out.println(solu.findTheArrayConcVal(new int[]{5,14,13,8,12}));
    }
}
