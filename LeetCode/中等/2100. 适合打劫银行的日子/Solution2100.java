/*
url: https://leetcode.cn/problems/find-good-days-to-rob-the-bank/
相关: https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
      https://leetcode.cn/problems/longest-increasing-subsequence/
      https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
*/

import java.util.ArrayList;
import java.util.List;

public class Solution2100 {
    public List<Integer> goodDaysToRobBank(int[] security, int time) {
        int[] dpIncrease = new int[security.length]; // dpIncrease[i]代表[0...i]连续递减子序列长度
        int[] dpDecrease = new int[security.length]; // dpDecrease[i]代表[i, length - 1]连续递增子序列长度
        dpIncrease[0] = 1;
        dpDecrease[dpDecrease.length - 1] = 1;
        for (int i = 1; i < dpIncrease.length; i++) {
            if (security[i] <= security[i - 1]) {
                dpIncrease[i] = dpIncrease[i - 1] + 1;
            }
            else {
                dpIncrease[i] = 1;
            }
        }
        for (int i = dpDecrease.length - 2; i >= 0; i--) {
            if (security[i] <= security[i + 1]) {
                dpDecrease[i] = dpDecrease[i + 1] + 1;
            }
            else {
                dpDecrease[i] = 1;
            }
        }
        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < security.length; i++) {
            if (dpIncrease[i] >= time + 1 && dpDecrease[i] >= time + 1) {
                ans.add(i);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2100 solu = new Solution2100();
        System.out.println(solu.goodDaysToRobBank(new int[]{5,3,3,3,5,6,2}, 2));
    }
}