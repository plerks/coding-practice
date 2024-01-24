/*
url: https://leetcode.cn/problems/sum-of-values-at-indices-with-k-set-bits/description/?envType=daily-question&envId=2024-01-25
相关: LeetCode2397. 被列覆盖的最多行数
我的题解: https://leetcode.cn/problems/sum-of-values-at-indices-with-k-set-bits/solutions/2618802/gospers-hackzhao-dao-xia-yi-ge-you-kge-1-cyk9/
标签: Gosper's Hack算法
*/

import java.util.Arrays;
import java.util.List;

public class Solution2859 {
    public int sumIndicesWithKSetBits(List<Integer> nums, int k) {
        if (k == 0) return nums.get(0);
        int ans = 0;
        int select = (1 << k) - 1;
        int n = nums.size();
        while (select < n) {
            ans += nums.get(select);
            int lowbit = select & -select;
            int x = select + lowbit;
            select = ((select ^ x) / lowbit >> 2) | x;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2859 solu = new Solution2859();
        System.out.println(solu.sumIndicesWithKSetBits(Arrays.asList(1), 0));
    }
}
