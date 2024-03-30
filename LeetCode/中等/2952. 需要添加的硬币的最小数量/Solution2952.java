/*
url: https://leetcode.cn/problems/minimum-number-of-coins-to-be-added/description/?envType=daily-question&envId=2024-03-30
LeetCode参考: https://leetcode.cn/problems/minimum-number-of-coins-to-be-added/solutions/2551707/yong-gui-na-fa-si-kao-pythonjavacgo-by-e-8etj/
              https://leetcode.cn/problems/minimum-number-of-coins-to-be-added/solutions/2578933/xu-yao-tian-jia-de-ying-bi-de-zui-xiao-s-khhi/
*/

import java.util.*;

public class Solution2952 {
    /* 我的想法，dp，对于dp[i]，能否凑出i，考虑看dp[x]和dp[i-x](x<=i)能否凑出，但是这题能补充硬币，
    且dp[x]和dp[i-x]可能需要用到相同的硬币，不是独立的。因此考虑枚举dp[i]所用的最大硬币的个数（需要排序coins），然后
    这样dp[i - j * n]就是独立的子问题，但是这样得三重循环，肯定会超时。
    */
    /* 参考题解，用归纳的方式来想，可以避免上面需要考虑使用硬币重合的情况。排序coins，然后遍历coins[i]，假设目前[1,s]
    是能获取的范围，对coints[i]，若其大于s+1，则意味着必须添加硬币s+1，然后能获取的范围变为[1,s]+(s+1)+[s+2,s+s+1]=[1,2s+1]，
    若等于s+1，则能获取的范围变成[1,2s+1]，若小于s，则能获取的范围变为[1,s+nums[i]]，后两种情况可以合并
    */
    public int minimumAddedCoins(int[] coins, int target) {
        Arrays.sort(coins);
        int s = 0;
        int i = 0;
        int count = 0;
        while (s < target) {
            if (i >= coins.length || coins[i] > s + 1) { // 需要加硬币
                count++;
                s = 2 * s + 1;
            }
            else {
                s = s + coins[i];
                i++;
            }
        }
        return count;
    }

    public static void main(String[] args) {
        Solution2952 solu = new Solution2952();
        System.out.println(solu.minimumAddedCoins(new int[]{1,4,10}, 19));
    }
}
