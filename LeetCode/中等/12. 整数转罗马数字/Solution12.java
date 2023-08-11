/*
url: https://leetcode.cn/problems/integer-to-roman/
LeetCode参考: https://leetcode.cn/problems/integer-to-roman/solutions/774611/zheng-shu-zhuan-luo-ma-shu-zi-by-leetcod-75rs/ 
*/

public class Solution12 {
    public String intToRoman(int num) {
        int[] keys = new int[]{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        String[] values = new String[]{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        StringBuilder ans = new StringBuilder();
        while (num != 0) {
            for (int i = 0; i < keys.length; i++) {
                if (num >= keys[i]) {
                    ans.append(values[i]);
                    num -= keys[i];
                    break;
                }
            }
        }
        return ans.toString();
    }

    public static void main(String[] args) {
        Solution12 solu = new Solution12();
        System.out.println(solu.intToRoman(20));
    }
}