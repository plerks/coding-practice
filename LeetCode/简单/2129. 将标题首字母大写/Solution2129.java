/*
url: https://leetcode.cn/problems/capitalize-the-title/description/?envType=daily-question&envId=2024-03-11
相关: LeetCode2785. 将字符串中的元音字母排序
标签: 位运算, 大小写转换
*/

public class Solution2129 {
    public String capitalizeTitle(String title) {
        int n = title.length();
        StringBuilder ans = new StringBuilder();
        StringBuilder word = new StringBuilder();
        int mask = 1 << 5;
        // 转大小写的技巧关键点类似LeetCode2785. 将字符串中的元音字母排序，A-Z和a-z的低5位都是1-26的数字，对应的大小写字母在第6位上相反
        for (int i = 0; i < n; i++) {
            char c = title.charAt(i);
            if (c == ' ') {
                if (word.length() > 2) {
                    word.setCharAt(0, (char)(word.charAt(0) & ~mask)); // 首字母大写
                }
                ans.append(word);
                word.delete(0, word.length());
                ans.append(c);
            }
            else {
                word.append((char)(c | mask)); // 统一转小写
            }
        }
        if (word.length() > 2) {
            word.setCharAt(0, (char)(word.charAt(0) & ~mask)); // 首字母大写
        }
        ans.append(word);
        return ans.toString();
    }

    public static void main(String[] args) {
        Solution2129 solu = new Solution2129();
        System.out.println(solu.capitalizeTitle("capiTalIze tHe titLe"));
    }
}
