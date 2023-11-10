/*
url: https://leetcode.cn/problems/search-insert-position/
标签: 二分查找
相关: 典型问题/有序范围内的二分查找
*/

public class Solution35 {
    // 题目假设了nums元素不重复，这里发散一下，假设元素可重复，返回这样的位置: 若nums包含target，返回target的最后出现位置，否则返回target将会被按顺序插入的位置
    public int searchInsert(int[] nums, int target) {
        // 寻找第一个>target的位置，即最后一个<=target的位置+1
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // left现在为第一个>target的位置，left - 1为最后一个<=target的位置，left - 1范围为[-1, nums.length)
        if (left - 1 >= 0 && nums[left - 1] == target) return left - 1; // 即target出现的最后位置
        return left;
    }

    // 这个实现找的是<target的最后一个位置+1，即>=target的第一个位置
    public int searchInsert_implementation2(int[] nums, int target) {
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

    // 题目假设了nums元素不重复，这样写能过。但是若元素可重复，这个写法无法控制命中target时是第几个，若无法命中target，则left - 1是<=target的最大位置，则left是>target的第一个位置
    public int searchInsert_implementation3(int[] nums, int target) {
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
        System.out.println(solu.searchInsert(new int[]{1,3,3,10,30}, 5));
        System.out.println(solu.searchInsert_implementation2(new int[]{1,3,3,3,3,10,30}, 3));
    }
}