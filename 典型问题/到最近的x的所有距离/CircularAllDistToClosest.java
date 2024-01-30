/*
描述: 和AllDistToClosest.java类似，一个数组nums，其中某些元素是x，求数组的所有元素到最近的x的距离，区别在于数组是首尾相接的循环数组。
相关: 典型问题/到最近的x的最大距离, LeetCode849. 到最近的人的最大距离, LeetCode2808. 使循环数组所有元素相等的最少秒数, LeetCode514. 自由之路
*/

import java.util.Arrays;

public class CircularAllDistToClosest {
    private int[] circularAllDistToClosest(int[] nums, int x) {
        int n = nums.length;
        int[] dpL = new int[n]; // dpL[i]表示i向左走到x的最短距离
        if (nums[0] == x) {
            dpL[0] = 0;
        }
        else {
            for (int i = n - 1; i > 0; i--) {
                if (nums[i] == x) {
                    dpL[0] = n - 1 - i + 1;
                    break;
                }
            }
        }
        // dpL[0]已填充
        for (int i = 1; i < n; i++) {
            dpL[i] = nums[i] == x ? 0 : dpL[i - 1] + 1; // 若i位置上已经是x，则距离为0，否则要先走到i - 1位置再走向x
        }
        int[] dpR = new int[n];
        if (nums[n - 1] == x) {
            dpR[n - 1] = 0;
        }
        else {
            for (int i = 0; i < n - 1; i++) {
                if (nums[i] == x) {
                    dpR[n - 1] = i + 1;
                    break;
                }
            }
        }
        // dpR[n - 1]已填充
        for (int i = n - 2; i >= 0; i--) {
            dpR[i] = nums[i] == x ? 0 : dpR[i + 1] + 1;
        }
        int[] dp = new int[n];
        for (int i = 0; i < n; i++) {
            dp[i] = Math.min(dpL[i], dpR[i]);
        }
        return dp;
    }
    public static void main(String[] args) {
        CircularAllDistToClosest cadtc = new CircularAllDistToClosest();
        System.out.println(Arrays.toString(cadtc.circularAllDistToClosest(new int[]{1,0,0,0,1,0,1}, 1)));
        System.out.println(Arrays.toString(cadtc.circularAllDistToClosest(new int[]{1,0,0,0,1,0,0}, 1)));
    }
}
