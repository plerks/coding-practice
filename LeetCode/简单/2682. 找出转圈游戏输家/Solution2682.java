// https://leetcode.cn/problems/find-the-losers-of-the-circular-game/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution2682 {
    public int[] circularGameLosers(int n, int k) {
        int[] players = new int[n]; // 各个玩家接球数
        players[0] = 1;
        int pos = 0;
        int time = 1;
        while (true) {
            pos = (pos + k * time) % n;
            time++;
            players[pos]++;
            if (players[pos] == 2) {
                break;
            }
        }
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < players.length; i++) {
            if (players[i] == 0) {
                list.add(i + 1);
            }
        }
        int[] ans = new int[list.size()];
        for (int i = 0; i < list.size(); i++) {
            ans[i] = list.get(i);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2682 solu = new Solution2682();
        System.out.println(Arrays.toString(solu.circularGameLosers(5, 2)));
    }
}