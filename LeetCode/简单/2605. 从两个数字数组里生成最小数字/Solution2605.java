// https://leetcode.cn/problems/form-smallest-number-from-two-digit-arrays/?envType=daily-question&envId=2023-09-05

import java.util.HashSet;
import java.util.Set;

public class Solution2605 {
    public int minNumber(int[] nums1, int[] nums2) {
        int min1 = 10;
        int min2 = 10;
        for (int val : nums1) min1 = Math.min(min1, val);
        for (int val : nums2) min2 = Math.min(min2, val);
        if (min1 > min2) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }
        int ans1 = min1 * 10 + min2;
        Set<Integer> set = new HashSet<>();
        for (int val : nums1) set.add(val);
        int ans2 = 100;
        for (int val : nums2) {
            if (set.contains(val)) {
                ans2 = Math.min(ans2, val);
            }
        }
        return Math.min(ans1, ans2);
    }

    public static void main(String[] args) {
        Solution2605 solu = new Solution2605();
        System.out.println(solu.minNumber(new int[]{4,1,3}, new int[]{5,7}));
    }
}