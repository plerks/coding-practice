// https://leetcode.cn/problems/palindrome-number/

public class Solution9 {
    public boolean isPalindrome(int x) {
        String s = String.valueOf(x);
        for (int i = 0; i < s.length() - i - 1; i++) {
            if (s.charAt(i) != s.charAt(s.length() - i - 1)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Solution9 solu = new Solution9();
        System.out.println(solu.isPalindrome(121));
    }
}