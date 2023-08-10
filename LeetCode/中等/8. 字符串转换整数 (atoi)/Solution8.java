/*
url: https://leetcode.cn/problems/string-to-integer-atoi/
相关: https://leetcode.cn/problems/reverse-integer/solutions/
标签: 乘10时的溢出判断
*/

public class Solution8 {
    public int myAtoi(String s) {
        s = s.trim();
        int negative = 1;
        if (s.startsWith("-")) {
            negative = -1;
            s = s.substring(1);
        }
        else if (s.startsWith("+")) {
            negative = 1;
            s = s.substring(1);
        }
        int sum = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (!(c >= '0' && c <= '9')) break;
            if (sum > Integer.MAX_VALUE / 10 || (sum == Integer.MAX_VALUE / 10 && c > '7')) {
                return Integer.MAX_VALUE;
            }
            if (sum < Integer.MIN_VALUE / 10 || (sum == Integer.MIN_VALUE / 10 && c > '8')) {
                return Integer.MIN_VALUE;
            }
            sum = sum * 10 + (s.charAt(i) - '0') * negative;
        }
        return sum;
    }

    public static void main(String[] args) {
        Solution8 solu = new Solution8();
        System.out.println(solu.myAtoi("2147483648"));
    }
}