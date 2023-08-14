/*
url: https://leetcode.cn/problems/merge-sorted-array/
LeetCode参考: https://leetcode.cn/problems/merge-sorted-array/solutions/666608/he-bing-liang-ge-you-xu-shu-zu-by-leetco-rrb0/
相关: https://leetcode.cn/problems/remove-element/
标签: 双指针
*/

public class Solution88 {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        /* 要不用额外空间，得从后面开始双指针。
        是否会出现把num1的元素覆盖的情况？否，考虑极端情况num1一直未能在尾部留出空位，num2一直往num1尾部填充，
        这种情况最多刚好把num1尾部填满。
        */
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            }
            else if (nums1[i] <= nums2[j]) {
                nums1[k--] = nums2[j--];
            }
        }
        while (i >= 0) {
            nums1[k--] = nums1[i--];
        }
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }

    public static void main(String[] args) {
        Solution88 solu = new Solution88();
        solu.merge(new int[]{1,2,3,0,0,0}, 3, new int[]{2,5,6}, 3);
        // solu.merge(new int[]{2,0}, 1, new int[]{1}, 1);
    }
}