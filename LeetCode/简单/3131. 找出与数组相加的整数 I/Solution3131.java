/*
url: https://leetcode.cn/problems/find-the-integer-added-to-array-i/description/
标签: LeetCode第395场周赛
*/

public class Solution3131 {
    public int addedInteger(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int min1 = Integer.MAX_VALUE;
        int min2 = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            min1 = Math.min(min1, nums1[i]);
            min2 = Math.min(min2, nums2[i]);
        }
        return min2 - min1;
    }

    public static void main(String[] args) {
    }
}
