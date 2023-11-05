/*
url: https://leetcode.cn/problems/maximum-product-of-word-lengths/?envType=daily-question&envId=2023-11-06
标签: 字符串特化压缩
*/

public class Solution318 {
    public int maxProduct(String[] words) {
        int n = words.length;
        int[] charInfo = new int[n]; // 26个字母，用26位代表word是否含有某个字母
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < words[i].length(); j++) {
                char c = words[i].charAt(j);
                charInfo[i] |= 1 << (c - 'a');
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!((charInfo[i] & charInfo[j]) > 0)) {
                    ans = Math.max(ans, words[i].length() * words[j].length());
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution318 solu = new Solution318();
        System.out.println(solu.maxProduct(new String[]{"abcw","baz","foo","bar","xtfn","abcdef"}));
    }
}
