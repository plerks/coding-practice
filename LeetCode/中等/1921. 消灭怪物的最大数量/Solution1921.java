/*
url: https://leetcode.cn/problems/eliminate-maximum-number-of-monsters/?envType=daily-question&envId=2023-09-03
LeetCode参考: https://leetcode.cn/problems/eliminate-maximum-number-of-monsters/solutions/857961/xiao-mie-guai-wu-de-zui-da-shu-liang-by-0ou2p/
标签: 贪心
*/

import java.util.Arrays;

public class Solution1921 {
    public int eliminateMaximum(int[] dist, int[] speed) {
        // 记录怪物到达时间
        int[] monsters = new int[dist.length];
        for (int i = 0; i < monsters.length; i++) {
            // 向上取整
            monsters[i] = dist[i] % speed[i] == 0 ? dist[i] / speed[i] : dist[i] / speed[i] + 1;
        }
        Arrays.sort(monsters);
        int time = 0;
        int ans = 0;
        while (true) {
            if (time >= monsters.length || monsters[time] <= time) {
                break;
            }
            else {
                time++;
                ans++; // 消灭要最先到达的怪兽
            }
        }
        return ans;
    }

    public int eliminateMaximum_implementation2(int[] dist, int[] speed) {
        // 记录怪物到达时间
        int[] monsters = new int[dist.length];
        for (int i = 0; i < monsters.length; i++) {
            monsters[i] = (dist[i] - 1) / speed[i] + 1;
        }
        Arrays.sort(monsters);
        for (int i = 0; i < monsters.length; i++) {
            if (monsters[i] <= i) return i;
        }
        return monsters.length;
    }

    public static void main(String[] args) {
        Solution1921 solu = new Solution1921();
        System.out.println(solu.eliminateMaximum(new int[]{1,3,4}, new int[]{1,1,1}));
        System.out.println(solu.eliminateMaximum_implementation2(new int[]{1,3,4}, new int[]{1,1,1}));
    }
}