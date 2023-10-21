/*
url: https://leetcode.cn/problems/reducing-dishes/?envType=daily-question&envId=2023-10-22
相关: LeetCode2136. 全部开花的最早一天
我的题解: https://leetcode.cn/problems/reducing-dishes/solutions/2492833/shi-jian-100ju-bu-diao-zheng-fen-xi-pai-jfj8r/
标签: 局部调整法, 数学推导
*/

import java.util.Arrays;

public class Solution1402 {
    public int maxSatisfaction(int[] satisfaction) {
        Arrays.sort(satisfaction);
        int total = 0;
        for (int val : satisfaction) {
            total += val;
        }
        int first = 0;
        while (total <= 0 && first < satisfaction.length) {
            total -= satisfaction[first];
            first++;
        }
        int ans = 0;
        for (int i = 0; i + first < satisfaction.length; i++) {
            ans += (i + 1) * satisfaction[i + first];
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1402 solu = new Solution1402();
        System.out.println(solu.maxSatisfaction(new int[]{-1,-8,0,5,-9}));
    }
}
