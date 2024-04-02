/*
url: https://leetcode.cn/problems/harshad-number/
标签: LeetCode第391场周赛
*/

public class Solution3099 {
    public int sumOfTheDigitsOfHarshadNumber(int x) {
        int sum = 0;
        int temp = x;
        while (temp > 0) {
            int d = temp % 10;
            sum += d;
            temp /= 10;
        }
        return x % sum == 0 ? sum : -1;
    }

    public static void main(String[] args) {
        
    }
}