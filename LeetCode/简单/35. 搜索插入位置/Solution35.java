/*
url:  https://leetcode.cn/problems/search-insert-position/
标签: 不小于某元素的最大位置
*/

public class Solution35 {
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] > target) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }

    public int searchInsert_implementation2(int[] nums, int target) {
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] >= target) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }

    public static void main(String[] args) {
        Solution35 solu = new Solution35();
        System.out.println(solu.searchInsert(new int[]{1,3,10,30}, 5));
        System.out.println(solu.searchInsert_implementation2(new int[]{1,3,10,30}, 5));
    }
}