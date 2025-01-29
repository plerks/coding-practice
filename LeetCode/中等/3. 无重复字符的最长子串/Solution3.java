/*
url: https://leetcode.cn/problems/longest-substring-without-repeating-characters/
相关: LeetCode3090. 每个字符最多出现两次的最长子字符串, LeetCode3425. 最长特殊路径
标签: 滑动窗口, 双指针
*/

class Solution3 {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length();
        int[] count = new int[128];
        int ans = 0;
        int left = 0;
        for (int right = 0; right < n; right++) { // 相当于枚举子串的右边界在right位置，并把left从远处移到刚好能符合要求的位置
            char c = s.charAt(right);
            count[c]++;
            while (count[c] > 1) {
                count[s.charAt(left)]--;
                left++;
            }
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }
    
    public static void main(String[] args) {
    	Solution3 solu = new Solution3();
    	System.out.println(solu.lengthOfLongestSubstring("aacdr"));
    }
}
