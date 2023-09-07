// https://leetcode.cn/problems/calculate-delayed-arrival-time/?envType=daily-question&envId=2023-09-08

public class Solution2651 {
    public int findDelayedArrivalTime(int arrivalTime, int delayedTime) {
        return (arrivalTime + delayedTime) % 24;
    }

    public static void main(String[] args) {
        Solution2651 solu = new Solution2651();
        System.out.println(solu.findDelayedArrivalTime(15, 5));
    }
}