/*
url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/?envType=daily-question&envId=2023-10-01
相关: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
      https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/
*/

public class Solution121 {
    public int maxProfit(int[] prices) {
        int min = Integer.MAX_VALUE;
        int maxProfit = 0;
        for (int val : prices) {
            min = Math.min(val, min);
            maxProfit = Math.max(val - min, maxProfit);
        }
        return maxProfit;
    }

    public static void main(String[] args) {
        Solution121 solu = new Solution121();
        System.out.println(solu.maxProfit(new int[]{7,1,5,3,6,4}));
    }
}