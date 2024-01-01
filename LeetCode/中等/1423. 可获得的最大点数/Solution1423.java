/*
url: https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/
LeetCode参考: https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/solutions/2551432/liang-chong-fang-fa-ni-xiang-si-wei-zhen-e3gb/
标签: 滑动窗口, 卡牌问题
*/

public class Solution1423 {
    // 求中间n - k张卡的最小值
    public int maxScore(int[] cardPoints, int k) {
        int sum = 0, min = Integer.MAX_VALUE, total = 0;
        int len = cardPoints.length - k;
        for (int i = 0; i < len; i++) {
            sum += cardPoints[i];
        }
        min = sum; // min为连续len长的子数组的最小值
        total = sum;
        for (int i = len; i < cardPoints.length; i++) {
            total += cardPoints[i];
            sum = sum + cardPoints[i] - cardPoints[i - len]; // 新的窗口是[i - len + 1, i]
            min = Math.min(min, sum);
        }
        return total - min;
    }

    // 拿的牌是两端的，共k张，左侧i张(0 <= i <= k)，右侧k - i张，遍历i的情况
    public int maxScore_implementation2(int[] cardPoints, int k) {
        int sum = 0;
        for (int i = 0; i < k; i++) {
            sum += cardPoints[i];
        }
        int ans = sum;
        int n = cardPoints.length;
        for (int i = k - 1; i >= 0; i--) {
            sum = sum - cardPoints[i] + cardPoints[n - 1 - ((k - 1) - i)];
            ans = Math.max(ans, sum);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1423 solu = new Solution1423();
        System.out.println(solu.maxScore(new int[]{9,7,7,9,7,7,9}, 7));
        System.out.println(solu.maxScore_implementation2(new int[]{9,7,7,9,7,7,9}, 7));
    }
}
