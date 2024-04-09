/*
url: https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-ii/description/
相关: LeetCode3095. 或值至少 K 的最短子数组 I, LeetCode26. 删除有序数组中的重复项
LeetCode参考: https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-ii/solutions/2716483/zi-shu-zu-orandgcd-tong-yong-mo-ban-pyth-n8xj/
              https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-ii/solutions/2717120/bao-zheng-ni-kan-dong-wei-yun-suan-ha-xi-s547/
标签: 子数组, 位运算, 二分查找, 滑动窗口
*/

import java.util.*;

public class Solution3097 {
    // 暴力法，超时。此题与`LeetCode3095. 或值至少 K 的最短子数组 I`完全相同，不过那题标记为简单题，因此暴力也能过用例
    public int minimumSubarrayLength_exceed_time_limit(int[] nums, int k) {
        int n = nums.length;
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int orSum = 0;
            for (int j = i; j >= 0; j--) {
                orSum |= nums[j];
                if (orSum >= k) {
                    ans = Math.min(ans, i - j + 1);
                }
            }
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }

    // 参考灵茶山艾府题解
    public int minimumSubarrayLength(int[] nums, int k) {
        int n = nums.length;
        int ans = Integer.MAX_VALUE;
        /* 枚举右边界位置，对于每个右边界i，其向左扩展有多种可能，但这多种可能需要优化。不需要记录重复的元素。
        观察上面的暴力法，主要在于要用j第二重循环访问[0,i]的部分，而由于在从nums[0]到nums[i]不断添加数的过程中，由于或的性质，
        或的总值会单增。对于某一个右边界i，若nums[j...i-1]和nums[j-1...i-1]的或的结果相等，由于要求最短子数组，因此只需要记录nums[j...i-1]
        即可，这里用到`LeetCode26. 删除有序数组中的重复项`的去重技巧。
        */
        // 这里list中不会有重复数，而随元素添加，或的值单增，因此最多32个比特位全变为1，于是list中最多只会记录常数个数，第二重循环是O(1)
        List<int[]> list = new ArrayList<>(); // 记录遍历到i位置时，以i-1为子数组右边界所能产生的数。arr[0]记录值，arr[1]记录左边界位置
        for (int i = 0; i < n; i++) {
            list.add(new int[]{nums[i], i});
            int j = 0;
            for (int[] arr : list) {
                arr[0] |= nums[i];
                if (arr[0] >= k) ans = Math.min(ans, i - arr[1] + 1);
                if (arr[0] == list.get(j)[0]) { // 能产生的值相等，只需记录更短的那个
                    list.get(j)[1] = arr[1];
                }
                else {
                    list.set(++j, arr);
                }
            }
            list.subList(j + 1, list.size()).clear();
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }

    /* 这篇题解<https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-ii/solutions/2717120/bao-zheng-ni-kan-dong-wei-yun-suan-ha-xi-s547/>
    还提到了用二分的解法，没去写，不过思路大概是这样：对子数组的长度二分，二分check()最多32次，对于每次check()，相当于固定了子数组长度，因此可以用滑动窗口来进行检查
    子数组或是否大于k，通过记录元素在每个比特位上1出现的次数，窗口移动时就可以立即算出移动后的窗口或值。
    */

    public static void main(String[] args) {
        Solution3097 solu = new Solution3097();
        System.out.println(solu.minimumSubarrayLength(new int[]{2,1,8}, 10));
    }
}
