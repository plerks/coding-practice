/*
url: https://leetcode.cn/problems/pass-the-pillow/?envType=daily-question&envId=2023-09-26
LeetCode参考: https://leetcode.cn/problems/pass-the-pillow/solutions/2451117/di-zhen-tou-by-leetcode-solution-kl5e/
标签: 游标自动双向移动time后的位置
*/

public class Solution2582 {
    public int passThePillow(int n, int time) {
        // 每2(n-1)为一个周期
        int remain = time % (2 * (n - 1));
        if (remain < n) { // 有效步<= n - 1, 还没反向
            return remain + 1;
        }
        else { // 在n - 1时反向，又过了remain - (n - 1)时间
            return n - (remain - (n - 1));
        }
    }

    public static void main(String[] args) {
        Solution2582 solu = new Solution2582();
        System.out.println(solu.passThePillow(3, 2));
    }
}