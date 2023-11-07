// https://leetcode.cn/problems/find-the-longest-balanced-substring-of-a-binary-string/?envType=daily-question&envId=2023-11-08

public class Solution2609 {
    public int findTheLongestBalancedSubstring(String s) {
        int continousZeroCount = 0;
        int ans = 0;
        for (int i = 0; i < s.length();) {
            if (s.charAt(i) == '0') {
                continousZeroCount++;
                i++;
            }
            else {
                int continousOneCount = 0;
                while (i < s.length() && s.charAt(i) == '1') {
                    continousOneCount++;
                    i++;
                }
                ans = Math.max(ans, 2 * Math.min(continousZeroCount, continousOneCount));
                continousZeroCount = 0;
            }

        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2609 solu = new Solution2609();
        System.out.println(solu.findTheLongestBalancedSubstring("01000111"));
    }
}
