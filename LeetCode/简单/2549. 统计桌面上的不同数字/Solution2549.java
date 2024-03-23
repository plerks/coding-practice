// https://leetcode.cn/problems/count-distinct-numbers-on-board/description/?envType=daily-question&envId=2024-03-23

public class Solution2549 {
    public int distinctIntegers(int n) {
        /* 1 <= n <= 100且要重复10^9天，第一次，n - 1一定会被加入，因为n % (n - 1) == 1，
        第二次，n - 2一定会被n - 1加入，然后由数据范围2,...,n都会被加入。
        */
        return n == 1 ? 1 : n - 1; // n==1要单独判断下
    }

    public static void main(String[] args) {
        Solution2549 solu = new Solution2549();
        System.out.println(solu.distinctIntegers(5));
    }
}
