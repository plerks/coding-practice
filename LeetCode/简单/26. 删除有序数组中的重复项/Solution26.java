/*
url: https://leetcode.cn/problems/remove-duplicates-from-sorted-array/
LeetCode参考: https://leetcode.cn/problems/remove-duplicates-from-sorted-array/solutions/728105/shan-chu-pai-xu-shu-zu-zhong-de-zhong-fu-tudo/
*/

public class Solution26 {
    public int removeDuplicates(int[] nums) {
        int left = 0, right = 0;
        // 题目-10^4 <= nums[i] <= 10^4
        int current = Integer.MIN_VALUE;
        while (right < nums.length) {
            if (nums[right] != current) {
                nums[left++] = nums[right];
                current = nums[right];
            }
            right++;
        }
        return left;
    }

    // [官方](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/solutions/728105/shan-chu-pai-xu-shu-zu-zhong-de-zhong-fu-tudo/)这个不需要依赖nums[i]范围
    public int removeDuplicates_implementation2(int[] nums) {
        int left = 1, right = 1;
        while (right < nums.length) {
            if (nums[right] != nums[right - 1]) {
                nums[left++] = nums[right];
            }
            right++;
        }
        return left;
    }

    public static void main(String[] args) {
        Solution26 solu = new Solution26();
        System.out.println(solu.removeDuplicates_implementation2(new int[]{1,2,2,3}));
    }
}