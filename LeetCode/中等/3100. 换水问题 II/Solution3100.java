/*
url: https://leetcode.cn/problems/water-bottles-ii/description/
标签: LeetCode第391场周赛
*/

public class Solution3100 {
    public int maxBottlesDrunk(int numBottles, int numExchange) {
        int drunk = 0;
        int empty = 0;
        while (true) {
            if (numBottles > 0) {
                drunk += numBottles;
                empty += numBottles;
                numBottles = 0;
            }
            else if (empty >= numExchange) {
                numBottles++;
                empty -= numExchange;
                numExchange++;
            }
            else break;
        }
        return drunk;
    }

    public static void main(String[] args) {
        
    }
}
