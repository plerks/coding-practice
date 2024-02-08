/*
url: https://leetcode.cn/problems/sort-vowels-in-a-string/description/
标签: 计数
*/

import java.util.*;

public class Solution2785 {
    public String sortVowels(String s) {
        int[] count = new int[10]; // 记录每个元音出现次数
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
        while (index < 10 && count[index] == 0) index++; // index挪到第一个计数不为0的元音
        for (int i = 0; i < n; i++) {
            char c = ans[i];
            if (map1.containsKey(c)) { // 是元音
                ans[i] = map2.get(index);
                count[index]--;
                while (index < 10 && count[index] == 0) index++;
            }
        }
        return new String(ans);
    }

    public static void main(String[] args) {
        Solution2785 solu = new Solution2785();
        System.out.println(solu.sortVowels("lEetcOde"));
    }
}
