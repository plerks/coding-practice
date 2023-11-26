/*
url: https://leetcode.cn/problems/count-unique-characters-of-all-substrings-of-a-given-string/?envType=daily-question&envId=2023-11-26
标签: 幂集
*/

import java.util.HashMap;

public class Solution828 {
    public int uniqueLetterString(String s) {
        int n = s.length();
        // appearR[i]为s.charAt(i)在右侧的最近出现位置，未出现则为n - 1
        int[] appearR = new int[n];
        HashMap<Character, Integer> map = new HashMap<>();
        for (int i = n - 1; i >= 0; i--) {
            appearR[i] = map.getOrDefault(s.charAt(i), n);
            map.put(s.charAt(i), i);
        }
        // appearL[i]为s.charAt(i)在左侧的最近出现位置，未出现则为-1
        int[] appearL = new int[n];
        map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            appearL[i] = map.getOrDefault(s.charAt(i), -1);
            map.put(s.charAt(i), i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            // [appearL, i)和(i, appearR]两部分各有长度种情况，相乘
            ans += (i - appearL[i]) * (appearR[i] - i);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution828 solu = new Solution828();
        System.out.println(solu.uniqueLetterString("ABA"));
    }
}
