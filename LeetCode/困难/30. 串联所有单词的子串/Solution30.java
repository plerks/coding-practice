// https://leetcode.cn/problems/substring-with-concatenation-of-all-words/

import java.util.*;

public class Solution30{
    public static void main(String[] args){
        Solution30 solu = new Solution30();
        System.out.println(solu.findSubstring("foobarfoo",new String[]{"foo","bar"}));
    }

    public List<Integer> findSubstring(String s, String[] words) {
        List<Integer> res = new ArrayList<>();
        if (words.length == 0) {
            return res;
        }
        HashMap<String, Integer> map = new HashMap<>();
        for (String string : words) {
            map.put(string, map.getOrDefault(string, 0) + 1);
        }
        int len = words[0].length();
        for (int i = 0; i < len; i++) {
            int left = i, right = left;
            HashMap<String, Integer> tmp = new HashMap<>();
            int count = 0; // 已经匹配的word个数
            while (right + len <= s.length()) {
                String word = s.substring(right, right + len);
                right += len;
                if (!map.containsKey(word)) {
                    left = right;
                    count = 0;
                    tmp.clear();
                }
                else {
                    tmp.put(word, tmp.getOrDefault(word, 0) + 1);
                    count++;
                    while (tmp.get(word) > map.get(word)) { // word出现次数过多，需要滑动
                        String firstWindowWord = s.substring(left, left + len);
                        tmp.put(firstWindowWord, tmp.get(firstWindowWord) - 1);
                        count--;
                        left += len;
                    }
                }
                if (count == words.length) {
                    res.add(left);
                }
            }
        }
        return res;
    }
}


