// https://leetcode.cn/problems/number-of-longest-increasing-subsequence/

public class Solution673 {
    public int findNumberOfLIS(int[] nums) {
        int[] count = new int[nums.length]; // count[i]为以nums[i]结尾的最长递增子序列个数
        int[] len = new int[nums.length]; // len[i]为以nums[i]结尾的最长递增子序列长度
        count[0] = 1;
        len[0] = 1;
        int ans = 0;
        int maxLen = 1;
        for (int i = 1; i < count.length; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (len[j] + 1 > len[i]) {
                        len[i] = len[j] + 1;
                        count[i] = count[j];
                    }
                    else if (len[j] + 1 == len[i]) {
                        count[i] += count[j];
                    }
                }
                else {
                    len[i] = Math.max(1, len[i]);
                    count[i] = Math.max(1, count[i]);
                }
            }
            maxLen = Math.max(maxLen, len[i]);
        }
        for (int i = 0; i < count.length; i++) {
            if (len[i] == maxLen) {
                ans += count[i];
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution673 solu = new Solution673();
        System.out.println(solu.findNumberOfLIS(new int[]{1,3,5,4,7}));
    }
}