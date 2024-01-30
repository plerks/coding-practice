/*
描述: 一个数组nums，其中某些元素是x，求数组的所有元素到最近的x的距离。
相关: 典型问题/到最近的x的最大距离, LeetCode849. 到最近的人的最大距离, LeetCode2808. 使循环数组所有元素相等的最少秒数, LeetCode514. 自由之路
*/

import java.util.Arrays;

public class AllDistToClosest {
    public int[] allDistToClosest(int[] nums, int x) {
        int n = nums.length;
        int[] dpL = new int[n]; // dpL[i]表示i向左走到x的最短距离
        dpL[0] = nums[0] == x ? 0 : Integer.MAX_VALUE;
        for (int i = 1; i < n; i++) {
            dpL[i] = nums[i] == x ? 0 : dpL[i - 1] == Integer.MAX_VALUE ? Integer.MAX_VALUE : dpL[i - 1] + 1; // i可以先走到i-1再向左找x
        }
        int[] dpR = new int[n]; // dpR[i]表示i向右走到x的最短距离
        dpR[n - 1] = nums[n - 1] == x ? 0 : Integer.MAX_VALUE;
        for (int i = n - 2; i >= 0; i--) {
            dpR[i] = nums[i] == x ? 0 : dpR[i + 1] == Integer.MAX_VALUE ? Integer.MAX_VALUE : dpR[i + 1] + 1;
        }
        int[] dp = new int[n];
        for (int i = 0; i < n; i++) dp[i] = Math.min(dpL[i], dpR[i]);
        return dp;
    }
    public static void main(String[] args) {
        AllDistToClosest adtc = new AllDistToClosest();
        System.out.println(Arrays.toString(adtc.allDistToClosest(new int[]{1,0,0,0,1,0,1}, 1)));
        System.out.println(Arrays.toString(adtc.allDistToClosest(new int[]{1,0,0,0,1,0,0}, 1)));
    }
}
