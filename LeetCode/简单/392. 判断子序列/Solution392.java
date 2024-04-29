/*
url: https://leetcode.cn/problems/is-subsequence/description/
相关: LeetCode3132. 找出与数组相加的整数 II
标签: 双指针, 同向双指针, 子序列, 判断子序列
*/

// `LeetCode3132. 找出与数组相加的整数 II`用到此题
public class Solution392 {
    public boolean isSubsequence(String s, String t) {
        int i = 0, j = 0; // 用双指针来匹配
        while (i < s.length() && j < t.length()) {
            if (s.charAt(i) == t.charAt(j)) {
                i++;
                j++;
            }
            else {
                // 碰到相等就可以直接到下一个匹配位置，不存在选第一个不能匹配完而选后面的匹配位置能匹配上的可能
                j++;
            }
        }
        return i == s.length();
    }

    public static void main(String[] args) {
        Solution392 solu = new Solution392();
        System.out.println(solu.isSubsequence("abc", "ahbgdc"));
    }
}
