// https://leetcode.cn/problems/count-the-number-of-vowel-strings-in-range/?envType=daily-question&envId=2023-11-07

public class Solution2586 {
    public int vowelStrings(String[] words, int left, int right) {
        int mask = 0;
        // 26个英文字母，一个int就够长，用个掩码来判断是否是元音字母
        mask |= 1 << ('a' - 'a');
        mask |= 1 << ('e' - 'a');
        mask |= 1 << ('i' - 'a');
        mask |= 1 << ('o' - 'a');
        mask |= 1 << ('u' - 'a');
        int ans = 0;
        for (int i = left; i <= right; i++) {
            String word = words[i];
            int start = 1 << (word.charAt(0) - 'a');
            int end = 1 << (word.charAt(word.length() - 1) - 'a');
            if ((start & mask) > 0 && (end & mask) > 0) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2586 solu = new Solution2586();
        System.out.println(solu.vowelStrings(new String[]{"hey","aeo","mu","ooo","artro"}, 1, 4));
    }
}
