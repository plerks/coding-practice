/*
url: https://leetcode.cn/problems/count-alternating-subarrays/description/
我的题解: https://leetcode.cn/problems/count-alternating-subarrays/solutions/2720385/cong-lian-tong-fen-liang-de-shi-jiao-kao-xvjw/
LeetCode参考: https://leetcode.cn/problems/count-alternating-subarrays/solutions/2716871/jian-ji-xie-fa-pythonjavacgo-by-endlessc-tcc9/
标签: LeetCode第391场周赛, 连通分量, 子数组
*/

import java.util.*;

public class Solution3101 {
    // 周赛的写法，通过
    public long countAlternatingSubarrays(int[] nums) {
        // 求连通分量的个数和size
        int n = nums.length;
        long size = 1;
        ArrayList<Long> list = new ArrayList<>();
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[i - 1]) {
                size++;
            }
            else {
                list.add(size);
                size = 1;
            }
        }
        list.add(size);
        long ans = 0;
        for (long val : list) {
            ans += (val + 1) * val / 2;
        }
        return ans;
    }

    // 优化一下
    public long countAlternatingSubarrays_implementation2(int[] nums) {
        int n = nums.length;
        long size = 1;
        long ans = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[i - 1]) {
                size++;
            }
            else {
                ans += (size + 1) * size / 2;
                size = 1;
            }
        }
        ans += (size + 1) * size / 2;
        return ans;
    }

    // 参考题解，枚举子数组的右端点
    public long countAlternatingSubarrays_implementation3(int[] nums) {
        int n = nums.length;
        int count = 0;
        long ans = 0;
        // 枚举子数组的右端点，以i为右端点的交替子数组个数得看向左最远能到哪里，或者看成双指针
        for (int i = 0; i < n; i++) {
            count = i > 0 && nums[i] == nums[i - 1] ? 1 : count + 1;
            ans += count;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3101 solu = new Solution3101();
        System.out.println(solu.countAlternatingSubarrays(new int[]{0,1,1,1}));
        System.out.println(solu.countAlternatingSubarrays_implementation2(new int[]{0,1,1,1}));
        System.out.println(solu.countAlternatingSubarrays_implementation3(new int[]{0,1,1,1}));
    }
}
