// https://leetcode.cn/problems/maximum-profit-of-operating-a-centennial-wheel/?envType=daily-question&envId=2024-01-01

public class Solution1599 {
    public int minOperationsMaxProfit(int[] customers, int boardingCost, int runningCost) {
        int maxProfit = 0, ans = -1;
        int profit = 0, rotateCount = 0;
        int waitingCount = 0;
        for (int i = 0; i < customers.length; i++) {
            waitingCount += customers[i];
            if (waitingCount >= 4) {
                profit += 4 * boardingCost - runningCost;
                waitingCount -= 4;
            }
            else {
                profit += waitingCount * boardingCost - runningCost;
                waitingCount = 0;
            }
            rotateCount++;
            if (profit > maxProfit) {
                maxProfit = profit;
                ans = rotateCount;
            }
        }
        // 最后还剩下等待的人，注意，题目中的意思停止运营后把在上面的人送下来是不算开销的
        if (waitingCount > 0) {
            if (4 * boardingCost - runningCost > 0) {
                profit += (4 * boardingCost - runningCost) * (waitingCount / 4);
                if (profit > maxProfit) {
                    maxProfit = profit;
                    ans = rotateCount + waitingCount / 4;
                }
            }
            if ((waitingCount % 4) * boardingCost - runningCost > 0) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1599 solu = new Solution1599();
        System.out.println(solu.minOperationsMaxProfit(new int[]{5,0,0,0,0,30}, 5, 5));
    }
}
