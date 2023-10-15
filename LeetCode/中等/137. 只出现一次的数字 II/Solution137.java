/*
url: https://leetcode.cn/problems/single-number-ii/?envType=daily-question&envId=2023-10-15
LeetCode参考: https://leetcode.cn/problems/single-number-ii/solutions/746993/zhi-chu-xian-yi-ci-de-shu-zi-ii-by-leetc-23t6/
相关: LeetCode136. 只出现一次的数字, LeetCode260. 只出现一次的数字 III
标签: 对每一位分别求值, 数字逻辑, 数字电路
*/

public class Solution137 {
    /* 没办法像`LeetCode136. 只出现一次的数字`一样用异或的性质，把nums重复轮进行运算也不行，一个出现奇数次其它出现偶数次用LeetCode136的做法即可。
    但是一个出现一次(比方说a1)，其它出现奇数x次，把nums重复d次让a1出现奇数次，则x * d也会是奇数，没作用。
    */
    // LeetCode官方题解中还提供了一个特别巧妙的办法，那个由真值表求逻辑表达式的过程是数字逻辑里面的理论，我忘记了
    public int singleNumber(int[] nums) {
        // 计算每一位，出现3次，则那些数字的某一位加起来一定会是3的倍数
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int temp = 0;
            for (int val : nums) {
                temp = temp + ((val >> i) & 1);
            }
            ans = ans + ((temp % 3) << i);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution137 solu = new Solution137();
        System.out.println(solu.singleNumber(new int[]{2,2,3,2}));
    }
}
