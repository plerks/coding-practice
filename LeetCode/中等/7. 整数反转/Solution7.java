/*
url: https://leetcode.cn/problems/reverse-integer/solutions/
LeetCode题解: https://leetcode.cn/problems/reverse-integer/solutions/755611/zheng-shu-fan-zhuan-by-leetcode-solution-bccn/
相关: https://leetcode.cn/problems/string-to-integer-atoi/
*/

public class Solution7 {
    public int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int digit = x % 10;
            x = x / 10;
            /* if ((rev - Integer.MAX_VALUE / 10) * 10 > 7 - digit || (rev - Integer.MIN_VALUE / 10) * 10 < -digit - 8) {
                // 这样写，x=123，(rev - Integer.MIN_VALUE / 10) * 10会溢出，还是得按LeetCode上那样写，完全避开*10
                System.out.println((rev - Integer.MIN_VALUE / 10) * 10);
                return 0;
            } */

            // 这个判断方式的推导见LeetCode的官方题解
            if (rev - Integer.MAX_VALUE / 10 > 0 || rev - Integer.MIN_VALUE / 10 < 0) {
                return 0;
            }
            rev = rev * 10 + digit;
        }
        return rev;
    }

    public static void main(String[] args) {
        Solution7 solu = new Solution7();
        System.out.println(Integer.MIN_VALUE);
        System.out.println(Integer.MIN_VALUE / 10); // INT_MIN / 10是⌈INT_MIN⌉
        System.out.println(-16 % 10);
        System.out.println(solu.reverse(123));
    }
}