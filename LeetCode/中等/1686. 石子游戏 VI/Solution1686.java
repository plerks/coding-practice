/*
url: https://leetcode.cn/problems/stone-game-vi/description/?envType=daily-question&envId=2024-02-02
相关: LeetCode1402. 做菜顺序, LeetCode2029. 石子游戏 IX, LeetCode1690. 石子游戏 VII
我的题解: https://leetcode.cn/problems/stone-game-vi/solutions/2628684/fen-xi-er-ren-xuan-ze-de-zui-you-ce-lue-oje8f/
标签: 标号数组排序, 石子游戏
*/

import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution1686 {
    public int stoneGameVI(int[] aliceValues, int[] bobValues) {
        /* 假设Alice最优选择的石子序列为...,i,...。若Alice的最优解不需要i，则Alice的最优解要从Bob选择的石子序列中交换一个j。
        Alice i Bob j，Alice和Bob的得分差为aliceValues[i]-bobValues[j]，Alice j Bob i，得分差为aliceValues[j]-bobValues[i]。
        aliceValues[i]-bobValues[j] > aliceValues[j]-bobValues[i] <=> aliceValues[i]+bobValues[i] > aliceValues[j]+bobValues[j]。
        这样看来aliceValues[i]+bobValues[i]似乎是一个评判标准。

        下面说明只要Alice或者Bob面对着aliceValues[i]+bobValues[i]的最大值，他们就一定会抢这个i。
        若放任这个i不管而选择j，那么自己j对方i一定劣于自己i对方j。
        若自己放任i选择j，对方是否一定会马上抢走i?（即自己是否可以侥幸于对方不抢i，然后自己i,j都拿）
        若自己这一轮放走i而选择j，若对方在下一轮也选择放弃i而选择某个k，则由自己在下一回合抢回i，由上面的推导，对对方来说这一定不如
        抢i而让我方下一回合选剩余的某个x，
        即:
            自己: j   i
            对方:   k
        不如:
            自己: j   x
            对方:   i
        所以对方一定会抢i，而自己j对方i不如自己i对方j，因此己方一开始就该抢i。
        */
        int n = aliceValues.length;
        int aliceScore = 0;
        int bobScore = 0;
        PriorityQueue<Integer> q = new PriorityQueue<>((x, y) -> {
            return ((aliceValues[y] + bobValues[y]) - (aliceValues[x] + bobValues[x]));
        });
        for (int i = 0; i < n; i++) {
            q.offer(i);
        }
        for (int i = 0; i < (n + 1) / 2; i++) {
            aliceScore += aliceValues[q.poll()];
            if (!q.isEmpty()) {
                bobScore += bobValues[q.poll()];
            }
        }
        return aliceScore - bobScore > 0 ? 1 : aliceScore == bobScore ? 0 : -1;
    }

    // 实现2，实际运行时间更优
    public int stoneGameVI_implementation2(int[] aliceValues, int[] bobValues) {
        int n = aliceValues.length;
        int aliceScore = 0;
        int bobScore = 0;
        Integer[] idx = new Integer[n];
        for (int i = 0; i < n; i++) idx[i] = i;
        Arrays.sort(idx, (x, y) -> {
            return ((aliceValues[y] + bobValues[y]) - (aliceValues[x] + bobValues[x]));
        });
        int i = 0;
        while (i < n) {
            aliceScore += aliceValues[idx[i++]];
            if (i < n) {
                bobScore += bobValues[idx[i++]];
            }
        }
        return aliceScore - bobScore > 0 ? 1 : aliceScore == bobScore ? 0 : -1;
    }

    public static void main(String[] args) {
        Solution1686 solu = new Solution1686();
        System.out.println(solu.stoneGameVI(new int[]{2,4,3}, new int[]{1,6,7}));
    }
}
