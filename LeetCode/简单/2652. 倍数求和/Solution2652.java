/*
url: https://leetcode.cn/problems/sum-multiples/?envType=daily-question&envId=2023-10-17
LeetCode参考: https://leetcode.cn/problems/sum-multiples/solutions/2241283/o1-rong-chi-yuan-li-by-endlesscheng-yxc4/
标签: 容斥原理
*/

public class Solution2652 {
    public int sumOfMultiples(int n) {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
                ans += i;
            }
        }
        return ans;
    }

    public int sumOfMultiples_implementation2(int n) {
        return getSum(3, n) + getSum(5, n) + getSum(7, n) - getSum(15, n) - getSum(21, n) - getSum(35, n) + getSum(105, n);
    }

    public int getSum(int a, int n) {
        // [1, n]中a的倍数为a, 2a, 3a, ... , ⌊n / a⌋ * a
        int k = n / a;
        return (a + k * a) * k / 2;
    }

    public static void main(String[] args) {
        Solution2652 solu = new Solution2652();
        System.out.println(solu.sumOfMultiples_implementation2(7));
    }
}
