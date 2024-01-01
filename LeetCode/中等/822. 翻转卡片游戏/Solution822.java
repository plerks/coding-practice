/*
url: https://leetcode.cn/problems/card-flipping-game/
LeetCode参考: https://leetcode.cn/problems/card-flipping-game/solutions/2368848/du-dong-ti-jiu-neng-shi-xian-de-suan-fa-3hx0s/
标签: 卡牌问题
*/

import java.util.HashSet;

public class Solution822 {
    public int flipgame(int[] fronts, int[] backs) {
        // 选背面的数字和所有正面不同，则当且仅当这个数字没有同时出现在一张卡牌的正反面即可选
        HashSet<Integer> set = new HashSet<>();
        for (int i = 0; i < fronts.length; i++) {
            if (fronts[i] == backs[i]) {
                set.add(fronts[i]);
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int i : fronts) {
            if (!set.contains(i)) {
                ans = Math.min(ans, i);
            }
        }
        for (int i : backs) {
            if (!set.contains(i)) {
                ans = Math.min(ans, i);
            }
        }
        return ans == Integer.MAX_VALUE ? 0 : ans;
    }

    public static void main(String[] args) {
        Solution822 solu = new Solution822();
        System.out.println(solu.flipgame(new int[]{1,2,4,4,7}, new int[]{1,3,4,1,3}));
    }
}