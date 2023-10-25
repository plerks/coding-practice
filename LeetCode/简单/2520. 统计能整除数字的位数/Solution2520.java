// https://leetcode.cn/problems/count-the-digits-that-divide-a-number/?envType=daily-question&envId=2023-10-26

public class Solution2520 {
    public int countDigits(int num) {
        int ans = 0;
        int a = num;
        while (a > 0) {
            int digit = a % 10;
            if (num % digit == 0) {
                ans++;
            }
            a /= 10;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2520 solu = new Solution2520();
        System.out.println(solu.countDigits(121));
    }
}
