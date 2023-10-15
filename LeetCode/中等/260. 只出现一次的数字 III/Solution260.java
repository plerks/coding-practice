/*
url: https://leetcode.cn/problems/single-number-iii/?envType=daily-question&envId=2023-10-16
LeetCode参考: https://leetcode.cn/problems/single-number-iii/solutions/587516/zhi-chu-xian-yi-ci-de-shu-zi-iii-by-leet-4i8e/
相关: LeetCode136. 只出现一次的数字, LeetCode137. 只出现一次的数字 II
标签: 异或的特殊性质, x与-x的补码特征
*/

import java.util.Arrays;

public class Solution260 {
    public int[] singleNumber(int[] nums) {
        int x = 0;
        for (int val : nums) {
            x ^= val; // 设只出现一个的两个数为a1, a2，则x = a1 ^ a2
        }
        int firstOneValue = x & -x; // x + -x == 0，由于可以排除x为0的情况(因为a1 != a2)，则x的从低位往高位的第一个1一定在-x中也为1，其它高位一个为0一个为1 
        // firstOneValue为一个有且仅有一位为1的数。此时，在firstOneValue的1所在的这一位，由于x的这一位为1，则a1和a2这一位上一个为0一个为1，从而可以进行分类
        int ans1 = 0, ans2 = 0;
        for (int val : nums) {
            if ((val & firstOneValue) > 0) {
                ans1 ^= val;
            }
            else ans2 ^= val;
        }
        return new int[]{ans1, ans2};
    }

    public static void main(String[] args) {
        Solution260 solu = new Solution260();
        System.out.println(Arrays.toString(solu.singleNumber(new int[]{2,1,2,3,4,1})));
    }
}
