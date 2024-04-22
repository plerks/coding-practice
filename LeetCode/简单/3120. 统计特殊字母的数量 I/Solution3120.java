/*
url: https://leetcode.cn/problems/count-the-number-of-special-characters-i/description/
LeetCode参考: https://leetcode.cn/problems/count-the-number-of-special-characters-i/solutions/2749291/wei-yun-suan-yi-ci-bian-li-o1-kong-jian-c6wy1/
相关: 典型问题/大小写转换, LeetCode2785. 将字符串中的元音字母排序, LeetCode3121. 统计特殊字母的数量 II
标签: LeetCode第394场周赛, 位运算
*/

public class Solution3120 {
    // 我的解法
    public int numberOfSpecialChars(String word) {
        int[] count1 = new int[26];
        int[] count2 = new int[26];
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (c >= 'a' && c <= 'z') {
                count1[c - 'a']++;
            }
            else count2[c - 'A']++;
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            if (count1[i] >= 1 && count2[i] >= 1) {
                ans++;
            }
        }
        return ans;
    }

    // 灵茶山艾府题解做法，用位运算优化，用一个int作为map，技巧类似LeetCode2785. 将字符串中的元音字母排序
    public int numberOfSpecialChars_implementation2(String word) {
        int mask1 = 0, mask2 = 0;
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (c >= 'a' && c <= 'z') {
                mask1 |= 1 << ((c & 31) - 1);
            }
            else mask2 |= 1 << ((c & 31) - 1);
        }
        return Integer.bitCount(mask1 & mask2);
    }

    public static void main(String[] args) {
        Solution3120 solu = new Solution3120();
        System.out.println(solu.numberOfSpecialChars("aaAbcBC"));
        System.out.println(solu.numberOfSpecialChars_implementation2("aaAbcBC"));
    }
}
