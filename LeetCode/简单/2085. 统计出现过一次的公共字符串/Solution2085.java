// https://leetcode.cn/problems/count-common-words-with-one-occurrence/description/?envType=daily-question&envId=2024-01-12

import java.util.HashMap;
import java.util.Map;

public class Solution2085 {
    public int countWords(String[] words1, String[] words2) {
        Map<String, Integer> map1 = new HashMap<>();
        for (String s : words1) {
            map1.put(s, map1.getOrDefault(s, 0) + 1);
        }
        Map<String, Integer> map2 = new HashMap<>();
        for (String s : words2) {
            map2.put(s, map2.getOrDefault(s, 0) + 1);
        }
        int ans = 0;
        for (String s : map2.keySet()) {
            if (map2.get(s) == 1 && map1.getOrDefault(s, 0) == 1) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2085 solu = new Solution2085();
        System.out.println(solu.countWords(new String[]{"leetcode","is","amazing","as","is"}, new String[]{"amazing","leetcode","is"}));
    }
}
