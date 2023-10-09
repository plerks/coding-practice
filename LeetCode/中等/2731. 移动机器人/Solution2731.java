/*
url: https://leetcode.cn/problems/movement-of-robots/?envType=daily-question&envId=2023-10-10
LeetCode参考: https://leetcode.cn/problems/movement-of-robots/solutions/2470646/yi-dong-ji-qi-ren-by-leetcode-solution-tm4n/
标签: 移动
*/

import java.util.Arrays;

public class Solution2731 {
    public int sumDistance(int[] nums, String s, int d) {
        // 每次相撞，视为两个机器人互换位置，从而可以视为机器人未发生相撞一直在往同一个方向走
        int n = nums.length;
        long[] pos = new long[n];
        for (int i = 0; i < n; i++) {
            int direction = s.charAt(i) == 'R' ? 1 : -1;
            pos[i] = nums[i] + d * direction;
        }
        Arrays.sort(pos);
        long ans = 0;
        int mod = (int)1e9 + 7;
        for (int i = 1; i < n; i++) {
            // nums[i] - nums[i - 1]这条线段会被计算的次数: [0, i -1]有i个点，[i, n - 1]有n - i个点，次数为i * (n - i)
            ans = (ans + (long)((pos[i] - pos[i - 1]) * i % mod * (n - i) % mod) % mod) % mod;
        }
        return (int)ans;
    }

    public static void main(String[] args) {
        Solution2731 solu = new Solution2731();
        System.out.println(solu.sumDistance(new int[]{1,0}, "RL", 2));
    }
}
