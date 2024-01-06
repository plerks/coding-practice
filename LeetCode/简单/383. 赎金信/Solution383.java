// https://leetcode.cn/problems/ransom-note/description/?envType=daily-question&envId=2024-01-07

public class Solution383 {
    public boolean canConstruct(String ransomNote, String magazine) {
        char[] map = new char[26];
        for (int i = 0; i < magazine.length(); i++) {
            map[magazine.charAt(i) - 'a']++;
        }
        for (int i = 0; i < ransomNote.length(); i++) {
            char c = ransomNote.charAt(i);
            if (map[c - 'a'] > 0) {
                map[c - 'a']--;
            }
            else return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Solution383 solu = new Solution383();
        System.out.println(solu.canConstruct("aa", "aab"));
    }
}
