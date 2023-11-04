/*
url: https://leetcode.cn/problems/repeated-dna-sequences/?envType=daily-question&envId=2023-11-05
LeetCode参考: https://leetcode.cn/problems/repeated-dna-sequences/solutions/1035568/zhong-fu-de-dnaxu-lie-by-leetcode-soluti-z8zn/
标签: 滑动窗口, 字符串压缩到整数
*/

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Solution187 {
    // 容易想到的直接解法
    public List<String> findRepeatedDnaSequences(String s) {
        HashMap<String, Integer> map = new HashMap<>();
        List<String> ans = new ArrayList<>();
        for (int i = 0; i + 10 <= s.length(); i++) {
            String sub = s.substring(i, i + 10);
            map.put(sub, map.getOrDefault(sub, 0) + 1);
            if (map.get(sub) == 2) { // 只添加一次
                ans.add(sub);
            }
        }
        return ans;
    }

    // [官方题解](https://leetcode.cn/problems/repeated-dna-sequences/solutions/1035568/zhong-fu-de-dnaxu-lie-by-leetcode-soluti-z8zn/)提供的优化办法，ACGT四种可能用2位即可表示，要找位置的串长度为10，则只需20位，即一个int即可存储
    public List<String> findRepeatedDnaSequences_implementation2(String s) {
        if (s.length() < 10) return new ArrayList<>();
        HashMap<Character, Integer> nucleobase = new HashMap<>();
        nucleobase.put('A', 0);
        nucleobase.put('C', 1);
        nucleobase.put('G', 2);
        nucleobase.put('T', 3);
        int sub = 0;
        HashMap<Integer, Integer> map = new HashMap<>();
        List<String> ans = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            sub = (sub << 2) | nucleobase.get(s.charAt(i)); // 用一个int来表示子串
        }
        map.put(sub, 1);
        // 滑动窗口，出一个字符入一个字符，计算新的sub值只需考虑这两个字符
        // mask为低20位都为1的数字，用于sub左移后去除高位
        int mask = (1 << 20) - 1;
        for (int i = 1; i + 10 <= s.length(); i++) {
            sub = (sub << 2) & mask | nucleobase.get(s.charAt(i + 9));
            map.put(sub, map.getOrDefault(sub, 0) + 1);
            if (map.get(sub) == 2) { // 只添加一次
                ans.add(s.substring(i, i + 10));
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution187 solu = new Solution187();
        System.out.println(solu.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
        System.out.println(solu.findRepeatedDnaSequences_implementation2("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
    }
}
