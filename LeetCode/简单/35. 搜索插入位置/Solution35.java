/*
url: https://leetcode.cn/problems/search-insert-position/
标签: 不小于某元素的最小位置
*/

public class Solution35 {
    public int searchInsert(int[] nums, int target) {
        // >=target的位置可能在nums.length的位置，因为可能target比nums的所有元素都大，现在候选的范围是[0, nums.length]
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
        // 由于left < right, [left, mid]或[mid + 1, right]都是比上一次迭代的[left, right]区间严格变小的
        return left;
    }

    public int searchInsert_incorrect(int[] nums, int target) {
        // >=target的位置可能在nums.length的位置，因为可能target比nums的所有元素都大，现在候选的范围是[0, nums.length]
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
        // 由于left < right, [left, mid]或[mid + 1, right]都是比上一次迭代的[left, right]区间严格变小的
        return left;
    }

    public static void main(String[] args) {
        Solution35 solu = new Solution35();
        System.out.println(solu.searchInsert(new int[]{1,3,3,10,30}, 3));
        System.out.println(solu.searchInsert_incorrect(new int[]{1,3,3,10,30}, 3));
    }
}