/*
url: https://leetcode.cn/problems/number-of-ways-to-buy-pens-and-pencils/
相关: https://leetcode.cn/problems/combination-sum/
标签: 选数
*/

public class Solution2240 {
    public long waysToBuyPensPencils(int total, int cost1, int cost2) {
        int i = 0;
        long ans = 0;
        while (cost1 * i <= total) {
            ans += (total - cost1 * i) / cost2 + 1;
            i++;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2240 solu = new Solution2240();
        System.out.println(solu.waysToBuyPensPencils(20, 10, 5));
    }
}