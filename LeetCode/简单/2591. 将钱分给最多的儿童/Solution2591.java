/*
url: https://leetcode.cn/problems/distribute-money-to-maximum-children/?envType=daily-question&envId=2023-09-22
LeetCode参考: https://leetcode.cn/problems/distribute-money-to-maximum-children/solutions/2177180/fen-lei-tao-lun-o1-zuo-fa-by-endlesschen-95ef/
标签: 贪心, 分配
*/

public class Solution2591 {
    public int distMoney(int money, int children) {
        money -= children; // 每人一美元
        if (money < 0) return -1;
        int ans = Math.min(money / 7, children); // 可以出这么多个8
        int childrenLeft = children - ans; // 有这么多个1
        int moneyLeft = money - ans * 7; // 剩余的钱
        if (childrenLeft == 0 && moneyLeft > 0) return ans - 1;
        if (childrenLeft == 1 && moneyLeft == 3) return ans - 1;
        // 否则把钱全给childrenLeft中的一人，若其为4，则给一美元给别人，ans不变
        return ans;
    }

    public static void main(String[] args) {
        Solution2591 solu = new Solution2591();
        System.out.println(solu.distMoney(17, 2));
    }
}