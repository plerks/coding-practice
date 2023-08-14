/*
url: https://leetcode.cn/problems/remove-element/
相关: https://leetcode.cn/problems/merge-sorted-array/
标签: 双指针
*/

public class Solution27 {
    public int removeElement(int[] nums, int val) {
        if (nums.length == 0) return 0;
        int left = 0;
        int right = nums.length - 1;
        int ans = nums.length;
        while (right >= 0 && nums[right] == val) {
            right--;
            ans--;
        }
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[right];
                nums[right] = val;
                ans--;
                right--;
                while (nums[right] == val && left < right) {
                    right--;
                    ans--;
                }
            }
            left++;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution27 solu = new Solution27();
        System.out.println(solu.removeElement(new int[]{1}, 1));
    }
}