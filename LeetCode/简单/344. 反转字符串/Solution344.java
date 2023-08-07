public class Solution344 {
    public void reverseString(char[] s) {
        int n = s.length;
        for (int i = 0; i < n - i - 1; i++) {
            char temp = s[i];
            s[i] = s[n - i - 1];
            s[n - i - 1] = temp;
        }
    }

    public static void main(String[] args) {
        Solution344 solu = new Solution344();
        char[] s = new char[]{'a', 'b', 'c'};
        solu.reverseString(s);
        System.out.println(s);
    }
}