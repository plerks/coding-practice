/*
url: https://leetcode.cn/problems/find-and-replace-in-string/
LeetCode参考: https://leetcode.cn/problems/find-and-replace-in-string/solutions/2387388/zi-fu-chuan-zhong-de-cha-zhao-yu-ti-huan-9ns4/
*/

import java.util.*;

public class Solution833 {
    public String findReplaceString(String s, int[] indices, String[] sources, String[] targets) {
        HashMap<Integer, List<Integer>> map = new HashMap<>();
        for (int i = 0 ; i < indices.length; i++) {
            if (map.get(indices[i]) == null) {
                map.put(indices[i], new ArrayList<>());
            }
            map.get(indices[i]).add(i);
        }
        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < s.length();) {
            boolean hasReplace = false;
            if (map.containsKey(i)) {
                List<Integer> list = map.get(i);
                for (int j = 0; j < list.size(); j++) {
                    int index = list.get(j);
                    if (sources[index].equals(s.substring(i, Math.min(i + sources[index].length(), s.length())))) {
                        ans.append(targets[index]);
                        hasReplace = true;
                        i += sources[index].length();
                        break;
                    }
                }
            }
            if (!hasReplace) {
                ans.append(s.charAt(i));
                i++;
            }
        }
        return ans.toString();
    }

    public static void main(String[] args) {
        Solution833 solu = new Solution833();
        System.out.println(solu.findReplaceString("abcd", new int[]{0, 2}, new String[]{"a", "cd"}, new String[]{"eee", "ffff"}));
    }
}