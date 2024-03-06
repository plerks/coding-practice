/*
url: https://leetcode.cn/problems/find-the-divisibility-array-of-a-string/description/?envType=daily-question&envId=2024-03-07
标签: 数论, 动态规划
*/

import java.util.*;

public class Solution2575 {
    public int[] divisibilityArray(String word, int m) {
        /* 若x % m == d，即x = km + d，则10x = 10km + 10d，则(10x + y) % m = (10d + y) % m，这样就可以dp算
        */
        int n = word.length();
        int[] ans = new int[n];
        long d = 0; // 不用单独计算一次ans[0]作为初始情况，直接d = 0就可以作为初始情况
        for (int i = 0; i < word.length(); i++) {
            int y = word.charAt(i) - '0';
            long newD = (10 * d + y) % m;
            ans[i] = newD == 0 ? 1 : 0;
            d = newD;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2575 solu = new Solution2575();
        System.out.println(Arrays.toString(solu.divisibilityArray("998244353", 3)));
    }
}
