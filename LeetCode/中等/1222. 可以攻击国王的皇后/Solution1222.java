// https://leetcode.cn/problems/queens-that-can-attack-the-king/?envType=daily-question&envId=2023-09-14

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class Solution1222 {
    public List<List<Integer>> queensAttacktheKing(int[][] queens, int[] king) {
        List<List<Integer>> ans = new ArrayList<>();
        HashSet<Integer> set = new HashSet<>();
        for (int[] arr : queens) {
            set.add(arr[0] * 8 + arr[1]);
        }
        int[][] directions = new int[][]{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
        for (int[] direction : directions) {
            int x = king[0], y = king[1];
            while (true) {
                x += direction[0];
                y += direction[1];
                if (!(x >= 0 && x <= 7 && y >= 0 && y <= 7)) break;
                if (set.contains(x * 8 + y)) {
                    List<Integer> list = new ArrayList<>();
                    list.add(x);
                    list.add(y);
                    ans.add(list);
                    break;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1222 solu = new Solution1222();
        System.out.println(solu.queensAttacktheKing(new int[][]{{0,1},{1,0},{4,0},{0,4},{3,3},{2,4}}, new int[]{0, 0}));
    }
}