// https://leetcode.cn/problems/subtract-the-product-and-sum-of-digits-of-an-integer/

public class Solution1281 {
    public int subtractProductAndSum(int n) {
        String s = Integer.toString(n);
        int product = 1;
        int sum = 0;
        for (int i = 0; i < s.length(); i++) {
            int digit = s.charAt(i) - '0';
            product *= digit;
            sum += digit;
        }
        return product - sum;
    }

    public static void main(String[] args) {
        Solution1281 solu = new Solution1281();
        System.out.println(solu.subtractProductAndSum(1234));
    }
}