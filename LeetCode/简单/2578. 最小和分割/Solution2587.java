/*
url: https://leetcode.cn/problems/split-with-minimum-sum/?envType=daily-question&envId=2023-10-09
标签: 贪心, 局部调整法
*/

import java.util.Arrays;

public class Solution2587 {
    public int splitNum(int num) {
        String s = String.valueOf(num);
        int[] numbers = new int[s.length()];
        for (int i = 0; i < s.length(); i++) {
            numbers[i] = s.charAt(i) - '0';
        }
        Arrays.sort(numbers);
        int time1 = 1, time2 = 1;
        int ans = 0;
        // 每位数字最终都会乘一个10^i，要让越大的数字在越靠近个位的位置，否则调整这两个数字的位置之后和一定变小
        for (int i = numbers.length - 1; i >= 0; i--) {
            if (time1 <= time2) {
                ans += numbers[i] * time1;
                time1 *= 10;
            }
            else {
                ans += numbers[i] * time2;
                time2 *= 10;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2587 solu = new Solution2587();
        System.out.println(solu.splitNum(4325));
    }
}