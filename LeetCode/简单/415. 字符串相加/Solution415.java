// https://leetcode.cn/problems/add-strings/

class Solution415 {
    public String addStrings(String num1, String num2) {
        int length1 = num1.length();
        int length2 = num2.length();
        int sumOverTen = 0;
        StringBuilder s = new StringBuilder();
        int i = 0;
        for (; length1 -1 - i >= 0 || length2 - 1 - i >=0 || sumOverTen > 0; i++) {
            int p1 = length1 -1 - i >= 0? num1.charAt(length1 -1 - i) - '0' : 0;
            int p2 = length2 -1 - i >= 0? num2.charAt(length2 -1 - i) - '0' : 0;
            int p = p1 + p2 + sumOverTen;
            if (p >= 10) {
                sumOverTen = 1;
            }
            else {
                sumOverTen = 0;
            }
            p %= 10;
            s.append(p);
        }
        return s.reverse().toString();
    }

    public static void main(String[] args) {
        Solution415 solu = new Solution415();
        System.out.println(solu.addStrings("9", "99"));
    }
}