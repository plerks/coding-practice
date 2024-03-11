/*
url: https://leetcode.cn/problems/sort-vowels-in-a-string/description/
LeetCode参考: https://leetcode.cn/problems/sort-vowels-in-a-string/solutions/2354971/wei-yun-suan-jia-su-by-endlesscheng-c7h9/
              https://www.bilibili.com/video/BV1AM4y1x7r4/
相关: LeetCode2129. 将标题首字母大写
标签: 计数, 位运算
*/

import java.util.*;

public class Solution2785 {
    public String sortVowels(String s) {
        int[] count = new int[10]; // 记录每个元音字母出现次数
        HashMap<Character, Integer> map1 = new HashMap<>();
        map1.put('A', 0);
        map1.put('E', 1);
        map1.put('I', 2);
        map1.put('O', 3);
        map1.put('U', 4);
        map1.put('a', 5);
        map1.put('e', 6);
        map1.put('i', 7);
        map1.put('o', 8);
        map1.put('u', 9);
        HashMap<Integer, Character> map2 = new HashMap<>();
        map2.put(0, 'A');
        map2.put(1, 'E');
        map2.put(2, 'I');
        map2.put(3, 'O');
        map2.put(4, 'U');
        map2.put(5, 'a');
        map2.put(6, 'e');
        map2.put(7, 'i');
        map2.put(8, 'o');
        map2.put(9, 'u');
        int n = s.length();
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (map1.containsKey(c)) {
                count[map1.get(c)]++;
            }
        }
        char[] ans = s.toCharArray();
        int index = 0;
        while (index < 10 && count[index] == 0) index++; // index挪到第一个计数不为0的元音字母
        for (int i = 0; i < n; i++) {
            char c = ans[i];
            if (map1.containsKey(c)) { // 是元音字母
                ans[i] = map2.get(index);
                count[index]--;
                while (index < 10 && count[index] == 0) index++;
            }
        }
        return new String(ans);
    }

    // 参考题解使用了一个用位运算来判断一个字母是否是元音字母的技巧
    public String sortVowels_implementation2(String s) {
        int[] count = new int['z' - 'A' + 1];
        Arrays.fill(count, -1);
        String vowels = "AEIOUaeiou";
        for (int i = 0; i < vowels.length(); i++) {
            count[vowels.charAt(i) - 'A'] = 0;
        }
        int mask = 0;
        String vowelsUpperCase = "AEIOU";
        for (int i = 0; i < vowelsUpperCase.length(); i++) {
            mask |= 1 << (vowelsUpperCase.charAt(i) - 'A');
        }
        /* A-Z和a-z的低5位都是1-26的数字，用这个mask来判断一个字符c是否是AEIOUaeiou之一
        */
        int n = s.length();
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            // (c & 31) - 1取低5位再减1，范围为0-25，然后用mask判断是否是元音字母
            if ((mask & (1 << ((c & 31) - 1))) > 0) { // 是元音字母
                count[c - 'A']++;
            }
        }
        char[] ans = s.toCharArray();
        int index = 0;
        while (index < count.length && count[index] <= 0) index++;
        for (int i = 0; i < n; i++) {
            char c = ans[i];
            if ((mask & (1 << ((c & 31) - 1))) > 0) { // 是元音字母
                ans[i] = (char)('A' + index);
                count[index]--;
                while (index < count.length && count[index] <= 0) index++;
            }
        }
        return new String(ans);
    }

    public static void main(String[] args) {
        Solution2785 solu = new Solution2785();
        System.out.println(solu.sortVowels("lEetcOde"));
        System.out.println(solu.sortVowels_implementation2("lEetcOde"));
    }
}
