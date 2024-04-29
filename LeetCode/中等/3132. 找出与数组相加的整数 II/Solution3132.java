/*
url: https://leetcode.cn/problems/find-the-integer-added-to-array-ii/description/
LeetCode参考: https://leetcode.cn/problems/find-the-integer-added-to-array-ii/solutions/2759118/onlogn-pai-xu-shuang-zhi-zhen-pythonjava-rdj9/
相关: LeetCode392. 判断子序列
标签: LeetCode第395场周赛, 双指针, 同向双指针, 子序列
*/

import java.util.*;

public class Solution3132 {
    // 周赛时的暴力解法，通过，原本还以为O(n^3)的复杂度过不了，但是又没想出来怎么优化
    public int minimumAddedInteger(int[] nums1, int[] nums2) {
        int n = nums1.length;
        Arrays.sort(nums1);
        Arrays.sort(nums2);
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int p1 = 0, p2 = 0;
                while (p1 == i || p1 == j) {
                    p1++;
                }
                int diff = nums2[p2] - nums1[p1];
                p1++;
                p2++;
                while (p2 < n - 2) {
                    if (p1 == i || p1 == j) {
                        p1++;
                        continue;
                    }
                    if (nums2[p2] - nums1[p1] != diff) {
                        break;
                    }
                    p1++;
                    p2++;
                }
                if (p2 == n - 2) ans = Math.min(ans, diff);
            }
        }
        return ans;
    }

    // 灵茶山艾府题解解法，nums1删除后留下的最小值一定是nums1[0],nums1[1],nums1[2]三者之一，因此只需检查三次验证是否可行即可
    public int minimumAddedInteger_implementation2(int[] nums1, int[] nums2) {
        Arrays.sort(nums1);
        Arrays.sort(nums2);
        // 倒着验证，这样num2[0] - min(nums1)就会先是最小的那种情况
        // 记diff = nums2[0] - nums1[i]，只需要验证nums2 + diff是否是nums1的子序列即可，而这是`LeetCode392. 判断子序列`
        for (int i = 2; i >= 0; i--) {
            int diff = nums2[0] - nums1[i];
            // 同向双指针，在nums1中找子序列nums2
            int j = 0;
            for (int k = i; k < nums1.length; k++) {
                if (nums2[j] == nums1[k] + diff) {
                    j++;
                }
                if (j == nums2.length) return diff;
            }
        }
        return -1; // 题目保证答案存在，实际到不了这里
    }

    public static void main(String[] args) {
        Solution3132 solu = new Solution3132();
        System.out.println(solu.minimumAddedInteger(new int[]{4,20,16,12,8}, new int[]{14,18,10}));
        System.out.println(solu.minimumAddedInteger_implementation2(new int[]{4,20,16,12,8}, new int[]{14,18,10}));
    }
}
