/*
url: https://leetcode.cn/problems/trapping-rain-water/
题目简述: 给定n个非负整数表示每个宽度为1的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
LeetCode参考: https://leetcode.cn/problems/trapping-rain-water/solutions/2355502/li-kou-jia-jia-shuang-shu-zu-or-shuang-z-noah/
              https://leetcode.cn/problems/trapping-rain-water/solutions/2355400/ni-hui-jie-yu-shui-de-san-chong-fang-fa-sbbfc/
相关: LeetCode1793. 好子数组的最大分数, LeetCode84. 柱状图中最大的矩形, LeetCode2334. 元素值大于变化阈值的子数组, LeetCode907. 子数组的最小值之和
标签: 双指针
*/

public class Solution42 {
    public int trap(int[] height) {
        // height[i]能存多少水取决于i左右两侧的最高柱子的较小值，即min(max_i_left, max_i_right)。用双指针从两边往中间靠。
        int l = 0, r = height.length - 1;
        int res = 0;
        int lMax = 0, rMax = 0;
        while (l < r) {
            if (height[l] < height[r]) {
                if (height[l] > lMax) { // l这个柱子上无法存水
                    lMax = height[l];
                }
                else {
                    /*
                    这里隐含了lMax为短板，会不会出现左侧很高(比如height[0]很大，从而lMax很大)，但是右侧为短板，导致存水面积多算的情况？
                    否，能走到这个height[l] < height[r]的分支，说明前面已经存在某个height[r] > height[0]了。
                    */
                    res += lMax - height[l];
                }
                l++;
            }
            else {
                if (height[r] > rMax) {
                    rMax = height[r];
                }
                else {
                    res += rMax - height[r];
                }
                r--;
            }
        }
        return res;
    }

    public int trap_implementation2(int[] height) {
        int[] maxLeft = new int[height.length]; // maxLeft[i]表示height[0...i]的最大值
        int[] maxRight = new int[height.length];
        maxLeft[0] = height[0];
        maxRight[maxRight.length - 1] = height[height.length - 1];
        for (int i = 1; i < maxLeft.length; i++) {
            maxLeft[i] = Math.max(height[i], maxLeft[i - 1]);
        }
        for (int i = maxRight.length - 2; i >= 0; i--) {
            maxRight[i] = Math.max(height[i], maxRight[i + 1]);
        }
        int res = 0;
        for (int i = 0; i < height.length; i++) {
            res += Math.min(maxLeft[i], maxRight[i]) - height[i];
        }
        return res;
    }

    public static void main(String[] args) {
        Solution42 solu = new Solution42();
        System.out.println(solu.trap_implementation2(new int[]{10,2,5}));
    }
}