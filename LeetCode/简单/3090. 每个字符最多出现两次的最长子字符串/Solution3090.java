/*
url: https://leetcode.cn/problems/maximum-length-substring-with-two-occurrences/description/
LeetCode参考: https://leetcode.cn/problems/maximum-length-substring-with-two-occurrences/solutions/2704776/on-hua-dong-chuang-kou-pythonjavacgo-by-hl44d/
相关: LeetCode3. 无重复字符的最长子串
标签: LeetCode第390场周赛, 双指针, 滑动窗口
*/

import java.util.*;

// 此题属于我参加的LeetCode第390场周赛
public class Solution3090 {
    // 周赛直接写的暴力解法，能过
    public int maximumLengthSubstring(String s) {
        int n = s.length();
        int[] count = new int[26];
        int ans = 0;
        for (int i = 0; i < n; i++) {
            Arrays.fill(count, 0);
            int len = 0;
            for (int j = i; j < n; j++) {
                char c = s.charAt(j);
                count[c - 'a']++;
                if (count[c - 'a'] > 2) {
                    break;
                }
                else len++;
            }
            ans = Math.max(ans, len);
        }
        return ans;
    }

    /* 优化，用双指针实现。
    当[x,y]有字符出现两次时，[x,y]一定不是任何可行子串的一部分。这样双指针的正确性在于，当right在某一位置时，left一定是在能允许的最左位置。
    */
    public int maximumLengthSubstring_implementation2(String s) {
        int n = s.length();
        int[] count = new int[26];
        int ans = 0;
        int left = 0, right = 0; // right是要新加入的位置
        while (right < n) {
            char c = s.charAt(right);
            count[c - 'a']++;
            while (count[c - 'a'] > 2) {
                count[s.charAt(left) - 'a']--;
                left++; // 这里一定不会致使left>right
            }
            ans = Math.max(ans, right - left + 1);
            right++;
        }
        return ans;
    }

    // 参考灵茶山艾府题解，这样写枚举右边界位置感觉思路要更清晰一点
    public int maximumLengthSubstring_implementation3(String s) {
        int n = s.length();
        int[] count = new int[26];
        int ans = 0;
        int left = 0;
        for (int right = 0; right < n; right++) { // 相当于枚举子串的右边界在right位置，并把left从远处移到刚好能符合要求的位置
            char c = s.charAt(right);
            count[c - 'a']++;
            while (count[c - 'a'] > 2) {
                count[s.charAt(left) - 'a']--;
                left++;
            }
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3090 solu = new Solution3090();
        System.out.println(solu.maximumLengthSubstring("bcbbbcba"));
        System.out.println(solu.maximumLengthSubstring_implementation2("bcbbbcba"));
        System.out.println(solu.maximumLengthSubstring_implementation3("bcbbbcba"));
    }
}
